#ifndef FIELDPARTICIPANT_H
#define FIELDPARTICIPANT_H

#include "EventParticipant.h"

class FieldParticipant : public EventParticipant {
    private:
        double distance;
};

#include "FieldParticipant.cpp"
#endif