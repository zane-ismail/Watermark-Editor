import csv

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for student in reader['student_name']:
        print(student)