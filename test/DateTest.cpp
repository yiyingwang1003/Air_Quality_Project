#include "../Date.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {

    Date d1;
    d1.Print();
    cout << endl;

    Date d2(2022, 4, 14);
    d2.Print();
    cout << endl;

    cout << "year of d2: " << d2.GetYear() << endl;
    cout << "month of d2: " << d2.GetMonth() << endl;
    cout << "day of d2: " << d2.GetDay() << endl;

    d2.SetYear(2019);
    cout << "year of d2: " << d2.GetYear() << endl;
    d2.SetMonth(7);
    cout << "month of d2: " << d2.GetMonth() << endl;
    d2.SetDay(26);
    cout << "day of d2: " << d2.GetDay() << endl;

    d2.SetDmy(2008, 2, 5);
    d2.Print();
    cout << endl;

    cout << d2 << endl;

    string line;
    cout << "please enter a date(mm/dd/yyyy (example: 3/4/2004): ";
    while (getline(cin, line)) {
        istringstream line_stream(line);
        if (!(line_stream >> d1)){
            cout << "Invalid input. The format is mm/dd/yyyy (example: 3/4/2004) and the numbers should be valid. "
                 << endl << "Please enter the date again: ";
        } else {
            break;
        }
    }
    cout << d1;

    return 0;
}
