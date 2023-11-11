#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <list>
#include <iostream>
#include <sstream>
#include <unordered_set>

#include "../utils/BSTree.h"

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
		const static int NUM_SPECIAL_CHARS = 15;
		// const char SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {',', '.', '\"', '\'', '?', ';', ':', '!', '-', '(', ')', '[', ']', '\n', ' '};
		const std::unordered_set<char> SPECIAL_CHARS{',', '.', '\"', '\'', '?', ';', ':', '!', '-', '(', ')', '[', ']', '\n'};
		const std::unordered_set<std::string> THROW_WORDS{"the"};
		
		static void to_lower(std::string& str);
		bool is_number(const std::string& str) const;

		static int compare(WordInfo*& current, WordInfo*& incoming);
		static void on_duplicate(WordInfo*& current, WordInfo*& incoming);
		static void to_console(WordInfo*& info);
		static void to_file(WordInfo*& info, std::ofstream& fout);

		void remove_special_chars(std::string& word) const;
		void insert_word(std::string& word, int& lineNum);

	public:
		TextFile(const std::string& filePath): filePath(filePath) {};

		void parse_into_tree();
		void print_words();
		void print_words(const std::string& filePath);
		void print_input() const;
};

#endif