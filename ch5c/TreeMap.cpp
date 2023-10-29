#include "TreeMap.h"

// use the filepath to create a tree map
TreeMap::TreeMap(const std::string& filePath) {
    this->filePath = filePath;
    set_treemap_size();
    populate_treemap();
};

// explicitly create the numbered stand map
// call only when the tree map is no longer in use
// void TreeMap::build_stands() {
//     set_intmap();
//     trim_intmap();
// };


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

void TreeMap::remove_shadows() {
    TreeMap treeMapTracker(filePath);
    char** tracker = treeMapTracker.get_treemap();

    int** burnMap = get_array<int>(mapRows, mapCols, 0);
    std::vector<int> counts;
    int id = 0;

    for (int i = 1; i < mapRows - 1; ++i) {
        for (int j = 1; j < mapCols - 1; ++j) {
            if (tracker[i][j] == 'b') {
                id++;
                counts.push_back(mark_stand(tracker, burnMap, i, j, id, 0, 'b')); // arr vs arrTracker different????
            }
        }
    }

    for (int i = 1; i < mapRows - 1; ++i) {
        for (int j = 0; j < mapCols - 1; ++j) {
            if (burnMap[i][j] > 0 && counts[burnMap[i][j]-1] < 5) {
                treeMap[i][j] = 'g';
            }
        }
    }
};

void TreeMap::burn(int numStands) {
    trim_intmap();

    // dynamic allocation because only the pointer is necessary
    // deleted automatically at end of function call
    int* surrounding = new int[4];
    bool* isBurned = new bool[numStands];
    std::fill_n(isBurned, numStands, true);

    for (int i = 0; i < mapRows; ++i) {
        for (int j = 0; j < mapCols; ++j) {
            if (intMap[i][j] == 0 || intMap[i][j] == -1) continue;
            set_surrounding(surrounding, i, j);
            set_burned(isBurned, surrounding, intMap[i][j]);
        }
    }

    for (int i = 0; i < mapRows; ++i) {
        for (int j = 0; j < mapCols; ++j) {
            if (intMap[i][j] == 0 || intMap[i][j] == -1) continue;
            int& id = intMap[i][j];
            if (isBurned[id]) id = -1;
        }
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
int TreeMap::mark_stand(char**& arrTracker, int**& map, int row, int col, int id, int count, char tree) {
    // end call if cell is grass, burn
    if (arrTracker[row][col] != tree) return count;

    // mark visited cell as grass
    arrTracker[row][col] = 'g';
    map[row][col] = id;
    
    count++;

    // look around the current cell
    count = mark_stand(arrTracker, map, row, col - 1, id, count, tree);
    count = mark_stand(arrTracker, map, row + 1, col, id, count, tree);
    count = mark_stand(arrTracker, map, row, col + 1, id, count, tree);
    count = mark_stand(arrTracker, map, row - 1, col, id, count, tree);

    return count;
};

void TreeMap::set_intmap(int& id) {
    intMap = get_array<int>(mapRows, mapCols, 0);

    // give each isolated stand a unique id
    id = 0;    
    for (int i = 1; i < mapRows - 1; ++i) {
        for (int j = 1; j < mapCols - 1; ++j) {
            if (treeMap[i][j] == 't') {
                id++;
                mark_stand(treeMap, intMap, i, j, id);
            }
            if (treeMap[i][j] == 'b') {
                intMap[i][j] = -1;
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

void TreeMap::set_surrounding(int*& surrounding, int row, int col) {
    int current = intMap[row][col];

    surrounding[0] = row + 1 >= mapRows ? current : intMap[row+1][col]; 
    surrounding[1] = row - 1 < 0 ? current : intMap[row-1][col]; 
    surrounding[2] = col + 1 >= mapCols ? current : intMap[row][col+1]; 
    surrounding[3] = col - 1 < 0 ? current : intMap[row][col-1];
};

void TreeMap::set_burned(bool*& isBurned, int*& surrounding, int id) {
    for (int i = 0; i < 4; ++i) {
        if (surrounding[i] == 0) {
            isBurned[id] = false;
            return;
        }
    }
};