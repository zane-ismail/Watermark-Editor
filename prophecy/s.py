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

for student in students:
    print(student)
#     db.execute("INSERT INTO students (student_name) VALUES (?)", student["student_name"])

for rel in relationships:
    print(rel)
    # db.execute("INSERT INTO assignments (student_id, house_id) VALUES (?,?)", rel["student_name"], rel["house"])

for house in houses:
    print(house)
    db.execute("INSERT INTO houses (house, head) VALUES (?,?)", house["house"], head["head"])