#include "pch.h"
#include "TextFile.h"

void TextFile::to_lower(std::string& str) {
    for (int i = 0; i < str.size(); ++i) {
        str[i] = tolower(str[i]);
    }
}

// sourced from https://stackoverflow.com/questions/4654636/
bool TextFile::is_number(const std::string& str) const {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}


int TextFile::compare(WordInfo*& current, WordInfo*& incoming) {
    if (incoming->word > current->word) return 1;
    else if (incoming->word < current->word) return -1;
    else return 0;
}

// add the incoming line number to a node already in the tree
// upon creation in parse_into_tree, WordInfo has exactly 1 element in its lines list
// so attempting to insert should yank this element and delete the created WordInfo
void TextFile::on_duplicate(WordInfo*& current, WordInfo*& incoming) {
    current->lines.push_back(incoming->lines.front());
    delete incoming;
    incoming = nullptr;
}

// specify the output upon traversal visit
void TextFile::to_console(WordInfo*& info) {
    std::cout << info->word << ": ";
    for (auto it = info->lines.begin(); it != info->lines.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}

void TextFile::to_file(WordInfo*& info, std::ofstream& fout) {
    fout << info->word + ": ";
    for (auto it = info->lines.begin(); it != info->lines.end(); ++it) {
        fout << *it << " ";
    }
    fout << "\n";
}


void TextFile::remove_special_chars(std::string& word) const {
    while (true) {
        if (SPECIAL_CHARS.find(word[0]) != SPECIAL_CHARS.end()) word.replace(0, 1, "");
        else if (SPECIAL_CHARS.find(word[word.size() - 1]) != SPECIAL_CHARS.end()) word.replace(word.size() - 1, 1, "");
        else break;
    }
}

void TextFile::insert_word(std::string& word, int& lineNum) {
    // update the current verse
    if (is_number(word)) {
        lineNum = std::stoi(word);
        return;
    }

    to_lower(word);
    remove_special_chars(word);

    if (THROW_WORDS.find(word) != THROW_WORDS.end()) return;

    WordInfo* wordInfo = new WordInfo(word, lineNum);
    tree.insert(wordInfo, &compare, &on_duplicate);
}


void TextFile::set_input(const std::string& in) {
    this->in = in;
}

// add each word in the file to the tree
void TextFile::parse_into_tree() {
    std::istringstream iss(this->in);
    int lineNum = 0;
    std::string word;
    while (iss >> word) insert_word(word, lineNum);
}

// output the words alphabetically
void TextFile::print_words() {
    tree.traverse_inorder(&to_console);
    std::cout << std::endl;
}

void TextFile::print_words(const std::string& filePath) {
    tree.traverse_inorder(&to_file, filePath);
}

void TextFile::print_input() const {
    std::cout << in << std::endl;
}