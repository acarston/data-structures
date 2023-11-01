#ifndef FIELDPARTICIPANT_H
#define FIELDPARTICIPANT_H

#include "EventParticipant.h"

class FieldParticipant: public EventParticipant {
    public:
        virtual std::string getResult();
        virtual void setResult(std::string result);
        
    private:
        std::string distance;
};

//#include "FieldParticipant.cpp"
#endif