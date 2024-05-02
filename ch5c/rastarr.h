#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

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
    int mark_stand(char**& arrTracker, int**& map, int row, int col, int id, int count = 0, char tree = 't') {
        // end call if cell is grass, burn
        if (arrTracker[row][col] != tree) return count;

        // mark visited cell as grass
        arrTracker[row][col] = 'g';
        map[row][col] = id;
        
        count++;
        // look around the current cell
        count = mark_stand(arrTracker, map, row, col - 1, id, count, tree);
        count =       mark_stand(arrTracker, map, row + 1, col, id, count, tree);
        count =       mark_stand(arrTracker, map, row, col + 1, id, count, tree);
        count =       mark_stand(arrTracker, map, row - 1, col, id, count, tree);

        return count;
    }

    void set_surrounding(int**& map, int rows, int cols, int*& surrounding, int row, int col) {
        int current = map[row][col];

        surrounding[0] = row + 1 >= rows ? current : map[row+1][col]; 
        surrounding[1] = row - 1 < 0 ? current : map[row-1][col]; 
        surrounding[2] = col + 1 >= cols ? current : map[row][col+1]; 
        surrounding[3] = col - 1 < 0 ? current : map[row][col-1];
    }

    void set_burned(int**& map, bool*& isBurned, int*& surrounding, int id) {
        for (int i = 0; i < 4; ++i) {
            if (surrounding[i] == 0) {
                isBurned[id] = false;
                return;
            }
        }
    }
}

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

    char** get_map(int**& arr, int rows, int cols) {
        char** map = get_array<char>(rows, cols, 'g');
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] > 0) map[i][j] = 't';
                if (arr[i][j] < 0) map[i][j] = 'b';
            }
        }
        return map;
    }

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
    }

    void remove_shadows(char**& arr, char**& arrTracker, int rows, int cols) {
        int** map = get_array<int>(rows, cols, 0);
        std::vector<int> counts;
        int id = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                if (arrTracker[i][j] == 'b') {
                    id++;
                    counts.push_back(mark_stand(arrTracker, map, i, j, id, 0, 'b')); // arr vs arrTracker different????
                }
            }
        }

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 0; j < cols - 1; ++j) {
                if (map[i][j] > 0 && counts[map[i][j]-1] < 5) {
                    arr[i][j] = 'g';
                }
            }
        }
    }

    template <typename T>
    void output_map(T**& map, int rows, int cols, const std::string& filePath) {
        std::ofstream fout(filePath);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fout << map[i][j] << " ";
            }
            fout << "\n";
        }
    }
}