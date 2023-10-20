#pragma once

#include "EventParticipant.h"

void EventParticipant::setName(const std::string& name) { this->name = name; };
void EventParticipant::setSex(const std::string& sex) { this->sex = sex; };
void EventParticipant::setTeam(const std::string& team) { this->team = team; };
void EventParticipant::setAge(const std::string& age) { this->age = age; };
void EventParticipant::setPlace(int place) { this->place = place; };
void EventParticipant::setPoints(int points) { this->points = points; };

std::string EventParticipant::getName() { return name; };
std::string EventParticipant::getSex() { return sex; };
std::string EventParticipant::getTeam() { return team; };
std::string EventParticipant::getAge() { return age; };
int EventParticipant::getPlace() { return place; };
int EventParticipant::getPoints() { return points; };

/* implemented by children */
void EventParticipant::setResult(std::string result) { return; };
std::string EventParticipant::getResult() { return NULL; };