# Librarys
import csv
import sys


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    STRs = []

    # get STRs (works)
    with open(sys.argv[1], "r") as data:
        data_reader = csv.reader(data)
        for row in data_reader:
            for i in range(1, len(row)):
                if row[0] == 'name':
                    STRs.append(row[i])
    
    # Consecutive Repeats list
    CRs = []

    # Count sequence STRs
    for i in range(len(STRs)):
        consecutive_repeats = count(STRs[i])
        CRs.append(consecutive_repeats)
    
    # Check for match
    with open(sys.argv[1], "r") as data:
        data_reader = csv.reader(data)
        match_check = False
        for row in data_reader:
            check = 0
            if row[0] != 'name':
                for i in range(1, len(row)):
                    if int(row[i]) == int(CRs[i - 1]):
                        check += 1
                # Check if a match
                if check == (len(row) - 1):
                    print(row[0])
                    match_check = True
                    break
        # Check for match
        if match_check == False:
            print("No match")


def count(STR):
    with open(sys.argv[2], "r") as sequences:
        sequence_reader = csv.reader(sequences)
        No1 = 0
        No2 = 0
        for row in sequence_reader:
            sequence = row[0]
            for i in range(len(sequence)):
                if STR == sequence[i:i + len(STR)]:
                    for x in range(i, len(sequence), len(STR)):
                        if STR == sequence[x:x + len(STR)]:
                            No2 += 1
                        else:
                            if No2 > No1:
                                No1 = No2
                            No2 = 0
                            break
        return No1


main()
