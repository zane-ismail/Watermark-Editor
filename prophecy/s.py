import csv

with open('students.csv', newline='') as csvfile:
    s = csv.reader(csvfile)

    for student in s['student_name']:
        print(student)