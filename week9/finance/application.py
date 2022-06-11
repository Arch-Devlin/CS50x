import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

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
    index = db.execute(
        "SELECT SUM(amount) as shares, name, symbol, price FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    total = cash

    for i in index:
        total += i["shares"] * i["price"]

    return render_template("index.html", index=index, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide stock’s symbol", 400)

        elif not request.form.get("shares"):
            return apology("must provide amount", 400)
        
        elif not (request.form.get("shares")).isnumeric():
            return apology("share amount must be positive int", 400)

        else:
            stock = lookup(request.form.get("symbol"))

            if not stock:
                return apology("must provide valid stock’s symbol", 400)

            else:
                cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
                amount = request.form.get("shares", type=int)
                funds = cash[0]['cash']
                cost = amount * stock['price']

                if funds < cost:
                    return apology("not enough money", 400)
                else:
                    left = funds - cost
                    buy = db.execute("UPDATE users SET cash = ? WHERE id = ?", left, session["user_id"])
                    history = db.execute("INSERT INTO history (amount, name, symbol, type, price, total, user_id) VALUES(?, ?, ?, 'bought', ?, ?, ?)",
                                         amount, stock['name'], stock['symbol'], stock['price'], cost, session["user_id"])
                    return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE user_id = ?", session["user_id"])
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide stock’s symbol", 400)

        else:
            stock = lookup(request.form.get("symbol"))

            if not stock:
                return apology("must provide valid stock’s symbol", 400)

            else:
                return render_template("quoted.html", stock=stock)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation"):
            return apology("must confirm password", 400)

        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("passwords must match", 400)
        
        # inspired by answer on stackoverflow (any functiony)
        elif any(char.isdigit() for char in request.form.get("password")) != True:
            return apology("password must contain a number", 400)

        elif any(char.isupper() for char in request.form.get("password")) != True:
            return apology("password must contain a capital letter", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) == 0:
            hashed = generate_password_hash(request.form.get("password"))

            new = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), hashed)
        else:
            return apology("Username taken", 400)

        # get "user_id"

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        symbol = request.form.get("symbol")
        stock = lookup(symbol)
        amount = request.form.get("shares", type=int)
        check = db.execute("SELECT amount FROM history WHERE user_id = ? and symbol = ?", session["user_id"], symbol)[0]["amount"]
        
        if amount < 1 or amount == None:
            return apology("must sell at least 1 share", 400)
        
        elif check < amount:
            return apology("You dont have that many shares", 400)
        else:
            cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]['cash']
            price = amount * stock["price"]
            new = cash + price
            sell = db.execute("UPDATE users SET cash = ? WHERE id = ?", new, session["user_id"])
            history = db.execute("INSERT INTO history (amount, name, symbol, type, price, total, user_id) VALUES(?, ?, ?, 'sold', ?, ?, ?)", -
                                 amount, stock['name'], stock['symbol'], stock['price'], price, session["user_id"])
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        symbols = db.execute("SELECT symbol FROM history WHERE user_id = ? GROUP BY symbol", session["user_id"])
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
