#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>

#include "SLList.h"

class Flight {
    public: 
        Flight(int id) { this->id = id; };

        int getId() { return this->id; };

        void addPassenger(std::string name) { this->passengers.orderInsert(name); };
        void removePassenger(std::string name) { this->passengers.removeFirst(name); };
        void printPassengers() { this->passengers.out(); };
    private:
        int id;
        SLList<std::string> passengers;
};

#endif