#include <iostream>
#include <fstream>

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
    }

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
    }

    // give all cells within a stand a predetermined id in a matrix of ints 
    // modifies the original array of chars due to pass by reference
    void mark_stand(char**& arrTracker, int**& map, int row, int col, int& id) {
        // end call if the cell is not a tree
        if (arrTracker[row][col] == 'g') return;

        // mark visited cell as grass
        arrTracker[row][col] = 'g';
        map[row][col] = id;
        
        // look around the current cell
        mark_stand(arrTracker, map, row, col - 1, id);
        mark_stand(arrTracker, map, row + 1, col, id);
        mark_stand(arrTracker, map, row, col + 1, id);
        mark_stand(arrTracker, map, row - 1, col, id);
    }
}

namespace rastarr {
    template <typename T> 
    void print_matrix(T**& arr, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

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
    }

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
    }

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
    }

    int** get_map(char**& arr, int rows, int cols) {
        int** map = get_array<int>(rows, cols, 0);
        int id = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                if (arr[i][j] == 't') {
                    id++;
                    mark_stand(arr, map, i, j, id);
                }
            }
        }

        return map;
    }

    template <typename T>
    T** trim(T**& arr, int& rows, int& cols) {
        rows -= 2;
        cols -= 2;
        T** map = get_array<T>(rows, cols);

        for(int i = 0; i < rows; ++i) {
            for(int j = 0; j < cols; ++j) {
                map[i][j] = arr[i + 1][j + 1];
            }
        }

        return map;
    }

    void output_map(int**& map, int rows, int cols, const std::string& filePath) {
        std::ofstream fout(filePath);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fout << map[i][j] << " ";
            }
            fout << "\n";
        }
    }
}