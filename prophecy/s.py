import csv

with open('students.csv', newline='') as csvfile:
    s = csv.reader(csvfile, delimiter=' ', quotechar='|')