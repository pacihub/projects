from flask import Flask, render_template, request, jsonify, json, flash, redirect, session
import random
from flask_session import Session
from cs50 import SQL
import os, requests

#for password hashing
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

#import my functions
from functions import tickercheck, login_required


#configure application
app = Flask(__name__)

@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


#app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

#connect my database
db = SQL("sqlite:///portfolio.db")

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

@app.route("/")
@login_required
def hey():

    return render_template("index.html")


@app.route("/mystocks", methods=["GET", "POST"])
@login_required
def ms():
#    if request.method == 'POST':
        #query a list of logged in user's favorite stocks.
        my_stocks = db.execute("SELECT *  FROM stockz WHERE id = :id ORDER BY divyield DESC", 
        id = session["user_id"])
        
        #query user's username to display on top of the html table
        user = db.execute("SELECT username FROM userz WHERE id = :id", id = session["user_id"])

        return render_template("mystocks.html", my_stocks = my_stocks, user=user[0]["username"])

#the my_stocks and user variable are a list of dictionaries. 
#That's why the index [0] when passing to the view (html)

@app.route("/explore", methods=["GET", "POST"])
@login_required
def expl():
    if request.method == 'POST':
        
        #whatever the user entered in the front end casted to all UPPER case
        symbol = request.form.get("ticker").upper()
        
        if not symbol:
            return "please enter a ticker"

        elif not tickercheck(symbol):
            return "not a valid ticker"
            
        #my function 'tickercheck' returns me a dict for XYZ stock for example per f-n definition
        #I store the whole dict in variable 'stockdata'
        stockdata = tickercheck(symbol)
        
        #I need to access stock data between routes, so I store it in Session dict which is global
        #and I can access those keys from different routes later
        session["ticker"] = stockdata["symbol"]
        session["name"] = stockdata["name"]
        session["beta"] = stockdata["beta"]
        session["sector"] = stockdata["sector"]
        session["divyield"] = stockdata["divyield"]
        session["industry"] = stockdata["industry"]
        session["divdate"] = stockdata["divdate"]
        session["exdivdate"] = stockdata["exdivdate"] 
        session["payoutratio"] = stockdata["payoutratio"]
        session["divpershare"] = stockdata["divpershare"]
        
        return render_template("stdata.html", stockdata = stockdata)
        
    else:
        return render_template("explore.html")
 
 
@app.route("/stdata", methods=["GET", "POST"])
def stockdata():
    
        if request.method == 'POST':    
            
            #check if stock ticker is already in database by running a query. if it returns smth then stock is in
            if db.execute("SELECT ticker FROM stockz WHERE ticker = :tickerz AND id = :id", 
            tickerz = session["ticker"],id = session["user_id"]):
                return "stock is already in portfolio"
            
            #otherwise it injects all stock data into db. \ is for new line continuation w/out breaking code
            #I access all these values from the global session variables
            else:
                db.execute("INSERT INTO stockz (id, stock_name, ticker, beta, sector, divyield, industry, dividend_date, \
                exdividend_date, divpershare, payout_ratio) VALUES (:id, :stock_name, :ticker, :beta, :sector, :divyield, \
                :industry, :dividend_date, :exdividend_date, :divpershare, :payout_ratio)", id = session["user_id"], 
                stock_name = session["name"], ticker = session["ticker"],beta = session["beta"], 
                sector = session["sector"], divyield = session["divyield"], industry = session["industry"], dividend_date = session["divdate"],
                exdividend_date = session["exdivdate"], divpershare = session["divpershare"],
                payout_ratio = session["payoutratio"]) 
                      
                return redirect("/mystocks") 
                

@app.route("/delstock", methods=["GET", "POST"])  
@login_required
def delstk():
    
    #delete stock from user's favorites upon their selection
    if request.method == "POST":
        del_element = request.form.get("delelement").upper()
        
        db.execute("DELETE FROM stockz WHERE ticker = :element AND id = :id",
        element = del_element,id = session["user_id"])
        return redirect("/mystocks")                    
    
    
@app.route("/register", methods=["GET", "POST"])
def reg():
        if request.method == 'POST':
            if not request.form.get("username"):
                return "must provide username"
            elif not request.form.get("password"):
                return "must provide password"
            elif not request.form.get("confirmation"):
                return "you must retype your password"
    
            if request.form.get("password") != request.form.get("confirmation"):
                return("passwords don't match, dude")
    
            #check if username exists. Query for already registered username and if it exists ->error
            check_if_exist = db.execute("SELECT * FROM userz WHERE username = :username",
                          username=request.form.get("username"))
                          
            if check_if_exist:
                return "existing username. Try logging in instead."
            
            else:
                db.execute("INSERT into userz (username, hash) VALUES (:username, :hash)",
                username = request.form.get("username"),
                hash = generate_password_hash(request.form.get("password")))
    
            return redirect("/login")
            
        else:
            return render_template("register.html")    
    
    
@app.route("/login", methods = ["GET", "POST"])
def login():
 
    #forgets any user_id
    session.clear()
    
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return "must provide username"

        # Ensure password was submitted
        elif not request.form.get("password"):
            return "must provide password"
            
            
        rows = db.execute("SELECT * FROM userz WHERE username = :username",
                          username=request.form.get("username"))
                          
        if len(rows) != 1:
            return "invalid username"
        
        #remember that any sql query returns a list of dicts. That's why [0] index here
        #to access the value of key 'hash' in the 1st dictionary
        if not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return "password dude"
        
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        
        return redirect("/apiconnect")
    
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    return redirect("/")


@app.route("/apiconnect", methods=["GET", "POST"])  
@login_required

# Users must provide their own API token

def apifn():
        if request.method == "POST":
   
            users_apitoken = request.form.get("api")
            #I store user's input in a session key, which is global and I can access from my function
            session["apitoken"] = users_apitoken
            return redirect('/')
            
        else:
            return render_template('apiconnect.html')

@app.route("/newsearch", methods=["GET", "POST"]) 
def newsearch():
    
    return redirect('/explore')
    
    
@app.route("/contact", methods = ["GET","POST"])
def contact():
    
    if request.method == "GET":
        return render_template("contact.html")
    
    else:
        #grab the info that user typed in fields and stores in variable
        feedback_name = request.form.get("name")
        feedback_email = request.form.get("email")
        feedback_message = request.form.get("message")
        
        #inject the information in the DB in contact_form table.
        db.execute("INSERT into contact_form (name, email, message) VALUES (:ime, :email, :message)",
            ime = feedback_name, email = feedback_email, message = feedback_message)
          
        return redirect('/')

if __name__ == '__main__':
    app.run(debug = True)