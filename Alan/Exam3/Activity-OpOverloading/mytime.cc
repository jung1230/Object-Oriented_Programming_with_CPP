#include "mytime.h"

Time::Time() : days(0), hours(0) {}

Time::Time(int d, int h) : days(d), hours(h) {}

int Time::GetDays() const {
    return days;
}

int Time::GetHours() const {
    return hours;
}

// Overload for +
Time Time::operator+(const Time &other) const{
    Time result;
    result.days = days + other.days;
    result.hours = hours + other.hours;

    if (result.hours >= 24) {
        result.days += result.hours / 24;
        result.hours %= 24;
    }

    return result;
}

// Overload for *
Time Time::operator*(const int num) const{
    Time result;
    result.days = days * num;
    result.hours = hours *num;

    if (result.hours >= 24) {
        result.days += result.hours / 24;
        result.hours %= 24;
    }

    return result;
}


Time operator*(int num, const Time &time) {
    Time result;
    result.days = num * time.days;
    result.hours = num * time.hours;

    if (result.hours >= 24) {
        result.days += result.hours / 24;
        result.hours %= 24;
    }

    return result;
}

std::ostream& operator<<(std::ostream &os, const Time &time) {
    os << time.days << " days, " << time.hours << " hours ";
    return os;
}

Time Time::operator*(const Time &other) const{
    Time result;
    result.days = days * other.days;
    result.hours = hours * other.hours;

    if (result.hours >= 24) {
        result.days += result.hours / 24;
        result.hours %= 24;
    }

    return result;

}
