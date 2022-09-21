import csv
import sys


def main():
    if len(sys.argv) < 3:
        print("Usage:", "python dna.py data.csv sequence.txt")
        exit(1)

    rows = []
    STRs = []
    STRs_count = []
    dna = ""

    with open(sys.argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            rows.append(row)

    STRs = list(rows[0].keys())[1:]

    f = open(sys.argv[2], "r")
    dna = f.read()
    f.close()

    for i in STRs:
        STRs_count.append(
            next(r-1 for r in range(1, len(dna)+1) if i*r not in dna))

    for i in range(len(rows)):
        check = True
        for j in range(len(STRs)):
            if int(rows[i][STRs[j]]) != STRs_count[j]:
                check = False
                break
        if check:
            print(rows[i]["name"])
            break
    if not check:
        print("No match")

    return


main()