import os
import csv
from textfile_wrapper import TextFile
from word_data import WordData
from sia_data import SiaData

# translate raw form data to WordData format
def format_csv(form_path, out_path: str) -> None:
    textfile = TextFile()
    with open(form_path) as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            textfile.set_input(row[1], row[0])
            textfile.parse_into_tree()

    textfile.print_words(out_path)

def main():
    os.chdir(os.path.dirname(__file__))
    FORM_PATH: str = './data/foo.csv'
    WORDS_PATH: str = './data/words.csv'
    WORDS_ALPHA_JSON: str = './data/words_alpha.json'
    WORDS_COUNT_JSON: str = './data/words_count.json'
    SENTIMENT_JSON: str = './data/sentiment.json'

    format_csv(FORM_PATH, WORDS_PATH)

    word_data = WordData(WORDS_PATH)

    word_data.dump(WORDS_ALPHA_JSON)
    word_data.plot_words('Word Frequencies by Alphabetical Order', './data/words_alpha.png')
    word_data.sort_by_count()
    word_data.dump(WORDS_COUNT_JSON)
    word_data.plot_words('Word Frequencies by Number of Occurences', './data/words_count.png')

    siaInfo = SiaData(FORM_PATH)
    siaInfo.dump(SENTIMENT_JSON)

if __name__ == "__main__":
    main()