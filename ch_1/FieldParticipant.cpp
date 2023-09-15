#include "FieldParticipant.h"

FieldParticipant::FieldParticipant(const char* name, int age, const char* sex, const char* team, double distance): EventParticipant::EventParticipant(name, age, sex, team) {
    this->distance = distance;
}