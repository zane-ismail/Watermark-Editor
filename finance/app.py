import os

from datetime import datetime
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
        i = 1
        stocks_dict = {}
        symbols = []
        stocks = []
        prices = [0]
        user = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        try:
            cash = float(cash[0]["cash"])
            # add all user's stock symbols to a list
            purchases = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
            for purchase in purchases:
                # add the first symbol
                while i > 0:
                    symbols.append(purchase['symbol'])
                    i =- 1
                # add only unique symbols to list
                for symbol in symbols:
                    if purchase['symbol'] == symbol:
                        break
                    else:
                        symbols.append(purchase['symbol'])
            # tally how many shares a user has for each stock
            for symbol in symbols:
                shares_amount = 0
                i = 0
                all_shares = db.execute("SELECT * FROM purchases WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
                shares = db.execute("SELECT shares FROM purchases WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
                for share in all_shares:
                    if i < len(all_shares):
                        if share['type'] == "BUY":
                            shares_amount = shares_amount + share['shares']
                        else:
                            shares_amount = shares_amount - share['shares']
                        i =+ 1
                # Don't display stocks the user previously owned
                if shares_amount < 1:
                    symbols.remove(symbol)
                    pass
                # Add number of stocks owned to dictionary
                else:
                    stocks.append(shares_amount)
                    stocks_dict.update({symbol: shares_amount})

            sum = 0
            for symbol in stocks_dict:
                price = lookup(symbol)
                prices.append(price["price"])
                sum = sum + price["price"] * stocks_dict[symbol]
            total = sum + cash
        # if the user has no assets
        except:
            return render_template("index.html", stocks_dict=[], cash=10000, sum=0, prices=0, total=10000)


    return render_template("index.html", stocks_dict=stocks_dict, cash=cash, sum=sum, prices=prices, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # Submit the user’s input via POST to /buy.
    if request.method == "POST":
        # Require that a user input a stock’s symbol, implemented as a text field whose name is symbol.symbol = request.form.get("symbol")
        symbol = request.form.get("symbol").upper()
        # Require that a user input a number of shares, implemented as a text field whose name is shares.
        shares = float(request.form.get("shares"))
        # Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
        if not symbol:
            return apology("Missing symbol")
        # Render an apology if the input is not a positive integer.
        elif not shares:
            return apology("Missing shares")
        else:
            # Call lookup to look up a stock’s current price
            price = lookup(symbol)
            # Render an apology if the symbol does not exist (as per the return value of lookup)
            if price == None:
                return apology("Invalid symbol")
            price = float(price['price'])
            cost = (shares * price)
            transaction = "BUY"
            ts = datetime.today().strftime('%Y-%m-%d %I:%M:%S')
            # SELECT how much cash the user currently has in users
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = float(cash[0]['cash'])
            sum = cash - cost
            # Render an apology, without completing a purchase, if the user cannot afford the number of shares at the current price.
            if cost > cash:
                return apology("Can't afford")
            else:
                try:
                    # Add one or more new tables to finance.db via which to keep track of the purchase.
                    # Store enough information so that you know who bought what at what price and when.
                    db.execute("CREATE TABLE purchases(user_id int NOT NULL, symbol varchar(255), shares int, price float, type varchar(4), time varchar(255))")
                except RuntimeError:
                    pass
                # Update cash in database to reflect purchase
                db.execute("UPDATE users SET cash = ? WHERE id = ?", sum, session["user_id"])

            db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?, ?)", session['user_id'], symbol, shares, price, transaction, ts)
            # Upon completion, redirect the user to the home page.
            flash("Bought!")
            return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Display an HTML table summarizing all of a user’s transactions ever, listing row by row each and every buy and every sell.
    try:
        transactions = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        # For each row, make clear whether a stock was bought or sold and include the stock’s symbol, the (purchase or sale) price, the number of shares bought or sold, and the date and time at which the transaction occurred.
        # You might need to alter the table you created for buy or supplement it with an additional table. Try to minimize redundancies.
    except:
        return render_template("history.html")

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
            return apology("Must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 403)

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
        price = lookup(symbol)
        # Render an apology if the symbol does not exist (as per the return value of lookup)
        if price == None:
            return apology("Invalid symbol")
        # Render an apology if the input is blank
        if not symbol:
            return apology("Missing symbol")
        return render_template("quoted.html", price=price)
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
        i = 0
        # Check existing usernames
        users = db.execute("SELECT username FROM users")

        for user in users:
            if i < len(users):
                print(f"USER: {user}")
                # Render an apology if username already exists
                print(f"USER: {users[i]['username']}")
                if users[i]['username'] == user:
                    return apology("Username already taken", 403)
            else:
                i =+ 1
        # Render an apology if either input is blank or the passwords do not match.
        if not request.form.get("username"):
            return apology("Missing username", 400)
        elif not request.form.get("password"):
            return apology("Missing password", 400)
        elif not request.form.get("confirmation"):
            return apology("Passwords don't match", 400)
        elif password != confirmation:
            return apology("Passwords don't match", 400)
        else:
            # Store a hash of the user’s password
            hash = generate_password_hash(password)
            # INSERT the new user into users
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            # Query database for username
            rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            session["user_id"] = rows[0]["id"]
            db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
            # Redirect user to home page
            flash("Registered!")
            return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # Submit the user’s input via POST to /sell.
    symbols = []
    symbols_owned = []
    rows = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
    for row in rows:
        if row['symbol'] not in symbols:
            symbols.append(row['symbol'])
    for symbol in symbols:
        rows = db.execute("SELECT * FROM purchases WHERE symbol = ? AND user_id = ?", symbol, session["user_id"])
        total_shares = 0
        for row in rows:
            if row["type"] == "BUY":
                total_shares =  total_shares + row["shares"]
            elif row["type"] == "SELL":
                total_shares = total_shares - row["shares"]
        if total_shares > 0:
            if row['symbol'] not in symbols_owned:
                symbols_owned.append(row['symbol'])
    print(symbols_owned)





    if request.method == "POST":
        """Sell shares of stock"""
        # Require that a user input a stock’s symbol, implemented as a select menu whose name is symbol.
        symbol = request.form.get("symbol").upper()
        # Require that a user input a number of shares, implemented as a text field whose name is shares.
        shares = float(request.form.get("shares"))
        # Render an apology if the input is blank or the symbol does not exist (as per the return value of lookup).
        if not symbol:
            return apology("Missing symbol")
        # Render an apology if the input is not a positive integer.
        elif not shares:
            return apology("Missing shares")
        else:
            transaction = "SELL"
            ts = datetime.today().strftime('%Y-%m-%d %I:%M:%S')
            price = lookup(symbol)
            # Render an apology if the symbol does not exist (as per the return value of lookup)
            if price == None:
                return apology("Invalid symbol")
            price = float(price['price'])
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash = cash[0]['cash']
            sum = cash + (shares * price)
            rows = db.execute("SELECT * FROM purchases WHERE user_id = ?", session["user_id"])
            total_shares = 0
            for row in rows:
                if row['symbol'] == symbol:
                    if row["type"] == "BUY":
                        total_shares =  total_shares + row["shares"]
                    elif row["type"] == "SELL":
                        total_shares = total_shares - row["shares"]
                    elif not symbol:
                        return apology("Missing symbol")
            # Render an apology if the input is not a positive integer or if the user does not own that many shares of the stock.
            if total_shares < shares:
                return apology("Too many shares")
            else:
                db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?, ?)", session['user_id'], symbol, shares, price, transaction, ts)
                # Update cash in database to reflect sale
                db.execute("UPDATE users SET cash = ? WHERE id = ?", sum, session["user_id"])
                flash("Sold!")
                return redirect("/")
                # Render an apology if the user fails to select a stock
            # Or if (somehow, once submitted) the user does not own any shares of that stock.

    # Upon completion, redirect the user to the home page.
    return render_template("sell.html", symbols=symbols_owned)
