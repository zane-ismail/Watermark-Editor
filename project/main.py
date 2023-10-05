import csv
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

data = []
recipe_data = []
query = []
length = 0
query_input = input("What ingredients do you have?: ").lower().split()
for i in query_input:
    length += 1
    for item in i:
        item.replace(",", "")


def read_csv():
    with open('Recipes.csv', encoding="utf8") as data_csv:
        reader = csv.DictReader(data_csv)
        total_recipes = 0
        for row in reader:
            data = row
            return(data)

def query():
    # Todo create a new function for queries
    count = 0
    for i in query_input:
        i = i.replace(",", "")
        # Search ONLY exact match
        for ingredient in data['ingredients'].replace("'", " ").replace("[", " ").replace("]", " ").split(","):
        # Expanded search
        for ingredient in data['ingredients'].replace("'", " ").replace(",", " ").replace("[", " ").replace("]", " ").split(","):
            print(ingredient)
            if i == ingredient:
                count += 1
    # Enter data into dictionary
    if count == length:
        total_recipes += 1
        for x in range(total_recipes):
            recipe_data.append({data['name']: data['ingredients']})
            total_recipes = 0
# Todo be able to call any given recipe name and pull data for it (db query)
for recipe in recipe_data:
    for name in recipe:
        if name == 'vegan tiramisu':
            print(data['vegan tiramisu'])


def create_database():
    data = read_csv()
    # Todo Add csv into database
    try:
        db.execute("CREATE TABLE recipes(id int NOT NULL, name varchar(255), ingredients varchar(255), description varchar(255), steps text, minutes int, tags varchar(255), n_ingredients int, n_steps int)")
        # Todo add each parameter to the db
        db.execute("INSERT INTO purchases VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", data['id'], data['name'], data['ingredients'], data['description'], data['steps'], data['minutes'], data['tags'], data['n_ingredients'], data['n_steps'], data[''])
    except RuntimeError:
        pass







read_csv()

# print(data)
# for ingredient in data['ingredients']:
#     print(ingredient)