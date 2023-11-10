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
    // make copies for comparison
    std::string currentWord = current->word;
    std::string incomingWord = incoming->word;
    to_lower(currentWord);
    to_lower(incomingWord);

    if (incomingWord > currentWord) return 1;
    else if (incomingWord < currentWord) return -1;
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
    int charIndex;
    for (int i = 0; i < NUM_SPECIAL_CHARS; ++i) {
        // determine if start, end is a special char
        charIndex = (word[0] == SPECIAL_CHARS[i]) ? 0 : -1;
        charIndex = (word[word.size() - 1] == SPECIAL_CHARS[i]) ? word.size() - 1 : charIndex;
        if (charIndex != -1) {
            word.replace(charIndex, 1, "");
            // restart
            i = -1;
        }
    }
}

void TextFile::insert_word(std::string& word, int& lineNum) {
    // update the current verse
    if (is_number(word)) { 
        lineNum = std::stoi(word); 
        return; 
    }

    auto hyphenIndex = word.find("-");
    if (hyphenIndex != -1 && hyphenIndex != 0 && hyphenIndex != word.size() - 1) {
        // split hyphenated words into 2 separate words
        // also works for en and em dashes 
        std::string word1 = word.substr(0, hyphenIndex);
        std::string word2 = word.substr(hyphenIndex, word.size() - hyphenIndex);
        insert_word(word1, lineNum);
        insert_word(word2, lineNum);
    }
    else {
        remove_special_chars(word);
        WordInfo* wordInfo = new WordInfo(word, lineNum);
        tree.insert(wordInfo, &compare, &on_duplicate);
    }
}


// add each word in the file to the tree
void TextFile::parse_into_tree() {
    std::fstream fin(filePath);
    if (!fin.is_open()) {
        std::cout << "FATAL: unable to open file" << std::endl;
        exit(-1);
    }

    std::string line;
    int lineNum = 0;
    while(std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) insert_word(word, lineNum);
    }
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
    std::fstream fin(filePath);    
    std::string line;
    while (std::getline(fin, line)) std::cout << line << "\n";
}