import os
import csv
import json
from textfile_wrapper import TextFile
from typing import Any

def main():
    os.chdir(os.path.dirname(__file__))

    textFile = TextFile()
    with open('./data/foo.csv') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            textFile.set_input(row[1], row[0])
            textFile.parse_into_tree()
        textFile.print_words('./data/out.csv')
    
    #json dumping by Timothy Zink
    with open('./data/out.csv') as csvfile:
        reader = csv.reader(csvfile)
        data: list[dict[str, str | list[str] | int]] = [{
            "word": row[0],
            "people": row[1].split(";"),
            "count": row[2]
        } for row in reader]

        json.dump(data, open("./data/data.json", "w"))

if __name__ == "__main__":
    main()