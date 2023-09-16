#ifndef TRACKPARTICIPANT_H
#define TRACKPARTICIPANT_H

#include "EventParticipant.h"

class TrackParticipant: public EventParticipant {
    // public:
    //     TrackParticipant(const char* name, int age, const char* sex, const char* team, const char* time);
    private:
        const char* time;
};

#include "TrackParticipant.cpp"
#endif