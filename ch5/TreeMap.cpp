#include "TreeMap.h"

TreeMap::TreeMap(const std::string& filePath) {
    this->filePath = filePath;
    set_map_size();
    populate_map();
};

void TreeMap::build_stands() {
    set_intmap();
    trim_intmap();
};

void TreeMap::print_treemap() {
    print_matrix<char>(treeMap, mapRows, mapCols); 
};

void TreeMap::print_treemap_parsed() {
    for (int i = 0; i < mapRows; ++i) {
        for (int j = 0; j < mapCols; ++j) {
            if (treeMap[i][j] == 't') std::cout << treeMap[i][j] << " ";
            else std::cout << "  ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
};

void TreeMap::print_intmap() {
    print_matrix<int>(intMap, mapRows, mapCols);
};

void TreeMap::output_intmap(const std::string& outPath) {
    std::ofstream fout(outPath);
    for (int i = 0; i < mapRows; ++i) {
        for (int j = 0; j < mapCols; ++j) {
            fout << intMap[i][j] << " ";
        }
        fout << "\n";
    }
};


template <typename T> 
T** TreeMap::get_array(int rows, int cols) {
    T** arr = new T*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new T[cols];
    }
    return arr;
};

template <typename T> 
T** TreeMap::get_array(int rows, int cols, T defaultVal) {
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

void TreeMap::set_map_size() {
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
    mapRows = std::stoi(arrSizeInfo.substr(first + 1, middle-first)) + 2;
    mapCols = std::stoi(arrSizeInfo.substr(last + 1)) + 2;

    treeMap = get_array<char>(mapRows, mapCols);
};

void TreeMap::populate_map() {
    // add a grassland border
    for (int i = 0; i < mapCols; ++i) {
        treeMap[0][i] = 'g';
        treeMap[mapRows-1][i] = 'g';
    }
    for (int i = 0; i < mapRows; ++i) {
        treeMap[i][0] = 'g';
        treeMap[i][mapCols-1] = 'g';
    }

    std::fstream fin(filePath);
    if (!fin.is_open()) {
        std::cout << "FATAL: unable to open file" << std::endl;
        exit(0);
    }
    std::string line;
    std::getline(fin, line);

    for (int i = 1; i < mapRows - 1; ++i) {
        std::getline(fin, line);
        int k = 0;
        for (int j = 1; j < mapCols - 1; ++j, k += 2) {
            treeMap[i][j] = line[k];
        }
    }
};


template <typename T> 
void TreeMap::print_matrix(T**& arr, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
};


// give all cells within a stand a predetermined id in a matrix of ints 
// modifies the original array of chars due to pass by reference
void TreeMap::mark_stand(int row, int col, int& id) {
    // end call if the cell is not a tree
    if (treeMap[row][col] == 'g') return;

    // mark visited cell as grass
    treeMap[row][col] = 'g';
    intMap[row][col] = id;
    
    // look around the current cell
    mark_stand( row, col - 1, id);
    mark_stand(row + 1, col, id);
    mark_stand(row, col + 1, id);
    mark_stand(row - 1, col, id);
};

void TreeMap::set_intmap() {
    intMap = get_array<int>(mapRows, mapCols, 0);
    int id = 0;

    for (int i = 1; i < mapRows - 1; ++i) {
        for (int j = 1; j < mapCols - 1; ++j) {
            if (treeMap[i][j] == 't') {
                id++;
                mark_stand(i, j, id);
            }
        }
    }
};

void TreeMap::trim_intmap() {
    mapRows -= 2;
    mapCols -= 2;
    int** map = get_array<int>(mapRows, mapCols);

    for(int i = 0; i < mapRows; ++i) {
        for(int j = 0; j < mapCols; ++j) {
            map[i][j] = intMap[i + 1][j + 1];
        }
    }
    intMap = map;
};