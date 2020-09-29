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
        print(f"{first}, {middle}, {last}, {birth}")

if __name__ == "__main__":
    main()