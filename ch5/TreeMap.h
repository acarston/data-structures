#ifndef TREEMAP_H
#define TREEMAP_H

#include <string>
#include <fstream>
#include <iostream>

// A forest map represented by chars provided in the input file.
// Includes functionality to identify individual groups of tree
// chars and output them as a matrix of ints.
class TreeMap {
    public:
        TreeMap(const std::string& filePath);
        void build_stands();

        void print_treemap();
        void print_treemap_parsed();
        void print_intmap();
        void output_intmap(const std::string& outPath);
    private:
        std::string filePath;
        int mapRows, mapCols;
        char** treeMap = nullptr;
        int** intMap = nullptr;
        
        template <typename T> T** get_array(int rows, int cols);
        template <typename T> T** get_array(int rows, int cols, T defaultVal);
        void set_treemap_size();
        void populate_treemap();

        template <typename T> void print_matrix(T**& arr, int rows, int cols);

        void mark_stand(int row, int col, int& id);
        void set_intmap();
        void trim_intmap();
};

#include "TreeMap.cpp"
#endif