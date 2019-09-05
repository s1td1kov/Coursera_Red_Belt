#include "airline_ticket.h"

#include <sstream>
#include <string>
#include <tuple>

using namespace std;

bool operator == (const Date& lhs, const Date& rhs) {
    return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

bool operator == (const Time& lhs, const Time& rhs) {
    return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

istream& operator >> (istream& is, Date& date) {
    is >> date.year;
    is.ignore(1);
    is >> date.month;
    is.ignore(1);
    is >> date.day;
    return is;
}

ostream& operator<<(ostream& os, const Date& d) {
    return os << d.year << '-' << d.month << '-' << d.day;
}

istream& operator >> (istream& is, Time& time) {
    is >> time.hours;
    is.ignore(1);
    is >> time.minutes;
    return is;
}

ostream& operator<<(ostream& os, const Time& t) {
    return os << t.hours << ':' << t.minutes;
}


#define UPDATE_FIELD(ticket, field, values) { \
auto it = values.find(#field); \
if (it != values.end()) { \
    istringstream is(it->second);  \
    is >> ticket.field; \
    } \
}
