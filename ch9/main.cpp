#include <fstream>
#include <string>
#include <list>
#include "Heap.h"

void sort(std::ifstream& fin, bool ascending) {
    std::string line;
    int count = 0;
    std::list<int> nums;
    while (std::getline(fin, line)) {
        nums.push_back(std::stoi(line));
        ++count;
    }

    int* input = new int[count];
    int i = 0;
    for (auto it = nums.begin(); it != nums.end(); ++it, ++i) input[i] = *it;

    Heap<int> heap(input, count, ascending);
    heap.sort();
    heap.output();

    delete[] input;
    input = nullptr;
}

void sort(std::ifstream& fin, bool ascending, std::ofstream& fout) {
    std::string line;
    int count = 0;
    std::list<int> nums;
    while (std::getline(fin, line)) {
        nums.push_back(std::stoi(line));
        ++count;
    }

    int* input = new int[count];
    int i = 0;
    for (auto it = nums.begin(); it != nums.end(); ++it, ++i) input[i] = *it;

    Heap<int> heap(input, count, ascending);
    heap.sort();
    heap.output(fout);

    delete[] input;
    input = nullptr;
}

void user_interact(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "\t--DISAMBIGUATION--\nThe program requires at least 2 arguments: an input file path, an option (-a or -d), and (optionally) an output file path.";
        std::cout << "\nThe input file path must be the first argument; all others have no order.\nUsage: -a ASCENDING -d DECENDING" << std::endl;
        exit(0);
    }

    if (argc < 3 || argc > 4) {
        std::cout << "Error: unparsable number of arguments. Provide an input file, the appropriate flag (-a or -d), and (optionally) an output file.\nRun the program without any arguments to display the help message." << std::endl;
        exit(-1);
    }
    
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        std::cout << "Error: unable to open input file! Please provide the input file as the first parameter." << std::endl;
        exit(-1);
    }

    // locate and set the flag
    bool hasFlag = false;
    std::string* flag = nullptr;
    int i = 0;
    for (; i < argc - 2; ++i) {
        std::string cur = argv[i+2];
        if (cur == "-a" || cur == "-d") {
            flag = &cur;
            hasFlag = true;
            break;
        }
    }
    if (!hasFlag) {
        std::cout << "Missing option: -a or -d. Usage: -a ASCENDING -d DECENDING" << std::endl;
        exit(-1);
    }

    // this is cursed and I refuse to change it.
    bool ascending = (*flag == "-a") ? true : false;
    if (argc == 3) return sort(fin, ascending);
    std::ofstream fout(argv[!i+2]);
    sort(fin, ascending, fout);
}

int main(int argc, char** argv) {
    user_interact(argc, argv);
}