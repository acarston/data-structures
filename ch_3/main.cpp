#include <iostream>

#include "SLList.h"

int getIntIn(const std::string& prompt) {
    std::cout << prompt;
    int temp;
    std:: cin >> temp;
    return temp;
};

void userInteract() {
    std::string menu = "\t\t=== MAIN MENU ===\n1 - make or change a reservation\n2 - print all manifests\n 3 - driver\n0 - exit";
    int option = getIntIn(menu); 

    switch (option) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            return;
    }
};

int main() {
    SLList<int> list;

    for (int i = 0; i < 3; ++i) {
        list.push_back(i + 2);
    }
    list.out();
};