#include <iostream>
#include <iomanip>

#include "EventParticipant.h"
#include "FieldParticipant.h"
#include "TrackParticipant.h"
#include "Utils.h"

// input participants & return array of EventParticipant pointers
EventParticipant** inputEvents(bool isTrack, int& it) {
    // initialize array of base class pointers to avoid multiple arrays
    static EventParticipant* participants[100];

    for (it = 0; it < 100; ++it) {
        // dynamically allocate for each entry
        if (isTrack) {
            participants[it] = new TrackParticipant(); 
            participants[it]->setResult(Utils::getStrIn("enter TIME (m:s): "));
        }
        else {
            participants[it] = new FieldParticipant(); 
            participants[it]->setResult(Utils::getStrIn("enter DISTANCE: "));
        }

        participants[it]->setName(Utils::getStrIn("enter NAME (First Last): "));
        participants[it]->setTeam(Utils::getStrIn("enter TEAM: "));
        participants[it]->setSex(Utils::getStrIn("enter SEX: "));
        participants[it]->setAge(Utils::getStrIn("enter AGE: "));

        if (Utils::getStrIn("\nnew entry? [y/n]: ") != "y") {
            ++it;   // modify iterator to reflect number of entries
            return participants;
        }
    }
    return participants;
}

void displayOutput(int numParticipants, EventParticipant** participants, bool isTrack) {
    std::cout << "\n" << std::left << std::setw(24) << "NAME" << std::setw(24) << "TEAM" << std::setw(12) << "GENDER" << std::setw(12) << "AGE"; 
    if (isTrack) std::cout << std::setw(12) << "TIME";
    else std::cout << std::setw(12) << "DISTANCE";
    std::cout << std::setw(12) << "PLACE" << std::setw(12) << "POINTS" << "\n";

    for (int i = 0; i < numParticipants; ++i) {
        auto el = *(participants + i);  // get array element
        std::cout << std::left << std::setw(24) << el->getName() << std::setw(24) << el->getTeam() << std::setw(12) << el->getSex()
        << std::setw(12) << el->getAge() << std::setw(12) << el->getResult() << std::setw(12) << el->getPlace() << std::setw(12) << el->getPoints() << "\n";
    }
}

// test all functions for a 'track' event
void driver() {
    const int NUM_PARTICIPANTS = 6;
    EventParticipant* participants[NUM_PARTICIPANTS];
    for (int i = 0; i < NUM_PARTICIPANTS; ++i) participants[i] = new TrackParticipant();
    EventParticipant** participant = participants;  // required by function call for some reason

    participants[0]->setAge("42");
    participants[1]->setAge("20");
    participants[2]->setAge("17");
    participants[3]->setAge("26");
    participants[4]->setAge("29");
    participants[5]->setAge("39");

    participants[0]->setName("Joe Smith");
    participants[1]->setName("Aaron Carston");
    participants[2]->setName("Dale Hamilton");
    participants[3]->setName("Timothy Zink");
    participants[4]->setName("Icarus");
    participants[5]->setName("Name");

    participants[0]->setResult("123:4");
    participants[1]->setResult("45:45.5");
    participants[2]->setResult("70:300.6");
    participants[3]->setResult("45.45.6");
    participants[4]->setResult("0:6");
    participants[5]->setResult("0:78");

    participants[0]->setSex("Male");
    participants[1]->setSex("Male");
    participants[2]->setSex("Male");
    participants[3]->setSex("Male");
    participants[4]->setSex("Male");
    participants[5]->setSex("Female");

    participants[0]->setTeam("ZZZ");
    participants[1]->setTeam("NNU");
    participants[2]->setTeam("ANU");
    participants[3]->setTeam("QWT");
    participants[4]->setTeam("Greece");
    participants[5]->setTeam("Earth");

    Utils::sort(NUM_PARTICIPANTS, participant, "n");
    Utils::awardPlacesPoints(NUM_PARTICIPANTS, participant, "n");
    displayOutput(NUM_PARTICIPANTS, participants, true);

    Utils::sort(NUM_PARTICIPANTS, participant, "t");
    Utils::awardPlacesPoints(NUM_PARTICIPANTS, participant, "t");
    displayOutput(NUM_PARTICIPANTS, participants, true);
}

// get inputs and show output
void userInterface() {
    // input event type
    std::string input;
    while (!(input == "t" || input == "f" || input == "d")) {
        input = Utils::getStrIn("enter \'t\', \'f\', or \'d\' for track event, field event, or DRIVER respectively: ");
    }

    if (input == "d") {
        driver(); 
        return;
    }

    int numParticipants;
    bool isTrack = input == "t";
    EventParticipant** participants = inputEvents(isTrack, numParticipants);

    // input sort type
    std::string sortType;
    while (!(sortType == "t" || sortType == "n" || sortType == "d")) {
        std::cout << "\nsort by? ";
        sortType = isTrack ? Utils::getStrIn("[t/n] (time, name): ") : Utils::getStrIn("[d/n] (distance, name): ");
    }

    Utils::sort(numParticipants, participants, sortType);
    Utils::awardPlacesPoints(numParticipants, participants, sortType);
    displayOutput(numParticipants, participants, isTrack);
}

int main() {
    userInterface();
    std::cout << std::endl;
}
