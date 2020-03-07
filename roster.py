from cs50 import SQL
from sys import argv, exit

# check command line arguments
if len(argv) != 2:
    print("Usage: python roster.py students.db")
    exit(1)

# Do SQL SELECT
db = SQL("sqlite:///students.db")
roster = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", argv[1])

# check for middle name and print
for student in roster:
    if student['middle'] == None:
        print(student['first'], student['last'] + ", born", str(student['birth']))
    else:
        print(student['first'], student['middle'], student['last'] + ", born", str(student['birth']))

