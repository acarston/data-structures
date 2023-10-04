#include <iostream>

#include "SLList.h"
#include "Flight.h"

void ExitMessage() {
    std::cout << "terminating program..." << std::endl;
};

void InputError() {
    std::cout << "invalid input!\n";
};

template <typename T>
T GetInput(const std::string& prompt) {
    std::cout << prompt;
    T temp;
    std:: cin >> temp;
    return temp;
};

void PrintAll(SLList<Flight>& list) {
    for (int i = 0; i < list.length(); ++i) {
        Flight& flight = list.at(i);
        std::cout << "flight number " << flight.GetId() << ":\n";
        flight.PrintPassengers();
    }
};

void SetFlightIndex(SLList<Flight>& list, int id, int& index) { //BAD NAME?????????????????????????
    for (int i = 0; i < list.length(); ++i) {
        Flight flight = list.at(i);
        if (flight.GetId() == id) {
            index = i; 
            return;
        }
    }

    Flight flight(id);
    list.pushBack(flight);
    SetFlightIndex(list, id, index);
};

void DisplaceLoki (SLList<Flight>& list) {
    Flight& flight = list.at(1); // BETTER WAY TO GET FLIGHT ?????????????????????????????????????

    std::string flightNumStr = std::to_string(flight.GetId());
    std::string loki = "Loki the Mutt";

    int lokiIndex = flight.FindPassengerIndex(loki);
    if (lokiIndex != -1) { 
        std::cout << "found " + loki + " on flight " + flightNumStr + " at index " + std::to_string(lokiIndex) + "\n";
    }
    else {
        std::cout << "could not find loki :((\n"; 
        ExitMessage(); 
        exit(0);
    }

    flight.RemovePassenger(loki);
    std::cout << loki + " removed from flight " + flightNumStr + "\n";

    int flightIndex;
    SetFlightIndex(list, 2750, flightIndex);

    list.at(flightIndex).AddPassenger(loki);
    std::cout << loki + " added to flight " + std::to_string(2750) + "\n";

    std::cout << "\nreprinting all manifests...\n\n";
    PrintAll(list);
};

void Driver() { 
    std::string names[] = {"Hamilton Dale", "Hamilton Leslie", "Hamilton Jonathan", "Hamilton Nicholas",
        "Hamilton Annalisa", "Absorka Thor", "Snowwisper Nora", "Loki the Mutt"};

    SLList<Flight> flights;
    int flightNums[] = {2430, 2515};
    int flightIndex;
    for (int i = 0; i < 2; ++i) {
        SetFlightIndex(flights, flightNums[i], flightIndex);
        Flight& flight = flights.at(flightIndex);

        int j = i == 0 ? 0 : 5;
        int end = i == 0 ? 5 : 8;

        for (; j < end; ++j) {
            std::cout << names[j] + " was inserted into flight " + std::to_string(flightNums[i]) + "\n";
            flight.AddPassenger(names[j]);
        }
    }

    std::cout << "\n";
    PrintAll(flights);

    DisplaceLoki(flights);
};

void UserReservation(SLList<Flight>& list) {
    int flightNum;
    flightNum = GetInput<int>("enter a flight number: ");
    
    if (flightNum == 0) {
        InputError();
        ExitMessage();
        exit(0);
    }

    int flightIndex;
    SetFlightIndex(list, flightNum, flightIndex);

    while (true) {
        int option = GetInput<int>("\n\t=== MENU ===\n1 - insert passenger(s) onto flight "
            + std::to_string(flightNum) + "\n2 - remove passenger from flight " + std::to_string(flightNum) + "\n3 - list passengers on flight "
            + std::to_string(flightNum) + "\n4 - list passengers alphabetically\n0 - exit flight " + std::to_string(flightNum) + "\n\n:");
        std::cout << "\n";
        
        // define a reference to the current flight
        Flight& flight = list.at(flightIndex);

        if (option == 0) return; // TODO make this a switch
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
        else InputError();
    }
};

void UserInteract(SLList<Flight>& list) {
    while (true) {
        std::string menu = "\t=== MAIN MENU ===\n1 - make or change a reservation\n2 - print all manifests\n3 - driver\n0 - exit\n\n:";
        char option = GetInput<char>(menu); 
        std::cout << "\n";

        switch (option) {
            case '0':
                return;
            case '1':
                UserReservation(list);
                break;
            case '2':
                PrintAll(list);
                break;
            case '3':
                Driver();
                break;
            default:
                InputError();
                break;
        }
    }
};

int main() {
    SLList<Flight> list;
    UserInteract(list);

    ExitMessage();
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