from nltk.sentiment import SentimentIntensityAnalyzer
import csv
import json
from numpy import mean

class SiaData:
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
    
    def dump(self, out_path: str):
        json.dump({
            'people': self.sia_info,
            'averages': {
                'neg': mean([block['neg'] for block in self.sia_info]),
                'neu': mean([block['neu'] for block in self.sia_info]),
                'pos': mean([block['pos'] for block in self.sia_info])
            }
        }, open(out_path, 'w'))