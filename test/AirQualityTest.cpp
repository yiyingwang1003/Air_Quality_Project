#include "../AirQuality.h"
#include <sstream>
#include <iostream>

using namespace std;

int main() {

    AirQuality a1;
    a1.Print();
    cout << endl;
    cout << a1 << endl;

    AirQuality a2(2022, 4, 14, 18, 42, 15, 20.0, 0.11, 35.4);
    a2.Print();
    cout << endl;

    cout << "Date of a2: " << a2.GetDate() << endl;
    cout << "Time of a2: " << a2.GetTime() << endl;
    cout << "Temperature of a2: " << a2.GetTemperature() << endl;
    cout << "Absolute humidity of a2: " << a2.GetAbsoluteHumidity() << endl;
    cout << "Relative humidity of a2: " << a2.GetRelativeHumidity() << endl;

    Date d1;
    a2.SetDate(d1);
    cout << "Date of a2: " << a2.GetDate() << endl;
    a2.SetDate(2001, 1, 1);
    cout << "Date of a2: " << a2.GetDate() << endl;

    Time t1;
    a2.SetTime(t1);
    cout << "Time of a2: " << a2.GetTime() << endl;
    a2.SetTime(1,1,1);
    cout << "Time of a2: " << a2.GetTime() << endl;

    a2.SetTemperature(40.1);
    cout << "Temperature of a2: " << a2.GetTemperature() << endl;

    a2.SetAbsoluteHumidity(0.22);
    cout << "Absolute humidity of a2: " << a2.GetAbsoluteHumidity() << endl;

    a2.SetRelativeHumidity(55.2);
    cout << "Relative humidity of a2: " << a2.GetRelativeHumidity() << endl;

    string line;
    cout << "Please enter: " << endl;
    // enter : 3/10/2004,20:00:00,,,,,,,,,,,11.9,54.0,0.22,,
    while (getline(cin, line)) {
        istringstream line_stream(line);
        if (!(line_stream >> a1)){
            cout << "Invalid input. Please enter the AirQuality again: ";
        } else {
            break;
        }
    }
    cout << a1;

    return 0;
}

