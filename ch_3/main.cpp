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
    std::cin >> temp;
    return temp;
};

void PrintAll(SLList<Flight>& list) {
    for (int i = 0; i < list.length(); ++i) {
        Flight& flight = list.at(i); // define a reference to the current flight
        std::cout << "flight number " << flight.GetId() << ":\n";
        flight.PrintPassengers();
    }
};

int GetOrCreateFlightIndex(SLList<Flight>& list, int id) { 
    // give the list index of flight with flight number 'id'
    for (int i = 0; i < list.length(); ++i) {
        Flight flight = list.at(i);
        if (flight.GetId() == id) {
            return i;
        }
    }

    // add a new flight to the list if above loop fails
    Flight flight(id);
    list.pushBack(flight);
    return GetOrCreateFlightIndex(list, id);
};

void DisplaceLoki (SLList<Flight>& list) {
    // define a reference to flight 2515
    Flight& flight = list.at(GetOrCreateFlightIndex(list, 2515));

    std::string flightNumStr = std::to_string(flight.GetId());
    std::string loki = "Loki the Mutt";

    int lokiIndex = flight.FindPassengerIndex(loki);
    if (lokiIndex != -1) { // above function returns -1 if not found
        std::cout << "found " + loki + " on flight " + flightNumStr + " at index " + std::to_string(lokiIndex) + "\n";
    }
    else { // will never execute
        std::cout << "could not find loki :((\n"; 
        ExitMessage(); 
        exit(0);
    }

    flight.RemovePassenger(loki);
    std::cout << loki + " removed from flight " + flightNumStr + "\n";

    // add flight 2750 to the list and add loki to the flight
    int flightIndex = GetOrCreateFlightIndex(list, 2750);
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
    for (int i = 0; i < 2; ++i) {
        // create a new flight and define a reference to it
        int flightIndex = GetOrCreateFlightIndex(flights, flightNums[i]);
        Flight& flight = flights.at(flightIndex);

        // determine how to loop through names
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

void AddManyPassengers (Flight& flight) {
    std::string in;
    while (true) {
        in = GetInput<std::string>("enter name (or [0] to exit): ");
        if (in == "0") return;
        else flight.AddPassenger(in);
    }
};

/* manipulate a flight according to user input */
void UserReservation(SLList<Flight>& list) {
    int flightNum = GetInput<int>("enter a flight number: ");
    
    // terminate program if the user is bad
    if (flightNum == 0) { // implicitly checks for non-ints
        InputError();
        ExitMessage();
        exit(0);
    }

    int flightIndex = GetOrCreateFlightIndex(list, flightNum);

    while (true) {
        std::string flightNumStr = std::to_string(flightNum);
        char option = GetInput<char>("\n\t=== MENU ===\n1 - insert passenger(s) onto flight "
            + flightNumStr + "\n2 - remove passenger from flight " + flightNumStr + "\n3 - list passengers on flight "
            + flightNumStr + "\n4 - list passengers alphabetically\n5 - list passengers in reverse\n0 - exit flight " 
            + flightNumStr + "\n\n:");
        std::cout << "\n";
        
        // define a reference to the current flight
        Flight& flight = list.at(flightIndex);

        switch (option) {
            case '0':
                return;
                break;
            case '1':
                AddManyPassengers(flight);
                break;
            case '2':
                flight.RemovePassenger(GetInput<std::string>("enter name: "));
                break;
            case '3':
            case '4': // 3 and 4 equivalent by order insertion
                flight.PrintPassengers();
                break;
            case '5':
                flight.PrintPassengersReversed();
                break;
            default:
                InputError();
                break;
        }
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
                break;
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
};