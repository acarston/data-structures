import os
import csv
import json
from textfile_wrapper import TextFile
from nltk.sentiment import SentimentIntensityAnalyzer
from numpy import mean
from word_data import WordData

class WordInfo:
    def __init__(self, form_path: str) -> None:
        self.form_path = form_path

    def format_csv(in_path: str, out_path: str) -> None:
        textfile = TextFile()
        with open(in_path) as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                textfile.set_input(row[1], row[0])
                textfile.parse_into_tree()

        textfile.print_words(out_path)

    # function author: TimothyZink
    def dump(self, in_path: str, out_path: str):
        with open(in_path) as csvfile:
            reader = csv.reader(csvfile)
            data: list[dict[str, str | list[str] | int]] = [{
                "word": row[0],
                "people": row[1].split(";"),
                "count": row[2]
            } for row in reader]

            json.dump(data, open(out_path, "w"))  

class SiaInfo:
    def __init__(self, form_path: str) -> None:
        self.form_path = form_path
        self.__set_sentiment_info()

    def __set_sentiment_info(self) -> None:
        sia = SentimentIntensityAnalyzer()
        self.sia_info: list[dict[str, str | float]] = []
        with open (self.form_path) as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                ps = sia.polarity_scores(row[1])
                self.sia_info.append({
                    'name': row[0],
                    'neg': ps['neg'],
                    'neu': ps['neu'],
                    'pos': ps['pos']
                })
    
    def dump(self, filepath: str):
        json.dump({
            'people': self.sia_info,
            'averages': {
                'neg': mean([block['neg'] for block in self.sia_info]),
                'neu': mean([block['neu'] for block in self.sia_info]),
                'pos': mean([block['pos'] for block in self.sia_info])
            }
        }, open(filepath, 'w'))

def main():
    os.chdir(os.path.dirname(__file__))



    word_data = WordData('./data/words.csv')
    word_data.plot_words('Word Frequencies by Alphabetical Order', './data/words_alpha.png')
    word_data.sort_by_count()
    word_data.plot_words('Word Frequencies by Number of Occurences', './data/words_count.png')

    with open('./data/out.csv') as csvfile:
        reader = csv.reader(csvfile)
        data: list[dict[str, str | list[str] | int]] = [{
            "word": row[0],
            "people": row[1].split(";"),
            "count": row[2]
        } for row in reader]

        json.dump(data, open("./data/words.json", "w"))  

if __name__ == "__main__":
    main()