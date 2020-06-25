import csv
import re
from sys import argv,exit

#checks maximum number of consecutive times a substring appears in string
def maxcount_in_string(string, substring):
    maximum = 0
    pattern = substring
    temp = pattern
    while pattern in string:
        maximum += 1
        pattern += temp

    return maximum
#the program will open argv[1] as csv file(this is where FBI database is)
#and argv[2] as a text file, this is the sequence we need to compare against the database

def main():
    if len(argv) != 3:
       print("Usage: python dna.py data.csv sequence.txt")
       exit(1)
    
    with open(argv[1]) as csv_file:

        csv_inmemory = csv.reader(csv_file)  #reader method gives every single line of the file

        csv_goren_red = next(csv_inmemory)[1:]  
#since header is Name AGAT TRGA, etc, I am stripping it of name by [1:]
#so only sequences remain. next() method gives me the next row e.g. Vanessa 28, 3, 15, but without Vanessa. just numbers
#   print(goren_red)

#when using with, it opens the file and then closes automatically when no longer needed
        with open(argv[2]) as txt_file:
            long_dnasequence = txt_file.read()

#we are reading the long sequence in the text file in memory (with read method) in a variable long_dnasequence

#create an empty list(array) obtained_sequence_list[]
#then iterate over the header line with sequence names. then every STR sequence I feed in my function
#maxcount_in_string. it calculates max No consecutive times AGAT appears in the string ->spits out a number
#then i append the number to that empy list via append method
            obtained_sequence_list = []
            for sequence in csv_goren_red:
                obtained_sequence_list.append(maxcount_in_string(long_dnasequence, sequence))   


#print check what array I have created 
#            print(obtained_sequence_list)

        for row in csv_inmemory:
            person = row[0]
            #csv_values = [ int(value) for value in row[1:] ] short handed version
            csv_values_fbi = []
            for value in row[1:]:
                value = int(value)  #convert all values to integers
                csv_values_fbi.append(value) #appends every number to the empty list csv_values_fbi
            #print(csv_values)
            if csv_values_fbi == obtained_sequence_list:    #compare what i've obtained to database 
                print(person)
                return
        print("No match.")

#if i don't use return, then it'll keep iterating after it finds a match and it will print both the match and No match          

#standard way of calling the main function

if __name__ == "__main__":
    main()