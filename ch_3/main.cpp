#include <iostream>

#include "SLList.h"

template <typename T>
T getInput(const std::string& prompt) {
    std::cout << prompt;
    T temp;
    std:: cin >> temp;
    return temp;
};

void Driver() {
    std::string names[] = {"Hamilton Dale", "Hamilton Leslie", "Hamilton Jonathan", "Hamilton Nicholas",
        "Hamilton Annalisa", "Absorka Thor", "Snowwisper Nora", "Loki the Mutt"};

    SLList<std::string> flight1, flight2;
    int flightNums[] = {2430, 2515};
    for (int i = 0; i < 2; ++i) {
        int j = i == 0 ? 0 : 5;
        int end = i == 0 ? 5 : 8;

        for (; j < end; ++j) {
            std::cout << names[j] + " was inserted into flight " + std::to_string(flightNums[i]) + "\n";

            if (i == 0) flight1.orderInsert(names[j]);
            else flight2.orderInsert(names[j]);
        }

        std::cout << "\nflight number: " + std::to_string(flightNums[i]) + "\n";
        if (i == 0) flight1.out();
        else flight2.out();
    }
};

void UserReservation(SLList<SLList<std::string>> list) {
    int flight = getInput<int>("enter a flight number: ");
    int option = getInput<int>("\n\t=== MENU ===\n1 - insert passenger onto flight "
        + std::to_string(flight) + "\n2 - remove passenger from flight " + std::to_string(flight) + "\n3 - list passengers on flight "
        + std::to_string(flight) + "\n4 - list passengers alphabetically\n0 - exit flight " + std::to_string(flight) + "\n\n:");

        if (option == 1 || option == 2) {
            std::string name = getInput<std::string>("enter name: ");
            // TODO insert alphabetically, remove
        }
        else if (option == 3 || option == 4); // call list.out
        else return;
};

void UserInteract(SLList<SLList<std::string>> list) {
    while (true) {
        std::string menu = "\t\t=== MAIN MENU ===\n1 - make or change a reservation\n2 - print all manifests\n3 - driver\n0 - exit\n\n:";
        int option = getInput<int>(menu); 
        std::cout << "\n";

        switch (option) {
            case 1:
                UserReservation(list);
                break;
            case 2:
                //TODO
                break;
            case 3:
                Driver();
                break;
            default:
                return;
        }
    }
};

int main() {
    SLList<SLList<std::string>> list;
    UserInteract(list);

    // SLList<int> list;
    // for (int i = 0; i < 3; ++i) {
    //     list.push_back(i + 2);
    // }
    // for (int i = 0; i < 3; ++i) {
    //     list.push_forward(i + 2);
    // }
    // list.out();
    // std::cout << list.length() << "\n";
    // list.removeFirst(3);
    // list.out();
    // SLLNode<int>* temp = new SLLNode<int>(9);
    // list.insert(temp, 3);
    // std::cout << list.iterate(6) << std::endl;
};