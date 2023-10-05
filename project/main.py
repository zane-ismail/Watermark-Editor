import csv
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session

# Configure application
app = Flask(__name__)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///recipes.db")

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
        data = []
        for row in reader:
            data.append(row)
        return(data)

def query():
    # Todo create a new function for queries
    count = 0
    for i in query_input:
        i = i.replace(",", "")
        # Search ONLY exact match
        # for ingredient in data['ingredients'].replace("'", " ").replace("[", " ").replace("]", " ").split(","):
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
    try:
        db.execute("CREATE TABLE recipes(id int NOT NULL, name varchar(255), ingredients varchar(255), description varchar(255), steps varchar(255), minutes int, tags varchar(255), n_ingredients int, n_steps int)")
    except:
        pass
    for i in range(len(data)):
        for ingredient in data[i]['ingredients']:
            ingredient = ingredient.replace("[", " ").replace("]", " ").replace(",", ";").replace("'", " ")
        for description in data[i]['description']:
            description = description.replace("[", " ").replace("]", " ").replace(",", ";").replace("'", " ")
        for step in data[i]['steps']:
            step = step.replace("[", " ").replace("]", " ").replace(",", ";").replace("'", " ")
        for tag in data[i]['tags']:
            tag = tag.replace("[", " ").replace("]", " ").replace(",", ";").replace("'", " ")

        print(data)
        # Todo Add csv into database
        try:
            # Todo add each parameter to the db
            db.execute("INSERT INTO recipes VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", data[i]['id'], data[i]['name'], data[i]['ingredients'], data[i]['description'], data[i]['steps'], data[i]['minutes'], data[i]['tags'], data[i]['n_ingredients'], data[i]['n_steps'])
            print("DONE")
        except RuntimeError:
            pass


create_database()



# print(data)
# for ingredient in data['ingredients']:
#     print(ingredient)