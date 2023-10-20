#include <iostream>
#include <fstream>

namespace rastarr {
    void print(char**& arr, int rows, int cols) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << arr[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    };

    char** get(const std::string& filePath, int& rows, int& cols) {
        std::fstream fin(filePath);
        if (!fin.is_open()) {
            std::cout << "unable to open file" << std::endl;
            exit(0);
        }

        std::string arrSizeInfo;
        std::getline(fin, arrSizeInfo);

        int first = arrSizeInfo.find("=");
        int middle = arrSizeInfo.find(",");
        int last = arrSizeInfo.find("=", middle);
        rows = std::stoi(arrSizeInfo.substr(first+1, middle-first)) + 2;
        cols = std::stoi(arrSizeInfo.substr(last+1)) + 2;

        char** arr = new char*[rows];
        for (int i = 0; i < rows; ++i) {
            arr[i] = new char[cols];
        }

        return arr;
    };

    void populate(char**& arr, const std::string& filePath, int rows, int cols) {
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
            std::cout << "unable to open file" << std::endl;
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

    int get_stand(char**& arr, int row, int col, int& id, int count = 0, bool first = true) {
        if (arr[row][col] != 't') return count;

        if (first) id++;
        arr[row][col] = id + '0';

        count++;
        
        count = get_stand(arr, row - 1, col, id, count, false);
        count = get_stand(arr, row + 1, col, id, count, false);
        count = get_stand(arr, row, col - 1, id, count, false);
        count = get_stand(arr, row, col + 1, id, count, false);

        return count;
    };

    void print_stands(char**& arr, int rows, int cols) {
        std::cout << "\n";
        int id = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                int count = get_stand(arr, i, j, id);
                if (count > 0) std::cout << "stand " << arr[i][j] << " has " << count << " trees.\n";
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] == 'g') arr[i][j] = '0';
            }
        }  

        std::cout << "\n";
        print(arr, rows, cols);
    };

    void print_stands(char**& arr, int rows, int cols, const std::string& filePath) {
        int id = 0;

        for (int i = 1; i < rows - 1; ++i) {
            for (int j = 1; j < cols - 1; ++j) {
                get_stand(arr, i, j, id);
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (arr[i][j] == 'g') arr[i][j] = '0';
            }
        }  

        std::ofstream fout(filePath);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                fout << arr[i][j] << " ";
            }
            fout << "\n";
        }
    };
};