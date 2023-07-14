import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        print(row["student_name"])

        print(row["student_name"])
        db.execute("SELECT * FROM students");
        db.execute(f"INSERT INTO students VALUES (student_name, {row['student_name']}");
        if row['head'] not in row:
            db.execute(f"INSERT INTO students VALUES (house, {row['head']}");