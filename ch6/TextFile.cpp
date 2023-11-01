#include "TextFile.h"

std::string& TextFile::get_word(WordInfo* info) {
    return info->word;
}

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
            fout << word << " ";
        }
    }
}


void TextFile::parse_into_tree() {
    parse_verses();

    std::fstream fin(PARSED_FILE_PATH);
    std::string line;
    while(std::getline(fin, line)) {
        lineNum++;

        std::istringstream iss(line);
        std::string word;
        WordInfo* wordInfo;

        // ignore the first word (a verse number)
        iss >> word;
        while (iss >> word) {
            remove_special_chars(word);
            wordInfo = new WordInfo(word, lineNum);
            tree.insert(wordInfo, &get_word, &on_duplicate);
        }
    }
}

void TextFile::print_words() {
    tree.traverse_inorder(&visit);
    std::cout << std::endl;
}
