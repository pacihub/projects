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
#the dictreader reads in the csv file into memory as a dictionary. read abt reader vs. dictreader
        for row in csv_inmemory:
#iterate over the csv in memory and split the names, because they are not separated with commas
            namez = row['name'].split()  # "Harry Potter" becomes ["Harry", "Potter"]
            #split breaks strings into words ordered in a LIST, separated by comma.
            #=> since it is a list, namez[0] = Harry and namez[1] will be Potter
            first = namez[0]

#condition if length of namez = 3, to put middle one as namez[1], if they are less, then middle name will be NULL or None
#and essentially it will print only first and last name
            if len(namez) == 3:
                middle = namez[1]
            else:
                middle = None

            last = namez[-1]

            house = row["house"]
            birth = row["birth"]
#after namez I have [house] and [birth], which i can access with row["house"] and row["birth"]

#           print(row)

            db.execute("INSERT into students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
            print(row)
#executing commands directly into the db. naming the columns in brackets that I want to insert into. if I don't enter
#those columns in brackets at all, it will give me a mistake that i have 6 columns (one for ID). the ? are placeholders like %s in C.
#after the comma, first middle and last are where it will take values from. just like placeholder syntax in C

if __name__ == "__main__":
    main()



#with this program i have a csv that looks like this:
#Adelaide Murton,Slytherin,1982
#Adrian Pucey,Slytherin,1977
#and i have to load it into a database, but since names are not separated with commas, i have to separate with commas
#and put each name in a different column |first|middle|last. That's why i use split() function to parse the names
#and then a command to load directly in the database. Where i put a condition for middle name, if the names < 3
#=> put the middle one as None.