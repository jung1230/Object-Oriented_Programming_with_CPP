#include <iostream>

// mytime.h
// simple Time class that follows C++ Primer Plus
#ifndef MYTIME_H_
#define MYTIME_H_
// This class represents a duration, not a specific time.
// As such, hours > 23 must be converted to days.
class Time {
    public:
        Time();
        Time(int d, int h);
        int GetDays() const;
        int GetHours() const;
        Time operator+(const Time &other) const;
        Time operator*(const int num) const;

        // need to use free or friend function for multiply a constant value with a Time object
        friend Time operator*(int constant, const Time &time);

        friend std::ostream& operator<<(std::ostream &os, const Time &time);

        Time operator*(const Time &other) const;

    private:
        int days;
        int hours;
};



#endif // MYTIME_H_

