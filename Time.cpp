#include "Time.h"
#include <iostream>

using namespace std;

const int kMinValidHms = 0;
const int kMaxValidHour = 23;
const int kMaxValidMs = 59;

Time::Time() {
    hour = 0;
    minute = 0;
    second = 0;
}
Time::Time(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

int Time::GetHour() const {
    return hour;
}

int Time::GetMinute() const {
    return minute;
}

int Time::GetSecond() const {
    return second;
}

void Time::SetHour(int h) {
    hour = h;
}

void Time::SetMinute(int m) {
    minute = m;
}

void Time::SetSecond(int s) {
    second = s;
}

void Time::SetHms(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

void Time::Print() const {
    cout << "Time: "<< hour << ":" << minute << ":" << second;
}

// ostream operator
ostream& operator << (ostream& os_object, const Time& time1) {
    os_object << "Time: "<< time1.hour << ":" << time1.minute << ":" << time1.second;
    return os_object;
}

// istream operator
istream& operator >> (istream& is_object, Time& time1){
    // declares the strings that used to take in the different parts of input
    string str_h, str_m, str_s;
    // declares the integers to store the hour, minute and second
    // that successfully converted from the input strings
    int h, m, s;

    // use ':' as the delimiter, delimit the origin input
    getline(is_object,str_h,':');
    getline(is_object,str_m,':');
    getline(is_object,str_s, ',');
    // if the process above is failed, just return to quit the whole process
    if (is_object.fail()) {
        return is_object;
    }

    // convert the strings into integers
    h = stoi(str_h);
    m = stoi(str_m);
    s = stoi(str_s);

    // if any of the three integers is invalid,
    // we will quit the whole process
    if (h < kMinValidHms || h > kMaxValidHour || m < kMinValidHms ||
        m > kMaxValidMs || s < kMinValidHms || s > kMaxValidMs) {
        is_object.clear(istream::badbit);
        return is_object;
    }
    // set the values of the object time1
    time1.SetHms(h, m, s);

    return is_object;
}

// Overloading "equal to" operator
bool Time::operator==(const Time& other_time) const {
    if (hour == other_time.hour && minute == other_time.minute
        && second == other_time.second)
        return true;
    else
        return false;
}

// Overloading "not equal to" operator
bool Time::operator!=(const Time& other_time) const {
    return !(*this == other_time);
}
