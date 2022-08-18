#ifndef FINAL_PROJECT_AIRQUALITY_H
#define FINAL_PROJECT_AIRQUALITY_H
#include "Date.h"
#include "Time.h"

using namespace std;

class AirQuality {

    // method overloading
    friend ostream& operator << (ostream&, const AirQuality&);
    friend istream& operator >> (istream&, AirQuality&);

public:
    // default constructor
    AirQuality();
    // specific constructor
    AirQuality(int y, int mo, int d, int h, int mi, int s, double t, double ah, double rh);

    // getters
    Date GetDate();
    Time GetTime();
    double GetTemperature() const;
    double GetAbsoluteHumidity() const;
    double GetRelativeHumidity() const;

    // setters
    void SetDate(int y, int mo, int d);
    void SetDate(Date d1);
    void SetTime(int h, int mi, int s);
    void SetTime(Time t1);
    void SetTemperature(double t);
    void SetAbsoluteHumidity(double ah);
    void SetRelativeHumidity(double rh);

    // print info
    void Print() const;

private:
    Date date;
    Time time;
    double temperature;
    double absolute_humidity;
    double relative_humidity;

};

#endif //FINAL_PROJECT_AIRQUALITY_H
