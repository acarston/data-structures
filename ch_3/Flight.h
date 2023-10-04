#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

#include "SLList.h"

class Flight {
    public: 
        Flight() {};
        Flight(int id) { this->id = id; };

        int GetId() { return this->id; };

        void AddPassenger(std::string name) { this->passengers.orderInsert(name); };
        void RemovePassenger(std::string name) { this->passengers.removeFirst(name); };
        void PrintPassengers() { this->passengers.out(); };
    private:
        int id;
        SLList<std::string> passengers;
};

#endif