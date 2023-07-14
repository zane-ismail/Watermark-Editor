import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")
students = []
houses = []
relationships = []


def create_house(houses, house, head):
     if house not in houses:
        houses.append[{"house": house, "head": head}]
        print(houses)




with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        name = row["student_name"]
        house = row["house"]
        head = row["head"]
        # print(house)
        create_house(houses, house, head)
        print(houses)

        # rows = db.execute("SELECT * FROM students")
        # db.execute(f"INSERT INTO students VALUES (student_name, {row['student_name']})");
        # if row['head'] not in row:
        #     db.execute(f"INSERT INTO students VALUES (house, {row['head']}");