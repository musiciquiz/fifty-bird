from cs50 import SQL
import csv
from sys import argv, exit

# check for command line arguments
if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit(1)

# create database
open(f"students.db", "w").close()
db = SQL("sqlite:///students.db")

# create tables
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth NUMERIC)")

# open csv file
with open(argv[1], "r") as file:

    # create DictReader
    reader = csv.DictReader(file)
    for row in reader:
        # parse name into first middle last
        row['name'] = row['name'].split()
        if len(row['name']) == 2:
            row['name'].insert(1, None)

        # insert student
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", row['name'][0],
                   row['name'][1], row['name'][2], row['house'], int(row['birth']))
