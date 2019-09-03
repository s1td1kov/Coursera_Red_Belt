#include "airline_ticket.h"
#include "test_runner.h"

#include <algorithm>
#include <numeric>
#include <tuple>
#include <string>
#include <sstream>

using namespace std;

#define SORT_BY(field) [](const AirlineTicket& tix1, const AirlineTicket& tix2) { \
return tix1.field < tix2.field; \
}

bool operator < (const Date& date1, const Date& date2) {
    return make_tuple(date1.year, date1.month, date1.day) < make_tuple(date2.year, date2.month, date2.day);
}

bool operator < (const Time& time1, const Time& time2) {
    return make_tuple(time1.hours, time1.minutes) < make_tuple(time2.hours, time2.minutes);
}

bool operator == (const Date& date1, const Date& date2) {
    return make_tuple(date1.year, date1.month, date1.day) == make_tuple(date2.year, date2.month, date2.day);
}

bool operator == (const Time& time1, const Time& time2) {
    return make_tuple(time1.hours, time1.minutes) == make_tuple(time2.hours, time2.minutes);
}

ostream& operator << (ostream& os, const Date& date) {
    os << date.day << " " << date.month << " " << date.year;
    return os;
}

ostream& operator << (ostream& os, const Time& time) {
    os << time.hours << ":" << time.minutes;
    return os;
}

void TestSortBy() {
    vector<AirlineTicket> tixs = {
        {"VKO", "AER", "Utair",     {2018, 2, 28}, {17, 40}, {2018, 2, 28}, {20,  0}, 1200},
        {"AER", "VKO", "Utair",     {2018, 3,  5}, {14, 15}, {2018, 3,  5}, {16, 30}, 1700},
        {"AER", "SVO", "Aeroflot",  {2018, 3,  5}, {18, 30}, {2018, 3,  5}, {20, 30}, 2300},
        {"PMI", "DME", "Iberia",    {2018, 2,  8}, {23, 00}, {2018, 2,  9}, { 3, 30}, 9000},
        {"CDG", "SVO", "AirFrance", {2018, 3,  1}, {13, 00}, {2018, 3,  1}, {17, 30}, 8000},
    };
    
    sort(begin(tixs), end(tixs), SORT_BY(price));
    ASSERT_EQUAL(tixs.front().price, 1200);
    ASSERT_EQUAL(tixs.back().price, 9000);
    
    sort(begin(tixs), end(tixs), SORT_BY(from));
    ASSERT_EQUAL(tixs.front().from, "AER");
    ASSERT_EQUAL(tixs.back().from, "VKO");
    
    sort(begin(tixs), end(tixs), SORT_BY(arrival_date));
    ASSERT_EQUAL(tixs.front().arrival_date, (Date{2018, 2, 9}));
    ASSERT_EQUAL(tixs.back().arrival_date, (Date{2018, 3, 5}));
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSortBy);
}
