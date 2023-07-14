import csv

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    for row in reader:
        for student in row["student_name"]:
            print(student)