import csv

with open('students.csv', newline='') as csvfile:
    reader = csv.DictReader(csvfile)

    for student in s['student_name']:
        print(student)