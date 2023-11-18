import sys
import os
import csv
import json
from textfile_wrapper import TextFile
from nltk.sentiment import SentimentIntensityAnalyzer
from numpy import mean
import matplotlib.pyplot as plt
import matplotlib.ticker as plticker

class WordData:
    def __init__(self, csv_filepath) -> None:
        try:
            with open(csv_filepath) as csvfile:
                reader = csv.reader(csvfile)
                self.data: list[tuple[str, list[str], int]] = [(row[0], row[1].split(";"), int(row[2])) for row in reader]
                self.__set_data_lists()

        except FileNotFoundError:
            print(f'Error: file {csv_filepath} not found')
            sys.exit(-1)
        except Exception as e:
            print(f'Error: {e}')
            sys.exit(-1)

    def __set_data_lists(self) -> None:
        self.words: list[str] = [pair[0] for pair in self.data]
        self.names: list[list[str]] = [pair[1] for pair in self.data]
        self.counts: list[int] = [pair[2] for pair in self.data]

    def sort_by_count(self) -> None:
        self.data = sorted(self.data, key=lambda pair: pair[2], reverse=True)
        self.__set_data_lists()

    def plot_words(self) -> None:
        fig, ax = plt.subplots()

        ax.bar(self.words, self.counts)
        ax.set_xlabel('Words', labelpad=20, fontsize='xx-large')
        ax.set_ylabel('Occurences', labelpad=20, fontsize='xx-large')
        loc = plticker.MultipleLocator(base=1)
        ax.yaxis.set_major_locator(loc)
        ax.set_title('Word Frequencies by Alphabetical Order', fontsize='xx-large')

        plt.show()

def main():
    os.chdir(os.path.dirname(__file__))
    
    sia = SentimentIntensityAnalyzer()
    sia_info: list[dict[str, str | float]] = []
    textfile = TextFile()
    with open('./data/foo.csv') as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            ps = sia.polarity_scores(row[1])
            sia_info.append({
                'name': row[0],
                'neg': ps['neg'],
                'neu': ps['neu'],
                'pos': ps['pos']
            })

            textfile.set_input(row[1], row[0])
            textfile.parse_into_tree()
        
    json.dump({
        'people': sia_info,
        'averages': {
            'neg': mean([block['neg'] for block in sia_info]),
            'neu': mean([block['neu'] for block in sia_info]),
            'pos': mean([block['pos'] for block in sia_info])
        }
    }, open('./data/sentiment.json', 'w'))

    textfile.print_words('./data/words.csv')
    word_data = WordData('./data/words.csv')
    word_data.plot_words()
    word_data.sort_by_count()
    word_data.plot_words()

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