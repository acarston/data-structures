import csv
import sys
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

    def plot_words(self, title: str, filePath: str) -> None:
        fig, ax = plt.subplots(figsize=(8, 5))

        ax.bar(self.words, self.counts)
        ax.set_xlabel('Words')
        ax.set_xticks(range(len(self.words)), labels=self.words, rotation='vertical')
        ax.set_ylabel('Occurences')
        loc = plticker.MultipleLocator(base=1)
        ax.yaxis.set_major_locator(loc)
        ax.set_title(title)

        plt.savefig(filePath, dpi=600, bbox_inches='tight')