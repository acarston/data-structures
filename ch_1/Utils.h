#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#include "EventParticipant.h"

class Utils {
    public:
        static void sort(int numParticipants, EventParticipant**& participants, std::string sortType);
        static void awardPlacesPoints(int numParticipants, EventParticipant**& participants, std::string sortType);
        static std::string getStrIn(std::string prompt);

    private:
        static void swap(EventParticipant*& par1, EventParticipant*& par2);
        static bool shouldSwap(std::string in, EventParticipant* par1, EventParticipant* par2);
};

#include "Utils.cpp"
#endif