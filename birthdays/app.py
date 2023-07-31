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


@app.route("/", methods=["GET", "POST"])update50
def index():
    if request.method == "POST":
        message = ""
        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")
        if name and month and day:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
            return redirect("/")
        else:
            message = "Input incomplete"
            rows = db.execute("SELECT * FROM birthdays")
            return render_template("index.html", message=message, rows=rows)

    else:
        # TODO: Display the entries in the database on index.html
        rows = db.execute("SELECT * from birthdays;")
        return render_template("index.html", rows=rows)


@app.route("/update/<int:id>", methods=["GET", "POST"])
def update(id):
    if request.method == "POST":
        birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", id)
        name = birthday[0]["name"]
        month = birthday[0]["month"]
        day = birthday[0]["day"]
        rows = db.execute("SELECT * FROM birthdays")
        new_name = request.form.get("updated_name")
        new_month = request.form.get("updated_month")
        new_day = request.form.get("updated_day")
        if new_name:
            db.execute("UPDATE birthdays SET name = ? WHERE id = ?", new_name, id)
            db.execute("UPDATE birthdays SET month = ? WHERE id = ?", new_month, id)
            db.execute("UPDATE birthdays SET day = ? WHERE id = ?", new_day, id)
            return redirect("/")
        else:
            if request.method == "POST":
                return render_template("/update.html", rows=rows, name=name, month=month, day=day, current_id=id)
    else:
        rows = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", message=message, rows=rows)


# Delete entry
@app.route("/delete/<int:id>", methods=["POST"])
def delete(id):
    if request.method == "POST":
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
        rows = db.execute("SELECT * FROM birthdays")
        message = "Input deleted"
        return render_template("index.html", message=message, rows=rows)




