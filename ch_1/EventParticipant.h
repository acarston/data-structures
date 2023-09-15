#ifndef EVENTPARTICIPANT_H
#define EVENTPARTICIPANT_H

class EventParticipant {
    public:
        EventParticipant(const char* name, int age, const char* sex, const char* team);
    protected:
        const char* name;
        int age;
        const char* sex;
        const char* team;
};

#endif