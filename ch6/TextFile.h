#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "BSTree.h"

class TextFile {
	private:
		struct WordInfo {
			std::string word;
			std::list<int> lines;

			WordInfo(std::string word, int line) {
				this->word = word;
				lines.push_back(line);
			};
		};

		BSTree<WordInfo*> tree;
		std::string filePath;
		int lineNum = 0;
		const static int NUM_SPECIAL_CHARS = 12;
		const std::string SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {"\"", ";", ",", ".", "?", "!", ":", "\n", "(", ")", "[", "]"};
		
		static std::string& get_word(WordInfo* info);
		static void on_duplicate(WordInfo* current, WordInfo* incoming);
		static void visit(WordInfo* info);
		void remove_special_chars(std::string& word);

	public:
		TextFile(const std::string& filePath): filePath(filePath) {};

		void parse_into_tree();
		void print_words();
};

#endif