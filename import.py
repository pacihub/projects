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
#the variable 'db' will store the SQLite file for us


    with open(argv[1]) as csv_file:
        csv_inmemory = csv.DictReader(csv_file)
        for row in csv_inmemory:
            namez = row['name'].split()
            first = namez[0]
            
            if len(namez) == 3:
                middle = namez[1]
            else:
                middle = None
            
            last = namez[-1]
            
            house = row['house']
            birth = row['birth']
            
            print(row)

            db.execute("INSERT into students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
        
print("done importing")
  
if __name__ == "__main__":
    main()
