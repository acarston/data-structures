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
    FORM_PATH = './data/foo.csv'
    WORDS_PATH = './data/words.csv'
    WORDS_ALPHA_JSON = './data/words_alpha.json'
    WORDS_COUNT_JSON = './data/words_count.json'
    SENTIMENT_INFO_JSON = './data/sentiment_info.json'
    SENTIMENT_SUMMARY_JSON = './data/sentiment_summary.json'

    format_csv(FORM_PATH, WORDS_PATH)

    word_data = WordData(WORDS_PATH)
    word_data.dump(WORDS_ALPHA_JSON)
    word_data.plot_words('Word Frequencies by Alphabetical Order', './data/words_alpha.png')
    word_data.sort_by_count()
    word_data.dump(WORDS_COUNT_JSON)
    word_data.plot_words('Word Frequencies by Number of Occurences', './data/words_count.png')

    siaInfo = SiaData(FORM_PATH)
    siaInfo.dump_info(SENTIMENT_INFO_JSON)
    siaInfo.dump_summary(SENTIMENT_SUMMARY_JSON)
    siaInfo.plot_summary('./data/sentiment_summary.png')

if __name__ == "__main__":
    main()