#include "rastarr.h"
// #include <sys/resource.h>

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
    // const rlim_t kStackSize = 1024 * 1024 * 1024;   // min stack size = 16 MB
    // struct rlimit rl;
    // int result;

    // result = getrlimit(RLIMIT_STACK, &rl);
    // if (result == 0)
    // {
    //     if (rl.rlim_cur < kStackSize)
    //     {
    //         rl.rlim_cur = kStackSize;
    //         result = setrlimit(RLIMIT_STACK, &rl);
    //         if (result != 0)
    //         {
    //             fprintf(stderr, "setrlimit returned result = %d\n", result);
    //         }
    //     }
    // }

    check_args(argc);

    int rows, cols;
    char** arr = rastarr::get_empty(argv[1], rows, cols); 
    rastarr::populate(arr, argv[1], rows, cols);

    int** map = rastarr::get_map(arr, rows, cols);
    if (argc == 2) rastarr::output_map(map, rows, cols);
    else rastarr::output_map(map, rows, cols, argv[2]);

    // if (argc == 2) rastarr::print_stands(arr, rows, cols);
    // else rastarr::print_stands(arr, rows, cols, argv[2]);
};