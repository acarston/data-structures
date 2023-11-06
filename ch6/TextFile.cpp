#include "TextFile.h"

void TextFile::to_lower(std::string& str) {
    for (int i = 0; i < str.size(); ++i) {
        str[i] = tolower(str[i]);
    }
}

// sourced from https://stackoverflow.com/questions/4654636/
bool TextFile::is_number(const std::string& str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}


int TextFile::compare(WordInfo*& current, WordInfo*& incoming) {
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
void TextFile::visit(WordInfo*& info) {
    std::cout << info->word << ": ";
    for (auto it = info->lines.begin(); it != info->lines.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}


void TextFile::remove_special_chars(std::string& word) {
    std::size_t charIndex;
    for (int i = 0; i < NUM_SPECIAL_CHARS; ++i) {
        charIndex = word.find(SPECIAL_CHARS[i]);
        if (charIndex != -1) {
            word.replace(charIndex, 1, "");
        }
    }

    // remove quotes while preserving singular possessives
    charIndex = word.find("'");
    if (charIndex == 0 || charIndex == word.size() - 1) {
        word.replace(charIndex, 1, "");
    }
}

// separate verses into text file lines
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
    // the first line is always blank
    int lineNum = -1;

    while(std::getline(fin, line)) {
        lineNum++;

        std::istringstream iss(line);
        std::string word;
        WordInfo* wordInfo;

        while (iss >> word) {
            remove_special_chars(word);
            wordInfo = new WordInfo(word, lineNum);
            tree.insert(wordInfo, &compare, &on_duplicate);
        }
    }
}

// output the words alphabetically
void TextFile::print_words() {
    tree.traverse_inorder(&visit);
    std::cout << std::endl;
}