#ifndef FINAL_PROJECT_TIME_H
#define FINAL_PROJECT_TIME_H
#include <iostream>

using namespace std;

class Time {
    // method overloading
    friend ostream& operator << (ostream&, const Time&);
    friend istream& operator >> (istream&, Time&);

public:
    // default constructor
    Time();

    // specific constructor
    Time(int h, int m, int s);

    // getters
    int GetHour() const;
    int GetMinute() const;
    int GetSecond() const;

    // setters
    void SetHour(int h);
    void SetMinute(int m);
    void SetSecond(int s);
    void SetHms(int h, int m, int s);

    // print info
    void Print() const;

    // Overloading operators
    bool operator==(const Time& other_date) const;
    bool operator!=(const Time& other_date) const;

private:
    int hour;
    int minute;
    int second;
};

#endif //FINAL_PROJECT_TIME_H
