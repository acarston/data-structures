#include "rastarr.h"
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

void user_interact(char**& arr, int rows, int cols, int argc) {
    char in = iohelpers::get_input<char>("enable verbose outputs? (not recommended for large files) [y/n]: ");
    if (in != 'y') return;

    std::cout << "\nreading from file...\ninput matrix:\n";
    rastarr::print_matrix(arr, rows, cols);
    std::cout << "parsed matrix:\n";
    rastarr::print_matrix_parsed(arr, rows, cols, 't');

    if (argc == 2) std::cout << "output matrix:\n";
    else std::cout << "outputting to file...";
};

int main(int argc, char* argv[]) {
    check_args(argc);

    int rows, cols;
    char** arr = rastarr::get_empty(argv[1], rows, cols); 
    rastarr::populate(arr, argv[1], rows, cols);

    user_interact(arr, rows, cols, argc);

    int** map = rastarr::get_map(arr, rows, cols);
    if (argc == 2) rastarr::output_map(map, rows, cols);
    else rastarr::output_map(map, rows, cols, argv[2]);
};