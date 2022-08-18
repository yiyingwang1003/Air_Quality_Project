#include "AirQuality.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// initialize the constants
const int kNormalSign = 0;
const int kQuitSign = 1;
const int kReadFileFailSign = -1;
const double kInvalidData = -200;
const int kMinValidMonth = 1;
const int kMinValidYear = 1;
const int kMaxValidMonth = 12;

// declares the helper functions
int FileProcess(const string&, vector<AirQuality>&);
int Quit();
void Start(const vector<AirQuality>&);

int SpecifiedMonthCalculation(const vector<AirQuality>&, char);
void SpecifiedTimeCalculation(vector<AirQuality>);

double AvgCalculation(vector<AirQuality>, char, int, int);
void HighestCalculation(vector<AirQuality>, char, int, int);
void HigherThanAvg(vector<AirQuality>, char, int, int);

int main() {
// declares a vector to store the AirQuality objects
    vector<AirQuality> air_q;

    if (FileProcess("../AirQualityUCI.csv", air_q) == kReadFileFailSign) {
        return kReadFileFailSign;
    }

    cout << fixed << showpoint << setprecision(2);

    if (air_q.empty()) {
        return kQuitSign;
    }

    Start(air_q);

    return 0;
}

// The helper function that reads the csv file and stores valid data into a vector of AirQuality objects
int FileProcess(const string& file_path, vector<AirQuality>& air_q) {
    // declares the variables for reading file
    ifstream fp(file_path);
    string temp, line;
    AirQuality temp_air_quality;

    // open the file
    if (!fp.is_open()) {
        cout << "Cannot open the file " << endl;
        return kReadFileFailSign;
    }

    // skip the title row of the csv file
    getline(fp, temp);
    // read the remaining data line by line
    while(getline(fp, line)) {
        istringstream line_stream(line);
        if (line_stream >> temp_air_quality) {
            air_q.push_back(temp_air_quality);
        }
    }

    fp.close();
    return 0;
}

// The helper function that starts the whole user interaction process
void Start(const vector<AirQuality>& air_q) {
    // initializes a sign for the decision if we need to quit the program
    int sign = kNormalSign;

    // Prompts user to make the first choice of the first round, select the calculation the user want
    char choice1;
    cout << "Please choose what kind of calculation you want"
            "(enter 1/2/3/4 to choose, any other character to quit)" << endl;
    cout << "1. the average data of a specified month" << endl
         << "2. the highest data of a specified month" << endl
         << "3. the dates and times for a specified month when the data is higher than the average" << endl
         << "4. the temperature and relative humidity of a specified time" << endl;
    cout << "Your choice is: ";
    while(cin >> choice1) {
        switch (choice1) {
            // If the choice is 1/2/3 (means the calculation you want is based on a specified month),
            // call the corresponding helper function to do further steps
            case '1':
            case '2':
            case '3':
                // the further steps might change the value of sign
                sign = SpecifiedMonthCalculation(air_q, choice1);
                break;
                // If the choice is 4 (means the calculation you want is based on a specified time) ,
                // call the corresponding helper function to do further steps
            case '4':
                SpecifiedTimeCalculation(air_q);
                break;
                // Otherwise, change the value of the sign
            default:
                sign = kQuitSign;
        }

        // if a specified value is assigned to the sign, quit the input process
        if (sign == kQuitSign) {
            break;
        }
        // Prompts user to make the first choice of more rounds, select the calculation the user want
        cout << "--------------------------------------------------------------------------------------------" << endl;
        cout << "Please choose what kind of calculation you want(enter 1/2/3/4 to choose, any other character to quit)"
             << endl;
        cout << "1. the average data of a specified month" << endl
             << "2. the highest data of a specified month" << endl
             << "3. the dates and times for a specified month when the data is higher than the average" << endl
             << "4. the temperature and relative humidity of a specified time" << endl;
        cout << "Your choice is: ";
    }

    // if a specified value is assigned to the sign, quit the whole program
    if (sign == kQuitSign) {
        Quit();
    }
}

// the helper function that does the quit job
int Quit() {
    cout << "Quiting..." << endl;
    return kQuitSign;
}

// the helper function that prompts the user to enter the specified date and time,
// and displays the temperature and relative humidity at that date and time.
void SpecifiedTimeCalculation(vector<AirQuality> air_q) {
    string line;
    Date d1;
    Time t1;
    vector<AirQuality>::iterator air_q_it;
    bool found = false;
    // discards the characters in the input stream
    cin.ignore();
    // prompts the user to enter a valid date
    cout << "Please enter the date mm/dd/yyyy (example: 3/4/2004): " << endl;
    while (getline(cin, line)) {
        istringstream line_stream(line);
        if (!(line_stream >> d1)){
            cout << "Invalid input. The format is mm/dd/yyyy (example: 3/4/2004) and the numbers should be valid. "
                    << endl << "Please enter the date again: ";
        } else {
            break;
        }
    }
    // prompts the user to enter a valid time
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

    // traverses through the vector to find if there is corresponding data for the specified date and time
    for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
        if (air_q_it->GetDate() == d1 && air_q_it->GetTime() == t1) {
            cout << air_q_it->GetDate() << " " << air_q_it->GetTime() << " "
            << "temperature: " << air_q_it->GetTemperature() << " "
            << "relative humidity: "<< air_q_it->GetRelativeHumidity() << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "There is no data for \"" << d1 << " "<< t1 << "\""<< endl;
    }

}

// the helper function that prompts the user to enter the specified month and what kind of data the user want,
// and displays the specified data of that month.
int SpecifiedMonthCalculation(const vector<AirQuality>& air_q, char choice1) {
    char choice2;
    string line;
    int month, year;
    int sign = kNormalSign;

    // discards the characters in the input stream
    cin.ignore();
    // prompts the user to enter a valid month
    cout << "Please enter the specified month and year you want to know(example: 3 2004): " << endl;
    while (getline(cin, line)) {
        istringstream line_stream(line);
        if (line_stream >> month >> year) {
            if (month < kMinValidMonth || month > kMaxValidMonth || year < kMinValidYear) {
                cout << "Wrong input of month/year. month/year should be positive and month should be less than 13."
                << endl << "Please enter the month and year again(example: 3 2004): " << endl;
            } else {
                break;
            }
        } else {
            cout << "Invalid input. Please enter the month and year again(example: 3 2004): " << endl;
        }
    }

    // prompts the user to choose what kind of data the user want to calculate
    cout << "Please choose what kind of data you want to calculate"
            "(enter 1/2/3 to choose, any other character to quit)" << endl;
    cout << "1. temperature" << endl
         << "2. absolute humidity" << endl
         << "3. relative humidity" << endl;
    cout << "Your choice is: ";
    while (cin >> choice2) {
        // if the input is not 1/2/3, change the value of sign and return it to quit the process
        if (!(choice2 == '1' || choice2 == '2' || choice2 == '3')) {
            sign = kQuitSign;
            return sign;
        }
        break;
    }

    // according to two-step choices, call corresponding methods with the info the user entered to do relative calculation
    switch(choice1) {
        case '1':
            AvgCalculation(air_q, choice2, month, year);
            break;
        case '2':
            HighestCalculation(air_q, choice2, month, year);
            break;
        case '3':
            HigherThanAvg(air_q, choice2, month, year);
            break;
        default:
            sign = kQuitSign;
    }

    return sign;
}

// the helper function that displays the average temperature/absolute humidity/relative humidity of a specified month
double AvgCalculation(vector<AirQuality> air_q, char choice2, int month, int year) {
    // declares an iterator
    vector<AirQuality>::iterator air_q_it;
    // initializes the variables
    int count = 0;
    double total_t = 0, total_ah = 0, total_rh = 0;

    // traverses through the vector to find the data for the specified month and do addition
    for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
        if (air_q_it->GetDate().GetMonth() == month && air_q_it->GetDate().GetYear() == year) {
            total_t += air_q_it->GetTemperature();
            total_ah += air_q_it->GetAbsoluteHumidity();
            total_rh += air_q_it->GetRelativeHumidity();
            count++;
        }
    }

    // if there is no data for that month, print out relative statement and return
    if (count == 0) {
        cout << "There is no data for month \"" << month << "\" year \"" << year << "\"" << endl;
        return kInvalidData;
    }

    // calculates the average
    double avg_t = total_t / count;
    double avg_ah = total_ah / count;
    double avg_rh = total_rh / count;

    // displays the result due to the request of user
    if (choice2 == '1') {
        cout << "The average temperature of month \""
        << month << "\" year \"" << year << "\" is: " << avg_t << endl;
        return avg_t;
    }else if (choice2 == '2') {
        cout << "The average absolute humidity of month \""
        << month << "\" year \"" << year << "\" is: " << avg_ah << endl;
        return avg_ah;
    }else if (choice2 == '3') {
        cout << "The average relative humidity of month \""
        << month << "\" year \"" << year << "\" is: " << avg_rh << endl;
        return avg_rh;
    }

    return kInvalidData;
}

// the helper function that displays the highest temperature/absolute humidity/relative humidity of a specified month
void HighestCalculation(vector<AirQuality> air_q, char choice2, int month, int year) {
    // declares an iterator
    vector<AirQuality>::iterator air_q_it;
    // initializes the variables
    double high_t = kInvalidData;
    double high_ah = kInvalidData;
    double high_rh = kInvalidData;

    // traverses through the vector to find the highest data for the specified month
    for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
        if (air_q_it->GetDate().GetMonth() == month && air_q_it->GetDate().GetYear() == year) {
            if (air_q_it->GetTemperature() > high_t)
                high_t = air_q_it->GetTemperature();
            if (air_q_it->GetAbsoluteHumidity() > high_ah)
                high_ah = air_q_it->GetAbsoluteHumidity();
            if (air_q_it->GetRelativeHumidity() > high_rh)
                high_rh = air_q_it->GetRelativeHumidity();
        }
    }

    // displays the result due to the request of user
    if (choice2 == '1' && (high_t != kInvalidData)) {
        cout << "The highest temperature of month \""
        << month << "\" year \"" << year << "\" is: " << high_t << endl;
    }else if (choice2 == '2' && (high_ah != kInvalidData)) {
        cout << "The highest absolute humidity of month \""
        << month << "\" year \"" << year << "\" is: " << high_ah << endl;
    }else if (choice2 == '3' && (high_rh != kInvalidData)) {
        cout << "The highest relative humidity of month \""
        << month << "\" year \"" << year << "\" is: " << high_rh << endl;
    } else {
        cout << "There is no data for month \"" << month << "\" year \"" << year << endl;
    }
}

// the helper function that displays all the dates and times for a specified month,
// when the temperature/absolute humidity/relative humidity is higher than the average for that month
void HigherThanAvg(vector<AirQuality> air_q, char choice2, int month, int year) {
    // get the average value by calling another helper function
    double avg = AvgCalculation(air_q, choice2, month, year);
    // if the average is invalid, quit from the calculation
    if (avg == kInvalidData) {
        return;
    }
    // declares an iterator
    vector<AirQuality>::iterator air_q_it;

    // displays the results due to the request of user
    if (choice2 == '1') {
        cout << "The dates and months for month \"" << month << "\" year \""
             << year << "\" when the temperature is higher than the average are: " << endl;
        // traverses through the vector to find all the dates and times
        // when the temperature is higher than the average for that month
        for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
            if (air_q_it->GetDate().GetMonth() == month && air_q_it->GetDate().GetYear() == year) {
                if (air_q_it->GetTemperature() > avg) {
                    cout << air_q_it->GetDate() << " " << air_q_it->GetTime()
                    << " temperature: " << air_q_it->GetTemperature() << endl;
                }
            }
        }
    }
    if (choice2 == '2') {
        cout << "The dates and months for month \"" << month << "\" year \""
             << year << "\" when the absolute humidity is higher than the average are: " << endl;
        // traverses through the vector to find all the dates and times
        // when the absolute humidity is higher than the average for that month
        for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
            if (air_q_it->GetDate().GetMonth() == month && air_q_it->GetDate().GetYear() == year) {
                if (air_q_it->GetAbsoluteHumidity() > avg) {
                    cout << air_q_it->GetDate() << " " << air_q_it->GetTime()
                    << " absolute humidity: " << air_q_it->GetAbsoluteHumidity() << endl;
                }
            }
        }
    }
    if (choice2 == '3') {
        cout << "The dates and months for month \"" << month << "\" year \""
             << year << "\" when the relative humidity is higher than the average are: " << endl;
        // traverses through the vector to find all the dates and times
        // when the relative humidity is higher than the average for that month
        for(air_q_it = air_q.begin(); air_q_it != air_q.end(); air_q_it++) {
            if (air_q_it->GetDate().GetMonth() == month && air_q_it->GetDate().GetYear() == year) {
                if (air_q_it->GetRelativeHumidity() > avg) {
                    cout << air_q_it->GetDate() << " " << air_q_it->GetTime()
                    << " relative humidity: " << air_q_it->GetRelativeHumidity() << endl;
                }
            }
        }
    }
}