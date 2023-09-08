// BusTour.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <StaticVectorLibrary.h>
#include <LinkedListLibrary.h>

#define TIME_COUNT 50

class Time {
public:
    int hour;
    int minute;

    Time() : hour(0), minute(0) {}

    Time(int h, int m) : hour(h), minute(m) {}

    Time(std::string input) {
        hour = (input[0] - '0') * 10 + (input[1] - '0');
        minute = (input[3] - '0') * 10 + (input[4] - '0') ;
    }
    int operator-(const Time& other) const {
        int thisMinutes = hour * 60 + minute;
        int otherMinutes = other.hour * 60 + other.minute;
        int diffMinutes = thisMinutes - otherMinutes;

        // Ensure the result is always positive
        if (diffMinutes < 0) {
            diffMinutes = -diffMinutes;
        }

        return diffMinutes;
    }

    Time operator+(int minutes) const {
        int total_minutes = hour * 60 + minute;
        total_minutes += minutes;

        int new_hour = total_minutes / 60;
        int new_minute = total_minutes % 60;

        if (new_hour >= 24) {
            new_hour %= 24; // Ensure the hour does not exceed 24
        }

        return Time(new_hour, new_minute);
    }

    // Overload the < operator to compare two Time objects
    bool operator<(const Time& other) const {
        if (hour < other.hour) {
            return true;
        } else if (hour == other.hour) {
            return minute < other.minute;
        } else {
            return false;
        }
    }

    // Overload the == operator to compare two Time objects for equality
    bool operator==(const Time& other) const {
        return (hour == other.hour) && (minute == other.minute);
    }

    int GetHour() {
        return hour;
    }
    
    int GetMinutes() {
        return minute;
    }

};

std::ostream& operator<<(std::ostream& os, Time& time) {
    os << "(" << time.GetHour() << ":" << time.GetMinutes() << ") ";
    return os;
}

void readInput(StaticVector<Time, TIME_COUNT>& busTimes) {

    std::string input[] = { "10.09", "10.10", "10.10", "10.12", "10.12", "10.14", "10.15", "10.15", "10.16", "10.18", "10.18", "10.20", "10.20", "-1"};

    int i = 0;
    while (input[i].compare("-1") != 0 ) {
        Time temp;
        temp.hour = (input[i][0] - '0') * 10 + (input[i][1] - '0');
        temp.minute = (input[i][3] - '0') * 10 + (input[i][4] - '0');

        busTimes.PushBack(temp);
        i++;
    }
}




int main() {

    StaticVector<Time, TIME_COUNT> busTimes;
    bool visited[TIME_COUNT] = { false };

    readInput(busTimes);

    for (int i = 0; i < busTimes.GetSize(); ++i) {

        if (visited[i]) // Node is already visited
            continue;


        StaticVector<Time, TIME_COUNT> maximumPattern;
        int maximumPeriodCount = 0;

        for (int j = i + 1; j < busTimes.GetSize(); ++j) {

            if (visited[j]){ // Node is already visited 
                continue;
            }


            int busPeriod = busTimes[j] - busTimes[i]; // Found a value for bus period to try.
            if(busPeriod == 0)
                continue;

            int periodCount = 1; // This was the possible first period 
            StaticVector<Time, TIME_COUNT> foundPattern;

            foundPattern.PushBack(busTimes[i]);
            foundPattern.PushBack(busTimes[j]);
            for (int k = j + 1; k < busTimes.GetSize(); ++k) {
                if (visited[k])
                    continue;

                Time nextPeriodPrediction = busTimes[j] + busPeriod * periodCount;

                if (nextPeriodPrediction < busTimes[k])  //If there is a contradiction stop operating
                    break;

                else if (nextPeriodPrediction == busTimes[k]) { // If there is equality in pattern add it to pattern
                    foundPattern.PushBack(busTimes[k]);
                    periodCount++;
                }
            }

            if (periodCount >= maximumPeriodCount) {
                maximumPeriodCount = periodCount;
                maximumPattern = foundPattern;
            }
        }

        int patternSize = 0;

        for (int k = 0; k < maximumPattern.GetSize(); ++k) {
            for (int l = 0; l < busTimes.GetSize(); ++l) {
                
                if (patternSize == maximumPattern.GetSize())
                    break;

                if (maximumPattern[k] == busTimes[l] && !visited[l]) {
                    visited[l] = true;
                    patternSize++;
                    break;
                }
            }
        }

        if(maximumPattern.GetSize() > 0)
            std::cout << "Found pattern is " << maximumPattern << std::endl;
    }

    return 0;
}



/*
int[] times;
bool[] visited = { false };

for (int i = 0; i < times.size(); ++i) {
    if (visited[i]) continue;

    int temp_times[] = subtract_element(times, times[i]);
    int maxlength = 0, period;
    int maxpattern[];
    //Try all possible periods for i'th item
    for (int j = i + 1; j < times.size(); ++j) {
        if (visited[j]) continue;
        int pred_period = temp_times[j] //Predicted period is temp_times[j]
            int pattern[];
        int length = 1;

        //Try to find a recurring pattern with period = temp_times[j]
        for (int k = j + 1; j < times.size(); ++k) {
            if (visited[k]) continue;
            int expected_time = (length + 1) * pred_period;

            //There is no possible value for rest of the array
            if (expected_time < temp_times[k]) break;

            else if (expected_time == temp_times[k]) {
                length++;
                pattern.push_back(k);
            }
        }

        if (length > maxlength) {
            maxlength = length;
            maxpattern = pattern;
            period = pred_period;
        }
    }

    visited[elements of the maxpattern] = true;
}
*/