import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")


def create_house(houses, house, head):
    count = 0
    for h in houses:
        if h["house"] == house:
            count += 1
    if count == 0:
        houses.append({"house": house, "head": head})

def create_students(students, name):
    students.append({"student_name": name})

def create_relationships(relationships, name, house):
    relationships.append({"student_name": name, "house": house})

students = []
houses = []
relationships = []


with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        name = row["student_name"]
        house = row["house"]
        head = row["head"]
        create_house(houses, house, head)
        create_students(students, name)
        create_relationships(relationships, name, house)
    print(houses, students, relationships)

        # rows = db.execute("SELECT * FROM students")
        # db.execute(f"INSERT INTO students VALUES (student_name, {row['student_name']})");
        # if row['head'] not in row:
        #     db.execute(f"INSERT INTO students VALUES (house, {row['head']}");