#include "AirQuality.h"

using namespace std;

const int kNumOfSkip = 10;
const double kInvalidData = -200;

AirQuality::AirQuality():date(),time() {
    temperature = 0;
    absolute_humidity = 0;
    relative_humidity = 0;
}

AirQuality::AirQuality(int y, int mo, int d, int h, int mi, int s, double t, double ah, double rh)
:date(y, mo, d),time(h, mi, s) {
    temperature = t;
    absolute_humidity = ah;
    relative_humidity = rh;
}

Date AirQuality::GetDate() {
    return date;
}

Time AirQuality::GetTime() {
    return time;
}

double AirQuality::GetTemperature() const {
    return temperature;
}

double AirQuality::GetAbsoluteHumidity() const {
    return absolute_humidity;
}

double AirQuality::GetRelativeHumidity() const {
    return relative_humidity;
}

void AirQuality::SetDate(int y, int mo, int d) {
    date.SetDmy(y, mo, d);
}

void AirQuality::SetDate(Date d1) {
    date = d1;
}

void AirQuality::SetTime(int y, int mi, int d) {
    time.SetHms(y, mi, d);
}

void AirQuality::SetTime(Time t1) {
    time = t1;
}

void AirQuality::SetTemperature(double t) {
    temperature = t;
}

void AirQuality::SetAbsoluteHumidity(double ah) {
    absolute_humidity = ah;
}

void AirQuality::SetRelativeHumidity(double rh) {
    relative_humidity = rh;
}

void AirQuality::Print() const {
    cout <<  date << " " << time << " "
         << "temperature: " << temperature << " "
         << "relative humidity: " << relative_humidity << " "
         << "absolute humidity: " << absolute_humidity << endl;
}

// ostream operator
ostream& operator << (ostream& os_object, const AirQuality& airQuality1) {
    os_object <<  airQuality1.date << " "
              << airQuality1.time << " "
              << "temperature: " << airQuality1.temperature << " "
              << "relative humidity: " << airQuality1.relative_humidity << " "
              << "absolute humidity: " << airQuality1.absolute_humidity;
    return os_object;
}

// istream operator
istream& operator >> (istream& is_object, AirQuality& airQuality1){
    // declares the strings that used to take in the different parts of input
    string str_t, str_ah, str_rh, temp;
    // declares the date and time
    Date date1;
    Time time1;
    // declares the doubles to store the temperature, relative humidity and absolute humidity
    // that successfully converted from the input strings
    double t, rh, ah;

    // quit the whole process if it is unable to read in the date object
    if (!(is_object >> date1)) {
        return is_object;
    }
    // quit the whole process if it is unable to read in the time object
    if (!(is_object >> time1)) {
        return is_object;
    }
    // skip the part of data we do not need
    for (int i = 0; i < kNumOfSkip; i++) {
        getline(is_object, temp, ',');
    }
    // use ',' as the delimiter, delimit the origin input
    getline(is_object, str_t, ',');
    getline(is_object, str_rh, ',');
    getline(is_object, str_ah, ',');
    if (is_object.fail()) {
        return is_object;
    }

    // convert the strings into doubles
    t = stod(str_t);
    rh = stod(str_rh);
    ah = stod(str_ah);

    // if any of the three doubles is equal to -200, which means the data is invalid,
    // we will quit the whole process
    if (t == kInvalidData || rh == kInvalidData || ah == kInvalidData) {
        is_object.clear(istream::badbit);
        return is_object;
    }

    // set the values of the object airQuality1
    airQuality1.SetDate(date1);
    airQuality1.SetTime(time1);
    airQuality1.SetTemperature(t);
    airQuality1.SetAbsoluteHumidity(ah);
    airQuality1.SetRelativeHumidity(rh);

    return is_object;
}
