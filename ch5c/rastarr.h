#include <iostream>
#include <fstream>
#include <algorithm>

// anonymous namespace for private functions
namespace {
    // dynamically allocate a 2D array
    template <typename T> 
    T** get_array(int rows, int cols) {
        T** arr = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new T[cols];
        }
        return arr;
    };

    // allocate and populate all elements with a value
    template <typename T> 
    T** get_array(int rows, int cols, T defaultVal) {
        T** arr = new T*[rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new T[cols];
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                arr[i][j] = defaultVal;
            }
        }
        return arr;
    };

    // give all cells within a stand a predetermined id in a matrix of ints 
    // modifies the original array of chars due to pass by reference
    void mark_stand(char**& arrTracker, int**& map, int row, int col, int& id) {
        // end call if the cell is grass, burn
        if (arrTracker[row][col] != 't') return;

        // mark visited cell as grass
        arrTracker[row][col] = 'g';
        map[row][col] = id;
        
        // look around the current cell
        mark_stand(arrTracker, map, row, col - 1, id);
        mark_stand(arrTracker, map, row + 1, col, id);
        mark_stand(arrTracker, map, row, col + 1, id);
        mark_stand(arrTracker, map, row - 1, col, id);
    };

    void set_surrounding(int**& map, int rows, int cols, int*& surrounding, int row, int col) {
        int current = map[row][col];

        surrounding[0] = row + 1 > rows ? current : map[row+1][col]; 
        surrounding[1] = row - 1 < 0 ? current : map[row-1][col]; 
        surrounding[2] = col + 1 > cols ? current : map[row][col+1]; 
        surrounding[3] = col - 1 < 0 ? current : map[row][col-1];
    };

    void set_burned(int**& map, bool*& isBurned, int*& surrounding, int id) {
        for (int i = 0; i < 4; ++i) {
            if (surrounding[i] == 0) {
                isBurned[id] = false;
                return;
            }
        }
    };

    void burn(int**& map, int rows, int cols, int numStands) {
        // dynamic allocation because only the pointer is necessary
        // deleted automatically at end of function call
        int* surrounding = new int[4];
        bool* isBurned = new bool[numStands];
        std::fill_n(isBurned, numStands, true);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                set_surrounding(map, rows, cols, surrounding, i, j);
                set_burned(map, isBurned, surrounding, map[i][j]);
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int& id = map[i][j];
                if (isBurned[id]) id = -1;
            }
        }
    };

    // TODO modify map to set burns to -1
    // void burn(int**& map, int rows, int cols, int numStands) { // TODO get numStands from id
    //     Border** borderMap = get_array<Border>(rows, cols);
    //     for (int i = 1; i < rows - 1; ++i) {
    //         for (int j = 1; j < cols - 1; ++j) {
    //             int current = map[i][j];
    //             if (current == 0 || current == -1) continue;
    //             borderMap[i][j].info = current;

    //             int surrounding[] = {map[i][j+1], map[i][j-1], map[i-1][j], map[i+1][j]}; // TODO make into its own function
    //             for (int k = 0; k < 4; ++k) {
    //                 if (surrounding[k] != current) {
                        
    //                 } 
    //             }

    //             if (right == current && left == current && top == current && bottom == current) continue;
    //             borderMap[i][j].isBorder = true;
    //         }
    //     }
    // };
};

namespace rastarr {
    template <typename T> 
    void print_matrix(T**& arr, int rows, int cols, int iStart = 0, int jStart = 0) {
        for (int i = iStart; i < rows; ++i) {
            for (int j = jStart; j < cols; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    };

    template <typename T>
    void print_matrix_parsed(T**& arr, int rows, int cols, T toParse) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] == toParse) std::cout << arr[i][j] << " ";
                else std::cout << "  ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    };

    // get an array of the appropriate size based on a file
    char** get_empty(const std::string& filePath, int& rows, int& cols) {
        std::fstream fin(filePath);
        if (!fin.is_open()) {
            std::cout << "FATAL: unable to open file" << std::endl;
            exit(0);
        }

        std::string arrSizeInfo;
        std::getline(fin, arrSizeInfo);

        // retrieve array dimensions
        int first = arrSizeInfo.find("=");
        int middle = arrSizeInfo.find(",");
        int last = arrSizeInfo.find("=", middle);
        rows = std::stoi(arrSizeInfo.substr(first + 1, middle-first)) + 2;
        cols = std::stoi(arrSizeInfo.substr(last + 1)) + 2;

        return get_array<char>(rows, cols);
    };

    void populate(char**& arr, const std::string& filePath, int rows, int cols) {
        // add a grassland border
        for (int i = 0; i < cols; ++i) {
            arr[0][i] = 'g';
            arr[rows-1][i] = 'g';
        }
        for (int i = 0; i < rows; ++i) {
            arr[i][0] = 'g';
            arr[i][cols-1] = 'g';
        }

        std::fstream fin(filePath);
        if (!fin.is_open()) {
            std::cout << "FATAL: unable to open file" << std::endl;
            exit(0);
        }
        std::string line;
        std::getline(fin, line);

        for (int i = 1; i < rows - 1; ++i) {
            std::getline(fin, line);
            int k = 0;
            for (int j = 1; j < cols - 1; ++j, k += 2) {
                arr[i][j] = line[k];
            }
        }
    };

    int** get_map(char**& arr, int rows, int cols, int& id) {
        int** map = get_array<int>(rows, cols, 0);
        id = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                if (arr[i][j] == 't') {
                    id++;
                    mark_stand(arr, map, i, j, id);
                }
                if (arr[i][j] == 'b') {
                    map[i][j] = -1;
                }
            }
        }

        return map;
    }

    void output_map(int**& map, int rows, int cols, int numStands) { 
        burn(map, rows - 1, cols - 1, numStands);
        print_matrix<int>(map, rows - 1, cols - 1, 1, 1); 
    };

    // TODO add burn function
    void output_map(int**& map, int rows, int cols, const std::string& filePath) {
        std::ofstream fout(filePath);
        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                fout << map[i][j] << " ";
            }
            fout << "\n";
        }
    };
};