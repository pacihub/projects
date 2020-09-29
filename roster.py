# TODO
import csv
import re
from sys import argv,exit
from cs50 import SQL

def main():
    if len(argv) != 2:
       print("Usage: error")
       exit(1)

    db = SQL("sqlite:///students.db")

    query_house = argv[1]

    rows = db.execute("SELECT * from students WHERE house = ? ORDER BY last, first, birth", query_house)
    for row in rows:
        first, middle, last, birth = row['first'], row["middle"], row["last"], row["birth"]
        print(f"{first} {middle + ' ' if middle else ''}{last}, born {birth}")

if __name__ == "__main__":
    main()

#i have to query the database that I just imported into, to give me names and birth year of students living in a particular
#house. The query house is in argv, i type it.
#so for every row iterate and define the values again for first, middle, last, birth
#then I print with condition. {middle + ' ' if middle else ''} this read as:
#print middle and space if there is middle, ELSE just print space.
