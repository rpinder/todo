#include <sstream>
#include "date.hpp"

Date::Date(int day, int month, int year)
    : day(day),
      month(month),
      year(year)
{}

auto Date::getDay() -> int
{
    return this->day;
}

auto Date::getMonth() -> int
{
    return this->month;
}

auto Date::getYear() -> int
{
    return this->year;
}

auto Date::read() -> std::string
{
    std::ostringstream ss;
    ss << this->getYear() << "/" << this->getMonth() << "/" << this->getDay();
    return ss.str();
}
