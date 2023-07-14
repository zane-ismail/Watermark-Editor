import csv
from cs50 import SQL

db = SQL("sqlite:///roster.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        # print(row["student_name"])

        rows = db.execute("SELECT * FROM students")
        for r in rows:
            insert = db.execute(f"INSERT INTO students VALUES (student_name, {row['student_name']}")
            print(r)
        # if row['head'] not in row:
        #     db.execute(f"INSERT INTO students VALUES (house, {row['head']}");