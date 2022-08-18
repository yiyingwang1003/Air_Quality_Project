#include "../Time.h"
#include <sstream>
#include <iostream>

using namespace std;

int main() {

    Time t1;
    t1.Print();
    cout << endl;

    Time t2(18, 42, 15);
    t2.Print();
    cout << endl;

    cout << "Hour of t2: " << t2.GetHour() << endl;
    cout << "Minute of t2: " << t2.GetMinute() << endl;
    cout << "Second of t2: " << t2.GetSecond() << endl;

    t2.SetHour(20);
    cout << "Hour of t2: " << t2.GetHour() << endl;
    t2.SetMinute(35);
    cout << "Minute of t2: " << t2.GetMinute() << endl;
    t2.SetSecond(40);
    cout << "Second of t2: " << t2.GetSecond() << endl;

    t2.SetHms(8, 1, 55);
    t2.Print();
    cout << endl;

    cout << t2 << endl;

    string line;
    cout << "Please enter the time hh:mm:ss (example: 18:00:00): " << endl;
    while (getline(cin, line)) {
        istringstream line_stream(line);
        if (!(line_stream >> t1)){
            cout << "Invalid input. The format is hh:mm:ss (example: 18:00:00) and the numbers should be valid. "
                 << endl << "Please enter the time again: ";
        } else {
            break;
        }
    }
    cout << t1;

    return 0;
}
