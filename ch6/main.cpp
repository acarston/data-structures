#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../utils/BSTree.h"

struct WordInfo {
	std::string word;
	std::list<int> verses;

	WordInfo(std::string word, int verse) {
		this->word = word;
		verses.push_back(verse);
	};
};

// std::string& get_word(WordInfo*);
// void on_duplicate(WordInfo*);

class TextFile {
	private:
		std::string filePath;
		int lineNum = 0;
		const static int NUM_SPECIAL_CHARS = 8;
		const std::string SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {"\"", ";", ",", ".", "?", "!", ":", "\n"};

		static std::string& get_word(WordInfo* info) {
			return info->word;
		};
		
		static void on_duplicate(WordInfo* current, WordInfo* incoming) {
			current->verses.push_back(incoming->verses.front());
			delete incoming;
			incoming = nullptr;
		};

		void remove_special_chars(std::string& word) {
			for (int i = 0; i < NUM_SPECIAL_CHARS; ++i) {
				if (word.find(SPECIAL_CHARS[i]) != -1) {
					word.replace(word.find(SPECIAL_CHARS[i]), 1, "");
				}
			}
		};
		
	public:
		TextFile(const std::string& filePath): filePath(filePath) {};

		void parse_into_tree() {
			std::fstream fin(filePath);
			if (!fin.is_open()) {
				std::cout << "FATAL: unable to open file" << std::endl;
				exit(0);
			}

			BSTree<WordInfo*> tree;

			std::string line;
			while(std::getline(fin, line)) {
				lineNum++;

				std::istringstream iss(line);
				std::string word;
				WordInfo* wordInfo;

				iss >> word;
				if (lineNum == 1) {
					remove_special_chars(word);
					iss >> word;
					wordInfo = new WordInfo(word, lineNum);
					tree.set_root(wordInfo);
				}
				while (iss >> word) {
					remove_special_chars(word);
					wordInfo = new WordInfo(word, lineNum);
					tree.insert(wordInfo, &get_word, &on_duplicate);
				}
			}
		};
};

std::string& get_word(WordInfo* info) {
	return info->word;
};

static int verse = 0;
void on_duplicate(WordInfo* current, WordInfo* incoming) {
	current->verses.push_back(incoming->verses.front());
};
		

int main(int argc, char* argv[]) {
	// std::string word = "hello";
	// WordInfo* wordInfo = new WordInfo(word, 1);

	// BSTree<WordInfo*> tree(wordInfo);

	// std::string word2 = "world";
	// WordInfo* wordInfo2 = new WordInfo(word2, 2);

	// tree.insert(wordInfo2, &get_word, &on_duplicate);
	// wordInfo2 = new WordInfo(word2, 3);

	// tree.insert(wordInfo2, &get_word, &on_duplicate);

	TextFile f(argv[1]);
	f.parse_into_tree();

	return 0;
};