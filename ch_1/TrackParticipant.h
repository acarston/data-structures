#ifndef TRACKPARTICIPANT_H
#define TRACKPARTICIPANT_H

#include "EventParticipant.cpp"

class TrackParticipant: EventParticipant {
    public:
        TrackParticipant(const char* name, int age, const char* sex, const char* team, const char* time);
    private:
        const char* time;
};

#endif