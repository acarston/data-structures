#include "rastarr.h"

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

int main(int argc, char* argv[]) {
    check_args(argc);

    int rows, cols;
    char** arr = rastarr::get(argv[1], rows, cols); 
    rastarr::populate(arr, argv[1], rows, cols);

    if (argc == 2) rastarr::print_stands(arr, rows, cols);
    else rastarr::print_stands(arr, rows, cols, argv[2]);
};