import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)
app.secret_key = "abcdefg1234567"

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    id = request.form.get("id")
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        message = ""
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if name and month and day:
            db.execute("INSERT into birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")
        else:
            message = "Input incomplete"
            rows = db.execute("SELECT * FROM birthdays")
            return render_template("index.html", message=message, rows=rows)

    else:
        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * from birthdays;")
        return render_template("index.html", rows=rows)


@app.route("/update/<int:id>", methods=["POST"])
def update(id):
    if request.method == "POST":
        name = db.execute("SELECT (name) FROM birthdays WHERE id = ?", id)
        print(name)
        rows = db.execute("SELECT * FROM birthdays")
        return render_template("/update.html", rows=rows)


# Delete entry
@app.route("/delete/<int:id>", methods=["POST"])
def delete(id):
    if request.method == "POST":
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
        rows = db.execute("SELECT * FROM birthdays")
        message = "Input deleted"
        return render_template("index.html", message=message, rows=rows)




