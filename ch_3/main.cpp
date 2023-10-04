#include <iostream>

#include "SLList.h"
#include "Flight.h"

template <typename T>
T GetInput(const std::string& prompt) {
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

void PrintAll(SLList<Flight>& list) {
    for (int i = 0; i < list.length(); ++i) {
        Flight& flight = list.iterate(i)->getInfo();
        std::cout << "flight number " << flight.GetId() << ":\n";
        flight.PrintPassengers();
    }
};

void GetFlightIndex(SLList<Flight>& list, int id, int& index) {
    for (int i = 0; i < list.length(); ++i) {
        Flight flight = list.at(i);
        if (flight.GetId() == id) {
            index = i; 
            return;
        }
    }

    Flight flight(id);
    list.pushBack(flight);
    GetFlightIndex(list, id, index);
};

void UserReservation(SLList<Flight>& list) {
    int flightNum;
    flightNum = GetInput<int>("enter a flight number: ");

    int flightIndex;
    GetFlightIndex(list, flightNum, flightIndex);

    while (true) {
        int option = GetInput<int>("\n\t=== MENU ===\n1 - insert passenger(s) onto flight "
            + std::to_string(flightNum) + "\n2 - remove passenger from flight " + std::to_string(flightNum) + "\n3 - list passengers on flight "
            + std::to_string(flightNum) + "\n4 - list passengers alphabetically\n0 - exit flight " + std::to_string(flightNum) + "\n\n:");
        std::cout << "\n";
        
        // define a reference to the current flight
        Flight& flight = list.iterate(flightIndex)->getInfo();

        if (option == 1) { 
            std::string in;
            while (true) {
                in = GetInput<std::string>("enter name (or [0] to exit): ");
                if (in == "0") break;
                else flight.AddPassenger(in);
            }
        }
        else if (option == 2) flight.RemovePassenger(GetInput<std::string>("enter name: "));
        else if (option == 3 || option == 4) flight.PrintPassengers();
        else return;
    }
};

void UserInteract(SLList<Flight>& list) {
    while (true) {
        std::string menu = "\t=== MAIN MENU ===\n1 - make or change a reservation\n2 - print all manifests\n3 - driver\n0 - exit\n\n:";
        int option = GetInput<int>(menu); 
        std::cout << "\n";

        switch (option) {
            case 1:
                UserReservation(list);
                break;
            case 2:
                PrintAll(list);
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
    SLList<Flight> list;
    UserInteract(list);

    return 0;


    // SLList<int> list;
    // list.insert(3);
    // list.insert(1);
    // list.insert(2, 0);

    // list.removeFirst(3);
    // list.removeAt(1);
    // list.removeAt(-1);
    // list.removeAt(8);
    // list.removeAt(0);

    // list.pushBack(1);
    // list.pushBack(0);
    // list.pushBack(2);
    // list.pushForward(-1);
};