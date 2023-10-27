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

    std::cout << "\nreading from file...\ninput matrix (shadows removed):\n";
    rastarr::print_matrix(arr, rows, cols);
    std::cout << "parsed matrix:\n";
    rastarr::print_matrix_parsed(arr, rows, cols, 't');

    if (argc == 2) std::cout << "output matrix:\n";
    else std::cout << "outputting to file...";
};

// namespace? delete dynamic allocation?
int main(int argc, char* argv[]) {
    check_args(argc);

    // create the original tree map
    int rows, cols;
    char** map = rastarr::get_empty(argv[1], rows, cols); 
    char** mapTracker = rastarr::get_empty(argv[1], rows, cols);
    rastarr::populate(map, argv[1], rows, cols);
    rastarr::populate(mapTracker, argv[1], rows, cols);
    rastarr::remove_shadows(map, mapTracker, rows, cols);

    user_interact(map, rows, cols, argc);

    // identify the stands
    int numStands = 0;
    int** stands = rastarr::get_map(map, rows, cols, numStands);

    // create the new tree map
    stands = rastarr::trim<int>(stands, rows, cols);
    rastarr::burn(stands, rows, cols, numStands);
    char** newMap = rastarr::get_map(stands, rows, cols);

    if (argc == 2) rastarr::print_matrix<char>(newMap, rows, cols);
    else rastarr::output_map<char>(newMap, rows, cols, argv[2]);
};