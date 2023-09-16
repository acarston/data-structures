#include <iostream>

#include "EventParticipant.h"
#include "FieldParticipant.h"
#include "TrackParticipant.h"

using namespace std;

string getStrIn(std::string prompt) {
    cout << prompt;
    std::string temp;
    cin >> temp;
    return temp;
};

int main() {
    bool yo = ("a" > "n");

    const int MAX_PARTICIPANTS = 100;
    EventParticipant* participants[MAX_PARTICIPANTS];

    char input;

    cout << "enter \'t\', \'f\', or \'d\' for track event, field event, or DRIVER respectively: ";
    cin >> input;

    if (input == 'd'); // TODO
    else if (!(input == 't' || input == 'f')) return 0;

    bool is_track = input == 't';
    int i;
    for (i = 0; i < MAX_PARTICIPANTS; ++i) {
        if (is_track) {
            participants[i] = new TrackParticipant(); 
            participants[i]->setResult(stod(getStrIn("enter TIME: ")));
        }
        else {
            participants[i] = new FieldParticipant(); 
            participants[i]->setResult(stod(getStrIn("enter DISTANCE: ")));
        }

        participants[i]->setName(getStrIn("enter NAME (Last, First): "));
        participants[i]->setTeam(getStrIn("enter TEAM: "));
        participants[i]->setSex(getStrIn("enter SEX: "));
        participants[i]->setAge(stoi(getStrIn("enter AGE: ")));

        if (getStrIn("\nnew entry? [y/n]: ") != "y") break;
    }

    std::string sort;
    cout << "sort by? ";
    sort = is_track ? getStrIn("[t/n] (time, name): ") : getStrIn("[d/n] (distance, name): ");


    // for (int j = 0; j <= i; ++j) {
    // }

    cout << endl;

    return 0;
}