#include "TrackParticipant.h"

TrackParticipant::TrackParticipant(const char* name, int age, const char* sex, const char* team, const char* time): EventParticipant::EventParticipant(name, age, sex, team) {
    this->time = time;
}