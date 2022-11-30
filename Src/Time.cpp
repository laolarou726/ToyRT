//
// Created by luoli on 2022/8/31.
//

#include "Time.h"
#include <iostream>

Time::Time() {
    minutes = 0;
}

Time::Time(double m) {
    minutes = m;
}

void Time::add(const Time &otherTimeObject) {
    minutes += otherTimeObject.minutes;
}

void Time::sub(const Time &otherTimeObject) {
    minutes -= otherTimeObject.minutes;
}

double Time::toMinutes() const {
    return minutes;
}

double Time::toHours() const {
    return minutes / 60;
}

double Time::toDays() const {
    return toHours() / 24;
}

void Time::printMinutes() const {
    std::cout << toMinutes() << " minutes" << std::endl;
}

void Time::printHours() const {
    std::cout << toHours() << " hours" << std::endl;
}

void Time::printDays() const {
    std::cout << toDays() << " days" << std::endl;
}
