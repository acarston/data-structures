#include "TextFile.h"

std::string& TextFile::get_word(WordInfo* info) {
    return info->word;
}

// add the incoming line number to a node already in the tree
// upon creation in parse_into_tree, WordInfo has exactly 1 element in its lines list
// so attempting to insert should yank this element and delete the created WordInfo
void TextFile::on_duplicate(WordInfo* current, WordInfo* incoming) {
    current->lines.push_back(incoming->lines.front());
    delete incoming;
    incoming = nullptr;
}

// specify the output upon traversal visit
void TextFile::visit(WordInfo* info) {
    std::cout << info->word << ": ";
    for (auto it = info->lines.begin(); it != info->lines.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}


void TextFile::remove_special_chars(std::string& word) {
    for (int i = 0; i < NUM_SPECIAL_CHARS; ++i) {
        if (word.find(SPECIAL_CHARS[i]) != -1) {
            word.replace(word.find(SPECIAL_CHARS[i]), 1, "");
        }
    }
}

// sourced from https://stackoverflow.com/questions/4654636/
bool TextFile::is_number(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

// separate verses into lines in a text file
void TextFile::parse_verses() {
    std::ofstream fout(PARSED_FILE_PATH);
    std::fstream fin(filePath);
    if (!fin.is_open()) {
        std::cout << "FATAL: unable to open file" << std::endl;
        exit(-1);
    }
    
    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string word;
        
        while (iss >> word) {
            if (is_number(word)) fout << "\n";
            else fout << word << " ";
        }
    }
}


// add each word in the parsed file to the tree
void TextFile::parse_into_tree() {
    parse_verses();

    std::fstream fin(PARSED_FILE_PATH);
    std::string line;
    while(std::getline(fin, line)) {
        lineNum++;

        std::istringstream iss(line);
        std::string word;
        WordInfo* wordInfo;

        while (iss >> word) {
            remove_special_chars(word);
            wordInfo = new WordInfo(word, lineNum);
            tree.insert(wordInfo, &get_word, &on_duplicate);
        }
    }
}

// output the words alphabetically
void TextFile::print_words() {
    tree.traverse_inorder(&visit);
    std::cout << std::endl;
}
