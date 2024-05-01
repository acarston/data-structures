#ifndef TRACKPARTICIPANT_H
#define TRACKPARTICIPANT_H

#include "EventParticipant.h"

class TrackParticipant: public EventParticipant {
    public:
        virtual std::string getResult();
        virtual void setResult(std::string result);
        
    private:
        std::string time;
};

#endif
