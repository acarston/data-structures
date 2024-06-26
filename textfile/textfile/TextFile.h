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
		std::list<std::string> people;
		int numPeople = 0;
		int count = 1;

		WordInfo(std::string word, std::string person) {
			this->word = word;
			people.push_back(person);
		};
	};

	BSTree<WordInfo*> tree;
	std::string in = "";
	std::string person = "";
	const static int NUM_SPECIAL_CHARS = 15;
	const std::unordered_set<char> SPLIT_CHARS{ '/', '\\', '-' };
	const std::unordered_set<char> PUNCTUATION{ '.', ',', '?', ';', ':', '!', '-', '(', ')', '[', ']' };
	const std::unordered_set<char> SPECIAL_CHARS{ ',', '.', '\"', '\'', '?', ';', ':', '!', '-', '(', ')', '[', ']', '\n', ' ', '&', '+' };
	const std::unordered_set<std::string> THROW_WORDS{ "the", "be", "to", "of", "and", "a", "in", "that", "have", "i", "it",
		"for", "not" "on", "with", "he", "as", "you", "do", "at", "this", "but", "his", "by", "from", "they", "we", "her", "does"
		"she", "or", "an", "will", "my", "would", "there", "their", "what", "so", "if", "about", "who", "get", "than", "which", 
		"go", "me", "when", "him", "into", "your", "am", "are", "been", "being", "doing", "etc", "is", "it's", "then", "our" };
	const std::unordered_set<std::string> THROW_PHRASES{ "the", "be", "to", "of", "and", "a", "in", "that", "have", "i", "it",
		"for", "on", "with", "he", "as", "you", "do", "at", "this", "but", "his", "by", "from", "they", "we", "her", "she", 
		"or", "an", "my", "would", "there", "their", "what", "so", "if", "about", "who", "get", "than", "which", "go", "me", 
		"when", "him", "into", "your", "am", "are", "been", "being", "doing", "etc", "is", "it's", "then", "our", "does" };

	static void to_lower(std::string& str);
	bool is_number(const std::string& str) const;

	static int compare(WordInfo*& current, WordInfo*& incoming);
	static void on_duplicate(WordInfo*& current, WordInfo*& incoming);
	static void to_console(WordInfo*& info);
	static void to_file(WordInfo*& info, std::ofstream& fout);

	bool has_punctuation(const std::string& word) const;
	void remove_special_chars(std::string& word) const;
	void insert_word(std::string& word);
	void insert_word(std::string& word1, std::string& word2);

public:
	TextFile() {}
	TextFile(const std::string& in) : in(in) {}

	void set_input(const std::string& in, const std::string& person);
	void parse_into_tree(bool phrases = false);
	void print_words();
	void print_words(const std::string& filePath);
	void print_input() const;
};

extern "C" {
	TEXTFILE_API TextFile* CTextFileDefault() {
		return new TextFile();
	};
	TEXTFILE_API TextFile* CTextFile(const wchar_t* cstr) {
		std::wstring ws(cstr);
		std::string str(ws.begin(), ws.end());
		return new TextFile(str);
	};
	TEXTFILE_API void c_set_input(TextFile* textFile, const wchar_t* in, const wchar_t* person) {
		std::wstring wInStr(in);
		std::string inStr(wInStr.begin(), wInStr.end());
		std::wstring wPersonStr(person);
		std::string personStr(wPersonStr.begin(), wPersonStr.end());
		textFile->set_input(inStr, personStr);
	};
	TEXTFILE_API void c_print_words(TextFile* textFile, const wchar_t* filePath) {
		std::wstring ws(filePath);
		std::string filePathStr(ws.begin(), ws.end());
		textFile->print_words(filePathStr);
	};
	TEXTFILE_API void c_parse_into_tree(TextFile* textFile, bool phrases) {
		textFile->parse_into_tree(phrases);
	};
}

#endif