#ifndef TEXTFILE_H
#define TEXTFILE_H

#ifdef TEXTFILE_EXPORTS
#define TEXTFILE_API __declspec(dllexport)
#else
#define TEXTFILE_API __declspec(dllimport)
#endif

#include <list>
#include <iostream>
#include <sstream>
#include <unordered_set>

#include "BSTree.h"

class TextFile {
private:
	struct WordInfo {
		std::string word;
		std::list<int> lines;
		// int iteration = 0;

		WordInfo(std::string word, int iteration) {
			this->word = word;
			lines.push_back(iteration);
			// this->iteration = iteration;
		};
	};

	BSTree<WordInfo*> tree;
	std::string in;
	int iteration = 0;
	const static int NUM_SPECIAL_CHARS = 15;
	const std::unordered_set<char> SPECIAL_CHARS{ ',', '.', '\"', '\'', '?', ';', ':', '!', '-', '(', ')', '[', ']', '\n' };
	const std::unordered_set<std::string> THROW_WORDS{ "the", "be", "to", "of", "and", "a", "in", "that", "have", "i", "it",
		"for", "not", "on", "with", "he", "as", "you", "do", "at", "this", "but", "his", "by", "from", "they", "we", "say",
		"her", "she", "or", "an", "will", "my", "all", "would", "there", "their", "what", "so", "if", "about", "who", "get",
		"which", "go", "me", "when", "make", "just", "him", "into", "your" };

	static void to_lower(std::string& str);
	bool is_number(const std::string& str) const;

	static int compare(WordInfo*& current, WordInfo*& incoming);
	static void on_duplicate(WordInfo*& current, WordInfo*& incoming);
	static void to_console(WordInfo*& info);
	static void to_file(WordInfo*& info, std::ofstream& fout);

	void remove_special_chars(std::string& word) const;
	void insert_word(std::string& word);

public:
	TextFile(const std::string& in) : in(in) {};

	void set_input(const std::string& in);
	void parse_into_tree();
	void print_words();
	void print_words(const std::string& filePath);
	void print_input() const;
};

extern "C" {
	TEXTFILE_API TextFile* CTextFile(const wchar_t* cstr) {
		std::wstring ws(cstr);
		std::string str(ws.begin(), ws.end());
		return new TextFile(str);
	};
	TEXTFILE_API void c_set_input(TextFile* textFile, const wchar_t* cstr) {
		std::wstring ws(cstr);
		std::string str(ws.begin(), ws.end());
		textFile->set_input(str);
	};
	TEXTFILE_API void c_print_words(TextFile* textFile, const wchar_t* filePath) {
		std::wstring ws(filePath);
		std::string filePathStr(ws.begin(), ws.end());
		textFile->print_words(filePathStr);
	};
	TEXTFILE_API void c_parse_into_tree(TextFile* textFile) {
		textFile->parse_into_tree();
	};
}

#endif