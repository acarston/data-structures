#include "TreeMap.h"

// use the filepath to create a tree map
TreeMap::TreeMap(const std::string& filePath) {
    this->filePath = filePath;
    set_treemap_size();
    populate_treemap();
};

// explicitly create the numbered stand map
// call only when the tree map is no longer in use
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


// dynamically allocate a 2D array
template <typename T> 
T** TreeMap::get_array(int rows, int cols) {
    T** arr = new T*[rows];
    for (int i = 0; i < rows; ++i) {
        arr[i] = new T[cols];
    }
    return arr;
};

// allocate and populate all elements with a value
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

void TreeMap::set_treemap_size() {
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

void TreeMap::populate_treemap() {
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

    // copy file chars into the tree map
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
// modifies the original tree map when placing 'visited' markers
void TreeMap::mark_stand(int row, int col, int& id) {
    // end call if the cell is not a tree
    if (treeMap[row][col] == 'g') return;

    // mark visited cells with grass, id
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

    // give each isolated stand a unique id
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

// remove the grassland border
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