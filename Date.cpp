#include <iostream>
#include "Date.h"

using namespace std;

const int kMinValidMonth = 1;
const int kMinValidDay = 1;
const int kMinValidYear = 1;
const int kMaxValidMonth = 12;
const int kMaxValidDay = 31;

Date::Date() {
    year = 2000;
    month = 1;
    day = 1;
}
Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

int Date::GetYear() const {
    return year;
}

int Date::GetMonth() const {
    return month;
}

int Date::GetDay() const {
    return day;
}

void Date::SetYear(int y) {
    year = y;
}

void Date::SetMonth(int m) {
    month = m;
}

void Date::SetDay(int d) {
    day = d;
}

void Date::SetDmy(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

void Date::Print() const {
    cout << "Date: " << month << "/" << day << "/" << year;
}

// ostream operator
ostream& operator << (ostream& os_object, const Date& date1) {
    os_object <<"Date: " <<  date1.month << "/" << date1.day << "/" << date1.year;
    return os_object;
}

// istream operator
istream& operator >> (istream& is_object, Date& date1){
    // declares the strings that used to take in the different parts of input
    string str_y, str_m, str_d;
    // declares the integers to store the year, month and day
    // that successfully converted from the input strings
    int y, m, d;

    // use '/' as the delimiter, delimit the origin input
    getline(is_object,str_m,'/');
    getline(is_object,str_d,'/');
    getline(is_object,str_y, ',');
    // if the process above is failed, just return to quit the whole process
    if (is_object.fail()) {
        return is_object;
    }

    // convert the strings into integers
    y = stoi(str_y);
    m = stoi(str_m);
    d = stoi(str_d);

    // if any of the three integers is invalid,
    // we will quit the whole process
    if (m < kMinValidMonth || m > kMaxValidMonth || d < kMinValidDay
        || d > kMaxValidDay || y < kMinValidYear) {
        is_object.clear(istream::badbit);
        return is_object;
    }
    // set the values of the object date1
    date1.SetDmy(y, m, d);

    return is_object;
}

// Overloading "equal to" operator
bool Date::operator==(const Date& other_date) const {
    if (year == other_date.year && month == other_date.month
        && day == other_date.day)
        return true;
    else
        return false;
}

// Overloading "not equal to" operator
bool Date::operator!=(const Date& other_date) const {
    return !(*this == other_date);
}
