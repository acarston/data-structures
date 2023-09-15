#ifndef FIELDPARTICIPANT_H
#define FIELDPARTICIPANT_H

#include "EventParticipant.cpp"

class FieldParticipant: EventParticipant {
    public:
        FieldParticipant(const char* name, int age, const char* sex, const char* team, double distance);
    private:
        double distance;
};

#endif