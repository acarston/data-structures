#include <iostream>

#include "SLList.h"
#include "Flight.h"

template <typename T>
T getInput(const std::string& prompt) {
    std::cout << prompt;
    T temp;
    std:: cin >> temp;
    return temp;
};

void Driver() { //TODO that thing in the assignment
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

// void printAll(SLList<std::tuple<int, SLList<std::string>>>& list) {
//     for (int i = 0; i < list.length(); ++i) {
//         auto flight = list.iterate(i);
//         std::cout << std::to_string();
//     }
// };

// Flight* getFlight(SLList<Flight>& list, int id) {
//     for (int i = 0; i < list.length(); ++i) {
//         Flight* flight = &list.at(i);
//         if (flight->getId() == id) return flight;
//     }

//     Flight flight(id);
//     list.pushBack(flight);
//     getFlight(list, id);
// };

// int getFlightIndex(SLList<Flight>& list, int id) {
//     for (int i = 0; i < list.length(); ++i) {
//         Flight flight = list.at(i);
//         if (flight.getId() == id) return i;
//     }

//     Flight flight(id);
//     list.pushBack(flight);
//     getFlightIndex(list, id);

//     return -1;
// };

// void getFlightIndex(SLList<Flight>& list, int id, int& index) {
//     for (int i = 0; i < list.length(); ++i) {
//         Flight flight = list.at(i);
//         if (flight.getId() == id) index = i; return;
//     }

//     Flight flight(id);
//     list.pushBack(flight);
//     getFlightIndex(list, id, index);
// };

// void UserReservation(SLList<Flight>& list) {
//     int flightNum;
//     // SLList<std::string> names; // destroyed when out of scope???
//     // auto flight = make_tuple(flightNum, names); 

//     flightNum = getInput<int>("enter a flight number: ");
//     int flightIndex;
//     getFlightIndex(list, flightNum, flightIndex);
//     // Flight* flight = getFlight(list, flightNum);
//     // auto flightIndex = getFlightIndex(list, flightNum);
//     while (true) {
//         int option = getInput<int>("\n\t=== MENU ===\n1 - insert passenger(s) onto flight "
//             + std::to_string(flightNum) + "\n2 - remove passenger from flight " + std::to_string(flightNum) + "\n3 - list passengers on flight "
//             + std::to_string(flightNum) + "\n4 - list passengers alphabetically\n0 - exit flight " + std::to_string(flightNum) + "\n\n:");
//         std::cout << "\n";
        
//         if (option == 1) {
//             std::string in;
//             while (true) {
//                 in = getInput<std::string>("enter name (or [0] to exit): ");
//                 if (in == "0") break;
//                 else list.at(flightIndex).addPassenger(in);
//             }
//         }
//         else if (option == 2) list.at(flightIndex).removePassenger(getInput<std::string>("enter name: "));
//         else if (option == 3 || option == 4) list.at(flightIndex).printPassengers();
//         else return;
//     }
// };

// void UserInteract(SLList<Flight>& list) {
//     while (true) {
//         std::string menu = "\t=== MAIN MENU ===\n1 - make or change a reservation\n2 - print all manifests\n3 - driver\n0 - exit\n\n:";
//         int option = getInput<int>(menu); 
//         std::cout << "\n";

//         switch (option) {
//             case 1:
//                 UserReservation(list); // doesnt check for duplicates!!!!!!!!!! should now
//                 break;
//             case 2:
//                 //TODO, commented out
//                 break;
//             case 3:
//                 Driver();
//                 break;
//             default:
//                 return;
//         }
//     }
// };

int main() {
    Flight flight(1040);
    flight.addPassenger("Joe");

    SLList<Flight> flights;
    flights.pushBack(flight);

    Flight flight2(1060);

    SLList<Flight> flights2;
    flights2.pushBack(flight2);

    auto &fli = flights2.iterate(0)->getInfo();

    fli.addPassenger("Joe");


    // SLList<Flight> list;
    // list.pushBack(flight);
    // UserInteract(list);

    // SLList<int> list;
    // for (int i = 0; i < 3; ++i) {
    //     list.pushBack(i + 2);
    // }
    // for (int i = 0; i < 3; ++i) {
    //     list.pushForward(i + 2);
    // }
    // list.out();
    // list.removeAt(0);
    // list.out();
    // std::cout << list.length() << "\n";
    // list.removeFirst(3);
    // list.out();
    // SLLNode<int>* temp = new SLLNode<int>(9);
    // list.insert(temp, 3);
    // std::cout << list.iterate(6) << std::endl;
};