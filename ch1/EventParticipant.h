#ifndef EVENTPARTICIPANT_H
#define EVENTPARTICIPANT_H

#include <string>

class EventParticipant {
    public:
        void setName(const std::string& name);
        void setSex(const std::string& sex);
        void setTeam(const std::string& team);
        void setAge(const std::string& age);
        void setPlace(int place);
        void setPoints(int points);

        std::string getName();
        std::string getSex();
        std::string getTeam();
        std::string getAge();
        int getPlace();
        int getPoints();

        virtual void setResult(std::string result);
        virtual std::string getResult();

    protected:
        std::string name, sex, team, age;
        int place, points;
};

#include "EventParticipant.cpp"
#endif