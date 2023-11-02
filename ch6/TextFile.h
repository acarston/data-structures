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
		const std::string PARSED_FILE_PATH = "./verses.txt";
		int lineNum = 0;
		const static int NUM_SPECIAL_CHARS = 12;
		const std::string SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {"\"", ";", ",", ".", "?", "!", ":", "\n", "(", ")", "[", "]"};
		
		static void to_lower(std::string& str);
		bool is_number(const std::string& str);

		static int compare(WordInfo*& current, WordInfo*& incoming);
		static void on_duplicate(WordInfo*& current, WordInfo*& incoming);
		static void visit(WordInfo*& info);

		void remove_special_chars(std::string& word);
		void parse_verses();

	public:
		TextFile(const std::string& filePath): filePath(filePath) {};

		void parse_into_tree();
		void print_words();
};

#endif