#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../utils/BSTree.h"

class TextFile {
	public:
		struct WordInfo {
			std::string word;
			std::list<int> lines;

			WordInfo(std::string word, int line) {
				this->word = word;
				lines.push_back(line);
			};
		};
	private:
		BSTree<WordInfo*> tree;
		std::string filePath;
		const static int NUM_SPECIAL_CHARS = 15;
		const char SPECIAL_CHARS[NUM_SPECIAL_CHARS] = {',', '.', '\"', '\'', '?', ';', ':', '!', '-', '(', ')', '[', ']', '\n', ' '};
		
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
		void PrintStructure(void (*func)(WordInfo*, int, int, std::vector<int>*)) { tree.PrintStructure(func);}
};

#endif