#include "TextFile.h"

std::string& TextFile::get_word(WordInfo* info) {
    return info->word;
}

void TextFile::on_duplicate(WordInfo* current, WordInfo* incoming) {
    current->verses.push_back(incoming->verses.front());
    delete incoming;
    incoming = nullptr;
}

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


void TextFile::parse_into_tree() {
    std::fstream fin(filePath);
    if (!fin.is_open()) {
        std::cout << "FATAL: unable to open file" << std::endl;
        exit(0);
    }

    std::string line;
    while(std::getline(fin, line)) {
        lineNum++;

        std::istringstream iss(line);
        std::string word;
        WordInfo* wordInfo;

        iss >> word;
        if (lineNum == 1) {
            remove_special_chars(word);
            iss >> word;
            wordInfo = new WordInfo(word, lineNum);
            tree.set_root(wordInfo);
        }
        while (iss >> word) {
            remove_special_chars(word);
            wordInfo = new WordInfo(word, lineNum);
            tree.insert(wordInfo, &get_word, &on_duplicate);
        }
    }
}

void TextFile::print_words() {
    tree.traverse_inorder(&visit);
}
