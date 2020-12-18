import requests
import os

from flask import redirect, render_template, request, session
from functools import wraps



def tickercheck(i):
    key = session["apitoken"]
    try:

        response = requests.get(f"https://www.alphavantage.co/query?function=OVERVIEW&symbol={i}&apikey={key}")

    #the API returns a JSON dict that i call 'api' and I parse and access its key:values accordingly
    except requests.RequestException:
        return None
    
    #then my function accesses those api's values and assigns them in my keys such as
    # "symbol", "name", "sector", etc.
    #then my function returns a dict (stockdata) with keys defined by me and values taken from the API
  
    try:
        api = response.json()
        return {
            "symbol" : api["Symbol"],
            "name" : api["Name"],
            "sector" : api["Sector"],
            "industry" : api["Industry"],
            "marketcap" : api["MarketCapitalization"],
            "peratio" : api["PERatio"],
            "bookvalue" : api["BookValue"],
            "divpershare" : api["DividendPerShare"],
            "divyield" : api["DividendYield"],
            "divdate" : api["DividendDate"],
            "exdivdate" :api["ExDividendDate"],
            "beta" : float(api["Beta"]),
            "52wkhigh" : api["52WeekHigh"],
            "52wklow" : api["52WeekLow"],
            "exchange" : api["Exchange"],
            "payoutratio" : api["PayoutRatio"]
        }
    except (KeyError, TypeError, ValueError):
        return None   

    
def login_required(f):

    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function    
    