#ifndef TREEMAP_H
#define TREEMAP_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

// A forest map represented by chars provided in the input file.
// Includes functionality to identify individual groups of tree
// chars and determine if the group is burned. If a group is 
// burned, tree chars are changed in output. 
class TreeMap {
    public:
        TreeMap(const std::string& filePath);
        
        void set_intmap(int& id);

        void print_treemap();
        void print_treemap_parsed();
        void print_intmap();
        void output_treemap(const std::string& outPath);

        void remove_shadows();
        void burn(int numStands);

    private:
        std::string filePath;
        int mapRows, mapCols;
        char** treeMap = nullptr;
        int** intMap = nullptr;

        char**& get_treemap() { return treeMap; }
        
        template <typename T> T** get_array(int rows, int cols);
        template <typename T> T** get_array(int rows, int cols, T defaultVal);
        void set_treemap_size();
        void populate_treemap();
        void populate_treemap(int burnNum);

        template <typename T> void print_matrix(T**& arr, int rows, int cols);

        int mark_stand(char**& arrTracker, int**& map, int row, int col, int id, int count = 0, char tree = 't');

        void trim_intmap();
        void set_surrounding(int*& surrounding, int row, int col);
        void set_burned(bool*& isBurned, int*& surrounding, int id);
};

#include "TreeMap.cpp"
#endif