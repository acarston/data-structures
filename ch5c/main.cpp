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
}

void user_interact(int argc, char* argv[]) {
    TreeMap treeMap(argv[1]);
    treeMap.remove_shadows();

    char in = iohelpers::get_input<char>("enable verbose outputs? (not recommended for large files) [y/n]: ");
    if (in == 'y') {
        std::cout << "\nreading from file...\ninput matrix (shadows removed):\n";
        treeMap.print_treemap();
        std::cout << "parsed matrix:\n";
        treeMap.print_treemap_parsed();
    }

    int numStands = 0;
    treeMap.set_intmap(numStands);
    treeMap.burn(numStands);

    if (argc == 2) {
        std::cout << "output matrix:\n";
        treeMap.print_treemap();
    }
    else {
        std::cout << "outputting to file...";
        treeMap.output_treemap(argv[2]);
    }
}

int main(int argc, char* argv[]) {
    check_args(argc);
    user_interact(argc, argv);
}