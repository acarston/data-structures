#include "TreeMap.h"
#include "../utils/iohelpers.h"

void check_args(int argc) {
    if (argc < 2) {
        std::cout << "no input files" << std::endl;
        exit(0);
    }
    else if (argc > 3) {
        std::cout << "too many arguments" << std::endl;
        exit(0);
    }
};

void user_interact(int argc, char* argv[]) {
    TreeMap treeMap(argv[1]);

    char in = iohelpers::get_input<char>("enable verbose outputs? (not recommended for large files) [y/n]: ");
    if (in == 'y') {
        std::cout << "\nreading from file...\ninput matrix:\n";
        treeMap.print_treemap();
        std::cout << "parsed matrix:\n";
        treeMap.print_treemap_parsed();
    }

    treeMap.build_stands();
    if (argc == 2) {
        std::cout << "output matrix:\n";
        treeMap.print_intmap();
    }
    else {
        std::cout << "outputting to file...";
        treeMap.output_intmap(argv[2]);
    }
};

int main(int argc, char* argv[]) {
    check_args(argc);
    user_interact(argc, argv);
};