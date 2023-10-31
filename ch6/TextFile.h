#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../utils/BSTree.h"

class TextFile {
	private:
		std::string filePath;
		int lineNum = 0;
		const static int NUM_SPECIAL_CHARS = 8;
		const std::string SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {"\"", ";", ",", ".", "?", "!", ":", "\n"};
		
		struct WordInfo {
			std::string word;
			std::list<int> verses;

			WordInfo(std::string word, int verse) {
				this->word = word;
				verses.push_back(verse);
			};
		};
		
		static std::string& get_word(WordInfo* info);
		static void on_duplicate(WordInfo* current, WordInfo* incoming);
		void remove_special_chars(std::string& word);

	public:
		TextFile(const std::string& filePath): filePath(filePath) {};

		void parse_into_tree();
};

#endif