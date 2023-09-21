#include "Utils.h"

void Utils::swap(EventParticipant*& par1, EventParticipant*& par2) {
    EventParticipant* temp = par1;
    par1 = par2;
    par2 = temp;
};

bool Utils::shouldSwap(std::string in, EventParticipant* par1, EventParticipant* par2) {
    auto result1 = par1->getResult();
    auto result2 = par2->getResult();
    if (in == "d") {
        return stod(result2) > stod(result1);
    }
    if (in == "t") {
        if (stod(result2.substr(0, result2.find(":"))) < stod(result1.substr(0, result1.find(":")))) return true;
        else if (stod(result2.substr(0, result2.find(":"))) > stod(result1.substr(0, result1.find(":")))) return false;
        else if (stod(result2.substr(result2.find(":")+1)) < stod(result1.substr(result1.find(":")+1))) return true;
        else return false;
    }

    std::string name1 = par1->getName();
    std::string name2 = par2->getName();
    if (in == "n") {
        return name2.substr(name2.find(" ")+1) < name1.substr(name1.find(" ")+1);
    }

    return false;
};

void Utils::sort(int numParticipants, EventParticipant**& participants, std::string sortType) {
    bool loop = true;
    while (loop) {
        loop = false;
        for (int i = 0; i < numParticipants - 1; ++i) {
            if (shouldSwap(sortType, *(participants + i), *(participants + i + 1))) {
                swap(*(participants + i), *(participants + i + 1));
                loop = true;
            }
        }
    }
};

void Utils::awardPlacesPoints(int numParticipants, EventParticipant**& participants, std::string sortType) {
    for (int i = 1, j = 10; i < numParticipants + 1; ++i, j -= 2) {
        auto participant = *(participants + i - 1);

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

std::string Utils::getStrIn(std::string prompt) {
    std::cout << prompt;
    std::string temp;
    std::cin >> temp;
    return temp;
};