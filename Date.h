#ifndef FINAL_PROJECT_DATE_H
#define FINAL_PROJECT_DATE_H
#include <iostream>
using namespace std;

class Date {

    // method overloading
    friend ostream& operator << (ostream&, const Date&);
    friend istream& operator >> (istream&, Date&);

public:
    // default constructor
    Date();

    // specific constructor
    Date(int y, int m, int d);

    // getters
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

    // setters
    void SetYear(int y);
    void SetMonth(int m);
    void SetDay(int d);
    void SetDmy(int y, int m, int d);

    // print info
    void Print() const;

    // Overloading operators
    bool operator==(const Date& other_date) const;
    bool operator!=(const Date& other_date) const;

private:
    int year;
    int month;
    int day;
};

#endif //FINAL_PROJECT_DATE_H
