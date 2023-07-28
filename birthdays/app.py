import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

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
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if name or not month or not day:
            db.execute("INSERT into birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")
        else:
            message = "Input incomplete"
            rows = db.execute("SELECT * FROM birthdays")
            return render_template("index.html",message=message, rows=rows)

    else:
        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * from birthdays;")
        return render_template("index.html", rows=rows)


# Delete entry
@app.route("/", methods=["GET", "POST"])
def delete(id):
    if request.method == "POST":
        message = "Entry deleted"
        db.execute("DELETE FROM birthdays WHERE id=?", id)
        birthdays = db.execute("SELECT * FROM birthdays")
        return redirect("index.html",message=message, rows=rows)





