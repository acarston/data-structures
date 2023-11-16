import os
import csv

def main():
    os.chdir(os.path.dirname(__file__))

    with open('./foo.csv', newline='') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            cell_value = row[1]
            print(cell_value)


if __name__ == "__main__":
    main()