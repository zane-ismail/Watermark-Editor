import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        symbols = []
        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        purchases = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
        for purchase in purchases:
            print(purchase)
            print(purchase['symbol'])
            for symbol in symbols:
                if purchase['symbol'] == symbol:
                    ...
                else:
                    symbols.append(purchase['symbol'])
        print(symbols)



        # print(purchases)
        # i = 1
        # sum = 0
        # for purchase in purchases:
        #     if i < len(purchases):
        #         if purchase["symbol"] == purchases[i]["symbol"] and purchase["type"] == "BUY":
        #             shares = 0
        #             symbol = purchase["symbol"]
        #             shares = shares + int(purchase['shares'])
        #             price = purchase["price"]
        #             sum = sum + price
        #             i += 1
        #         cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        #         cash = int(cash[0]["cash"])
        #         sum = sum + cash
        #         print(shares)

    return render_template("index.html")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Submit the user’s input via POST to /buy.
    if request.method == "POST":
        # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.symbol = request.form.get("symbol")
        symbol = request.form.get("symbol")
        # Require that a user input a number of shares, implemented as a text field whose name is shares.
        shares = int(request.form.get("shares"))
        # Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
        if not symbol:
            return apology("Please enter a symbol")
        # Render an apology if the input is not a positive integer.
        elif shares <= 0:
            return apology("Please enter a positive amount of shares")
        else:
            # Call lookup to look up a stock’s current price
            price = lookup(symbol)
            print(price)
            price = price['price']
            cost = (shares * price)
            transaction = "BUY"
            # SELECT how much cash the user currently has in users
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = cash[0]['cash']
            sum = cash - cost
            # Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
            if cost > cash:
                return apology("Not enough money")
            else:
                try:
                    # Add one or more new tables to finance.db via which to keep track of the purchase.
                    # Store enough information so that you know who bought what at what price and when.
                    db.execute("CREATE TABLE purchases(user_id int NOT NULL, symbol varchar(255), shares int, price float, type varchar(4))")
                except:
                    pass
                # Update cash in database to reflect purchase
                db.execute("UPDATE users SET cash = ? WHERE id = ?", sum, session["user_id"])

            db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?)", session['user_id'], symbol, shares, price, transaction)
            # Upon completion, redirect the user to the home page.
            return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Display an HTML table summarizing all of a user’s transactions ever, listing row by row each and every buy and every sell.
    transactions = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    print(transactions)
    # For each row, make clear whether a stock was bought or sold and include the stock’s symbol, the (purchase or sale) price, the number of shares bought or sold, and the date and time at which the transaction occurred.
    # You might need to alter the table you created for buy or supplement it with an additional table. Try to minimize redundancies.

    return render_template("history.html", transactions=transactions, cash=cash)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
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
    # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol
    symbol = request.form.get("symbol")
    # Submit the user’s input via POST to /quote.
    if request.method == "POST":
        symbol = lookup(symbol)
        return render_template("quoted.html", symbol=symbol)
    #  In response to a POST, quote can render that second template, embedding within it one or more values from lookup.
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Require that a user input a username
    username = request.form.get("username")

    # Require that a user input a password, and then that same password again
    password = request.form.get("password")
    confirmation = request.form.get("confirmation")

    if request.method == "POST":
        # Store a hash of the user’s password
        hash = generate_password_hash(password)
        # INSERT the new user into users
        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        try:
            existing_user = user[0]['username']
            # Render an apology if username already exists
            if existing_user == username:
                return apology("Username already taken", 403)
        except:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

            # Render an apology if either input is blank or the passwords do not match.
            if not request.form.get("username"):
                return apology("Please enter username", 403)
            elif not request.form.get("password"):
                return apology("Please enter password", 403)
            elif not request.form.get("confirmation"):
                return apology("Please confirm password", 403)
            elif password != confirmation:
                return apology("Passwords do not match", 403)

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # Require that a user input a stock’s symbol, implemented as a select menu whose name is symbol.
    symbol = request.form.get("symbol")
    # Require that a user input a number of shares, implemented as a text field whose name is shares.
    shares = request.form.get("shares")
    transaction = "SELL"
    # Submit the user’s input via POST to /sell.
    if request.method == "POST":
        price = lookup(symbol)
        price = price['price']
        shares = int(shares)
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]['cash']
        sum = cash + price
        stocks = db.execute("SELECT symbol FROM purchases WHERE user_id = ?", session['user_id'])
        amount = db.execute("SELECT shares FROM purchases WHERE symbol = ?", stocks[0]['symbol'])
        rows = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
        i = 0
        total_shares = 0
        for row in rows:
            user_stocks = (stocks[0]['symbol'])
            total_shares += (amount[i]['shares'])
            i += 1
        # Render an apology if the input is not a positive integer or if the user does not own that many shares of the stock.
        if total_shares < shares:
            return apology("Not enough stocks")
        elif symbol == user_stocks:
            db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?)", session['user_id'], symbol, shares, price, transaction)
            # Update cash in database to reflect sale
            db.execute("UPDATE users SET cash = ? WHERE id = ?", sum, session["user_id"])
            return redirect("/")
            # Render an apology if the user fails to select a stock
        elif not symbol:
            return apology("Please enter a symbol")
        # Or if (somehow, once submitted) the user does not own any shares of that stock.
        else:
            return apology("Stock not owned")
    # Upon completion, redirect the user to the home page.
    return render_template("sell.html")
