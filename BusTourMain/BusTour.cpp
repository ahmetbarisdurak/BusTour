// BusTour.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <StaticVectorLibrary.h>
#include <LinkedListLibrary.h>

#define TIME_COUNT 60

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

    std::string input[] = { "10.03", "10.05", "10.08", "10.10", "10.10", "10.15", "10.15", "10.17", "10.20", "10.25", "-1"};

    int i = 0;
    while (input[i].compare("-1") != 0 ) {
        Time temp;
        temp.hour = (input[i][0] - '0') * 10 + (input[i][1] - '0');
        temp.minute = (input[i][3] - '0') * 10 + (input[i][4] - '0');

        busTimes.PushBack(temp);
        i++;
    }
}

Time CreateBusStartTime(Time startTime, Time endTime) {

    bool checkTime = false;
    int startHour, startMinute;
    //std::cout << "Creating bus start time" << std::endl;

    while (!checkTime) {
        
        startHour = rand() % 24;
        startMinute = rand() % 60;

        Time busStartTime(startHour, startMinute);

        if (!(busStartTime < startTime) && busStartTime < endTime)
            return busStartTime;

    }
    
    return startTime;
}

void CreateBusPeriod(StaticVector<Time, TIME_COUNT>& busTimes, int busNumber, Time startTime, Time endTime) {

    int i = 0;
    while(i < busNumber) {
        int busPeriod = rand() % 30;

        Time busStartTime = CreateBusStartTime(startTime, endTime);
        
        std::cout << "Bus start time is " << busStartTime << " ";

        if (endTime < busStartTime + busPeriod)
            continue;

        while (busStartTime == endTime || busStartTime < endTime) {
            busTimes.PushBack(busStartTime);

            busStartTime = busStartTime + busPeriod;
        }

       
        std::cout << "Bus period is " << busPeriod << std::endl;
    
        //std::cout << busTimes;
        //std::cout << "\n--------------------------------" << std::endl;
        i++;

    }


}

bool CompareTime(const Time& time1, const Time& time2) {
    return !(time1 < time2);
}
/*
Vector<int, MAX_PULSE> toa;
Vector<bool, MAX_PULSE> marks;

Vector<Vector<int, MAX_PULSE>, MAX_GROUP> stable_groups;
Vector<int, MAX_PULSE> stable_periods;

Vector<Vector<int, MAX_GROUP>, MAX_GROUP> staggering_groups;
Vector<Vector<int, MAX_PULSE>, MAX_GROUP> all_staggering_groups;



void extract_staggering_groups(Vector<Vector<int, MAX_PULSE>, MAX_GROUP>& groups, Vector<Vector<int, MAX_GROUP>, MAX_GROUP>& groups2) {
    Vector<int, MAX_GROUP> periods;

    for (int i = 0; i < toa.size(); ++i) {
        if (marks[i]) continue;

        int maxlen = 0;
        int period = 0;
        double maxscore = 0;

        Vector<int, MAX_PULSE> temparr = toa;
        Vector<int, MAX_PULSE> visited;

        subtract_element(i, temparr);

        if (DEBUG) {
            std::cout << "Times: " << temparr << std::endl;
            std::cout << "Checked: " << marks << std::endl;
        }

        for (int j = i + 3; j < temparr.size(); ++j) {
            if (marks[j] || toa[j] - toa[i] > MAX_STAGGER_PERIOD) continue;

            int est_period = temparr[j];
            int prev = temparr[j];
            int length = 1;

            Vector<int, MAX_PULSE> visited_tmp;

            visited_tmp.push_back(i);
            visited_tmp.push_back(j);

            for (int k = j + 1; k < temparr.size(); ++k) {
                if (marks[k]) continue;

                int expected_time = (length + 1) * est_period;

                if (temparr[k] > expected_time) break; //There is no possible value for rest of the array
                else if (temparr[k] == expected_time) {
                    length++;
                    visited_tmp.push_back(k);
                }
            }

            est_period = toa[visited_tmp[1]] - toa[visited_tmp[0]];

            for (int k = 0; k < groups.size(); ++k) {
                if (groups[k].size() == visited_tmp.size() && est_period == periods[k]) {
                    maxlen = 0;
                    length = 0;
                    periods.push_back(est_period);
                    groups.push_back(visited_tmp);
                    break;
                }
            }

            if (length >= 2 && est_period > period) {
                period = est_period;
                visited = visited_tmp;
                maxlen = length;
            }
        }

        if (maxlen != 0) {
            periods.push_back(period);
            groups.push_back(visited);
        }
    }

    if (PRINT_GROUPS) {
        std::cout << "STAGGER GROUPS:" << std::endl;
        for (int i = 0; i < groups.size(); ++i) {
            std::cout << "index: " << i << " period " << periods[i] << " -- >";
            for (int j = 0; j < groups[i].size(); ++j) {
                std::cout << toa[groups[i][j]] << ", ";
            }
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;

    Vector<bool, MAX_GROUP> group_marks;

    for (int i = 0; i < groups.size(); ++i) group_marks.push_back(false);

    for (int i = 0; i < groups.size(); ++i) {
        if (group_marks[i]) continue;
        Vector<int, MAX_GROUP> visited;
        visited.push_back(i);

        for (int j = i + 1; j < groups.size(); ++j) {
            if (groups[i].size() != groups[j].size()) continue;

            if (periods[i] == periods[j])
                visited.push_back(j);
        }

        for (int j = 0; j < visited.size(); ++j) group_marks[visited[j]] = true;
        if (visited.size() >= 3) {
            groups2.push_back(visited);
        }
    }

    for (int i = 0; i < groups.size(); ++i) {
        if (group_marks[i]) continue;
        Vector<int, MAX_GROUP> visited;
        visited.push_back(i);

        for (int j = i + 1; j < groups.size(); ++j) {
            if (groups[i].size() != groups[j].size()) continue;

            if (periods[i] == periods[j])
                visited.push_back(j);
        }

        for (int j = 0; j < visited.size(); ++j) group_marks[visited[j]] = true;
        if (visited.size() >= 3) {
            groups2.push_back(visited);
        }
    }


    /*std::cout << "GROUP COUNT: " << groups2.size() << std::endl;
    for (int i = 0; i < groups2.size(); ++i) {
        for (int j = 0; j < groups2[i].size(); ++j) {
            for (int k = 0; k < groups[groups2[i][j]].size(); ++k) {
                std::cout << times[groups[groups2[i][j]][i]] << ", ";
            }
            std::cout << " | ";
        }

        std::cout << std::endl;
    }*/
/*
    std::cout << "STAGGER GROUP COUNT: " << groups2.size() << std::endl;
    for (int i = 0; i < groups2.size(); ++i) {
        Vector<int, MAX_GROUP>& curgroup = groups2[i];
        for (int j = 0; j < groups[curgroup[0]].size(); ++j) {
            for (int k = 0; k < curgroup.size(); ++k) {
                std::cout << toa[groups[groups2[i][k]][j]] << ", ";
            }
            std::cout << " | ";
        }
        std::cout << std::endl;
    }

}



*/

void ExtractAlternatingPeriods(StaticVector<Time, TIME_COUNT> busTimes, bool visited[TIME_COUNT]) {

    for (int i = 0; i < busTimes.GetSize(); ++i) {

        if (visited[i]) // Node is already visited
            continue;


        StaticVector<Time, TIME_COUNT> maximumPattern;
        int maximumPeriodCount = 0;

        for (int j = i + 1; j < busTimes.GetSize(); ++j) {

            if (visited[j]) // Node is already visited 
                continue;

            int busPeriod = busTimes[j] - busTimes[i]; // Found a value for bus period to try.

            if (busPeriod == 0)
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
            
                std::cout << "\n-------------------------------------------------" << std::endl;
                std::cout << "Entering the gate with period: " << busPeriod << std::endl;
                std::cout << "Current maximum pattern is " << maximumPattern;
                
                int period1, period2;
                int periods[20][2];
                int alternatingPeriodCount = 0;
                int count[20] = { 0 };

                for (int s = 0; s < maximumPattern.GetSize() - 1; s++) {
                    for (int start = 0; start < busTimes.GetSize(); ++start) {

                        if (busTimes[start] < maximumPattern[s] || busTimes[start] == maximumPattern[s])
                            continue;

                        else if (maximumPattern[s + 1] < busTimes[start] || busTimes[start] == maximumPattern[s + 1])
                            break;

                        period1 = busTimes[start] - maximumPattern[s];
                        period2 = maximumPattern[s + 1] - busTimes[start];

                        std::cout << "Period 1 is: " << period1 << " Period 2 is: " << period2 << std::endl;

                        bool found = false;

                        for (int index = 0; index < alternatingPeriodCount; ++index) {
                            if (periods[index][0] == period1 && periods[index][1] == period2) {
                                std::cout << "this one already exists " << period1 << "   " << period2 << std::endl;
                                count[index]++;
                                found = true;
                            }
                        }

                        if (!found) {

                            std::cout << "this one doesn't exists adding to periods " << period1 << "   " << period2 << std::endl;
                            periods[alternatingPeriodCount][0] = period1;
                            periods[alternatingPeriodCount][1] = period2;
                            count[alternatingPeriodCount] = 1;
                            alternatingPeriodCount++;
                        }
                    }
                }

                std::cout << "Finding the most occured pattern in the alternatif patterns" << std::endl;
                int max = 0;
                int maxIndex = -1;
                std::cout << "Alternatif period count is " << alternatingPeriodCount << std::endl;

                for (int s = 0; s < alternatingPeriodCount; ++s) {

                    if (count[s] > max) {
                        max = count[s];
                        maxIndex = s;
                    }

                }

                std::cout << "Maximum one is " << periods[maxIndex][0] << "   " << periods[maxIndex][1] << std::endl;
            
            }
        }



        std::cout << "Finished calculating the maximum pattern and alternating periods " << std::endl;

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

        if (maximumPattern.GetSize() > 0)
            std::cout << "Period is: " << maximumPattern[1] - maximumPattern[0] << " Found pattern is " << maximumPattern << std::endl;
    }






}







int main() {

    StaticVector<Time, TIME_COUNT> busTimes;
    bool visited[TIME_COUNT] = { false };


    srand(time(NULL));

    Time startTime(10, 0);
    Time endTime(11, 0);

    //CreateBusPeriod(busTimes, 5, startTime, endTime);

    //busTimes.Sort(CompareTime);

    //std::cout << busTimes << std::endl;

    
    readInput(busTimes);

    ExtractAlternatingPeriods(busTimes, visited);

    for (int i = 0; i < busTimes.GetSize(); ++i) {

        if (visited[i]) // Node is already visited
            continue;


        StaticVector<Time, TIME_COUNT> maximumPattern;
        int maximumPeriodCount = 0;

        for (int j = i + 1; j < busTimes.GetSize(); ++j) {

            if (visited[j]) // Node is already visited 
                continue;

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
            std::cout << "Period is:" << maximumPattern[1] - maximumPattern[0] << " Found pattern is " << maximumPattern << std::endl;
    }
    
    return 0;
}



