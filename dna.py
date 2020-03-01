from sys import argv, exit
import csv

# check command line arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# open csv file and covert to dictionary
csvfile = open(argv[1], "r")
database = csv.DictReader(csvfile)

# get list of keys of dict
keys = database.fieldnames
# remove name from list to get list of STR to compare
STR = keys[1:]
# empty dictionary with these keys
STRdict = {key: None for key in STR}

# open text file
txtfile = open(argv[2], "r")
seq = txtfile.read()

# compute longest run of consecutive STR
# for each STR compare and count consecutive
for i in range(len(STR)):
    counter = 0
    max = 0
    iter = 0
    STRlen = len(STR[i])
    while(iter < len(seq)):
        # start counting consecutive(if match jump forward)
        if(seq[iter:iter + STRlen] == STR[i]):
            counter += 1
            iter += STRlen
            if (counter > max):
                max = counter
        else:# no match - just go to next value and check there
            counter = 0
            iter += 1
    # populate the dict with consecutive max value
    STRdict[STR[i]] = max

# compare sequence with database
for row in database:
    iter = 0
    while(True):
        if(STRdict[STR[iter]] != int(row[STR[iter]])):
            break
        iter += 1
        if(iter == len(STR)-1):
            print(row['name'])
            exit(0)

# Else no match
print("No Match")