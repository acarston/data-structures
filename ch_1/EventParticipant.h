#ifndef EVENTPARTICIPANT_H
#define EVENTPARTICIPANT_H

#include <string>

class EventParticipant {
    public:
        void setName(const std::string& name);
        void setSex(const std::string& sex);
        void setTeam(const std::string& team);
        void setAge(int age);
        virtual void setResult(int result);
    protected:
        std::string name, sex, team;
        int age;
};

#include "EventParticipant.cpp"
#endif