import csv
from cs50 import SQL

db = SQL.("sqlite:///students.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        print(row["student_name"])
        db.execute("INSERT INTO students VALUES (student_name, row['student_name']");