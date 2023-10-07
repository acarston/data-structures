#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

#include "../utils/SLList.h"

class Flight {
    public: 
        Flight() {};
        Flight(int id) { this->id = id; };

        int GetId() { return this->id; };

        void AddPassenger(std::string name) { this->passengers.orderInsert(name); };
        void RemovePassenger(std::string name) { this->passengers.removeFirst(name); };
        int FindPassengerIndex(std::string name) { return this->passengers.findFirst(name); };
        void PrintPassengers() { this->passengers.out(); };
        void PrintPassengersReversed() { this->passengers.outReversed(); };
    private:
        int id;
        SLList<std::string> passengers;
};

#endif