import os
import csv
import json
from textfile_wrapper import TextFile
from nltk.sentiment import SentimentIntensityAnalyzer
from numpy import mean
from word_data import WordData

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