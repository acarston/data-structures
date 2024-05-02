#include "Utils.h"

// swap array elements
void Utils::swap(EventParticipant*& par1, EventParticipant*& par2) {
    EventParticipant* temp = par1;
    par1 = par2;
    par2 = temp;
}

// make comparison between array elements according to sort type
bool Utils::shouldSwap(std::string in, EventParticipant* par1, EventParticipant* par2) {
    auto result1 = par1->getResult();
    auto result2 = par2->getResult();

    // compare by distance
    if (in == "d") {
        return stod(result2) > stod(result1);
    }

    // compare by time
    if (in == "t") {
        // handle comparison in m:s format (no colon assumes minute)
        if (stod(result2.substr(0, result2.find(":"))) < stod(result1.substr(0, result1.find(":")))) return true;
        else if (stod(result2.substr(0, result2.find(":"))) > stod(result1.substr(0, result1.find(":")))) return false;
        else if (stod(result2.substr(result2.find(":")+1)) < stod(result1.substr(result1.find(":")+1))) return true;
        else return false;
    }

    std::string name1 = par1->getName();
    std::string name2 = par2->getName();

    // compare by name
    if (in == "n") {
        // prioritize last name in First Last format (no space assumes last name)
        return name2.substr(name2.find(" ")+1) < name1.substr(name1.find(" ")+1);
    }

    return false;
}

// change array order via bubble sort
void Utils::sort(int numParticipants, EventParticipant**& participants, std::string sortType) {
    bool loop = true;
    while (loop) {
        loop = false;
        for (int i = 0; i < numParticipants - 1; ++i) {
            if (shouldSwap(sortType, *(participants + i), *(participants + i + 1))) {   // use pointer arithmetic to retrieve elements
                swap(*(participants + i), *(participants + i + 1));     
                loop = true;
            }
        }
    }
}

// set place and points values based on current order
void Utils::awardPlacesPoints(int numParticipants, EventParticipant**& participants, std::string sortType) {
    for (int i = 1, j = 10; i < numParticipants + 1; ++i, j -= 2) {    // points (j) follow this arithmetic rule (except 6th)
        auto participant = *(participants + i - 1);

        // nullify place and points if sorting by name
        if (sortType == "n") {
            participant->setPlace(0);
            participant->setPoints(0);
            continue;
        }

        participant->setPlace(i);
        participant->setPoints(j);
        if (i == 6) participant->setPoints(1);
    }
}

// return user input from prompt
std::string Utils::getStrIn(std::string prompt) {
    std::cout << prompt;
    std::string temp;
    std::cin >> temp;
    return temp;
}