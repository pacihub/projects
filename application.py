import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

#    portfolio = db.execute("SELECT stock,SUM(quantity),cash FROM transactions JOIN users ON users.id = transactions.id WHERE transactions.id = :id GROUP BY stock HAVING SUM(quantity) > 0", id = session["user_id"])

    portfolio = db.execute("SELECT stock, SUM(quantity) FROM transactions WHERE id = :id GROUP BY stock HAVING SUM(quantity) > 0", id = session["user_id"])

    cash_balance = db.execute("SELECT cash FROM users WHERE id = :id", id = session["user_id"])
#    cash_amount = "{:.2f}".format(cash_balance[0]["cash"])
    cash_amount = round(cash_balance[0]["cash"],2)

    total_stocks_value = 0

    for ticker in portfolio:
        price_now = lookup(ticker["stock"])["price"]
        stock_value = price_now * ticker["SUM(quantity)"]
        ticker.update({'price' : usd(price_now), 'equity' : stock_value })
        total_stocks_value += stock_value

    total_acct_value = total_stocks_value + cash_amount
#    ticker = lookup(portfolio["stock"])
#    for i in range(len(portfolio)):
#        stock_price = lookup(portfolio[i]["stock"])
#        prices.append(stock_price["price"])
    logged_username = db.execute("SELECT username FROM users where id = :id",id = session["user_id"] )
    return render_template("index.html", portfolio = portfolio, cash_amount = cash_amount, total_acct_value = round(total_acct_value,2), logged_username = logged_username[0]["username"])


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    tr_history = db.execute("SELECT * FROM transactions WHERE id = :id", id = session["user_id"])
    return render_template("history.html", tr_history = tr_history)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        if not request.form.get("username"):
            return apology("must provide username", 401)
        elif not request.form.get("password"):
            return apology("must provide password", 401)
        elif not request.form.get("confirmation"):
            return apology("must provide password", 401)

        if request.form.get("password") != request.form.get("confirmation"):
            return("passwords don't match, dude")

        db.execute("INSERT into users (username, hash) VALUES (:username, :hash)",
        username = request.form.get("username"),
        hash = generate_password_hash(request.form.get("password")))

        return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        listofdicts = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
    #check_password_hash compares the stored in the DB hash at rows[0]["hash"] VS has of the password
        if len(listofdicts) != 1 or not check_password_hash(listofdicts[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = listofdicts[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    else:
        if not request.form.get("symbol"):
            return apology("please enter a ticker",403)

        elif not lookup(request.form.get("symbol")):
            return apology("not a valid ticker",403)


        stock = lookup(request.form.get("symbol"))
        return render_template("quoted.html", stock = stock)
        #passing the value of 'price' from python to html

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        users_cashdict = db.execute("SELECT cash FROM users WHERE id = :id",
        id = session["user_id"])
        buying_power = users_cashdict[0]["cash"]

        return render_template("buy.html", buying_power = round(buying_power,2), id = id)

    else:
#        if request.form.action:
            if not request.form.get("symbol"):
                return apology("please enter a ticker man",403)

            elif not lookup(request.form.get("symbol")):
                return apology("not a valid ticker dude",403)

            elif int(request.form.get("shares")) <= 0:
                return apology("dude, you can't buy negative shares", 403)

            #getting the account cash value of the current user
            users_cashdict = db.execute("SELECT cash FROM users WHERE id = :id",
            id = session["user_id"])
            buying_power = users_cashdict[0]["cash"]

            # condition on what to do if funds for transaction are insufficient
            stock = lookup(request.form.get("symbol"))
            num_sharestobuy = int(request.form.get("shares"))
            trx_cost = stock["price"] * num_sharestobuy

            if buying_power < trx_cost:
                return apology("not enough cash, dude", 401)
            else:
                        #""" Getting the price of the stock. lookup(request.form.get("symbol")) returns a dict
                        #with keys as follows {name: (value)
                        #                     symbol: (value)
                        #                     price: (value) }
                        #So stock["price"] accesses the value of price. """

                        #update CASH column in the users table
                db.execute("UPDATE users SET cash = cash - :trx_cost WHERE id = :id", trx_cost = trx_cost, id = session["user_id"])

                        #add transaction to transactions database

                db.execute("INSERT INTO transactions (id, stock, quantity, price, date) VALUES(:id, :stock, :quantity, :price, :date)",
                id = session["user_id"], stock = stock["symbol"], quantity = num_sharestobuy,
                price = stock["price"], date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
                return redirect("/")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        return render_template("sell.html")

    else:
        if not request.form.get("symbol"):
            return apology("please enter a ticker man",403)

        elif not lookup(request.form.get("symbol")):
            return apology("not a valid ticker dude",403)

        elif int(request.form.get("shares")) <= 0:
            return apology("dude, you can't sell negative shares", 403)



#getting the account stock value of the current user
        users_sharesdict = db.execute("SELECT quantity FROM transactions WHERE id = :id",
        id = session["user_id"])
        avail_shares = users_sharesdict[0]["quantity"]

# condition on what to do if funds for transaction are insufficient
        stock = lookup(request.form.get("symbol"))
        num_sharestosell = int(request.form.get("shares"))
        trx_proceeds = stock["price"] * num_sharestosell

      #check if user owns the stock
        existing_ticker = db.execute("SELECT stock FROM transactions WHERE id = :id AND stock = :stock",
        id = session["user_id"], stock = stock["symbol"])

        ticker_balance = db.execute("SELECT SUM(quantity) FROM transactions where id = :id AND stock = :stock",
        id = session["user_id"], stock = stock["symbol"])

        if not existing_ticker:
            return apology("you don't own this dude", 401)

        if ticker_balance[0]["SUM(quantity)"] == 0:
            return apology("you've traded this before, but now you have 0 shares of it", 401)

        if avail_shares < num_sharestosell:
            return apology("not enough shares, dude", 401)

        else:
#update CASH column in the users table
            db.execute("UPDATE users SET cash = cash + :trx_proceeds WHERE id = :id", trx_proceeds = trx_proceeds, id = session["user_id"])

#add transaction to transactions database
            db.execute("INSERT INTO transactions (id, stock, quantity, price, date) VALUES(:id, :stock, :quantity, :price, :date)",
            id = session["user_id"], stock = stock["symbol"], quantity = -num_sharestosell,
            price = stock["price"], date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
            return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
def add():
    if request.method == "GET":
        return render_template("addcash.html")

    else:
        how_much = request.form.get("addcash")

        if not how_much:
            return apology("please enter a ticker",403)

        elif int(how_much) <= 0:
            return apology("feeling generous today?", 403)

        elif int(how_much) > 5000:
            return apology("don't be so greedy!", 403)

        else:
               db.execute("UPDATE users SET cash = cash + :added_cash WHERE id = :id",
                added_cash = how_much, id = session["user_id"])

               return (f"you just added  ${how_much} to your account.")
               return render_template("index.html")








def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
