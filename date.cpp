#include <sstream>
#include "date.hpp"

Date::Date(int day, int month, int year)
    : day(day),
      month(month),
      year(year)
{}

auto Date::get_day() -> int
{
    return this->day;
}

auto Date::get_month() -> int
{
    return this->month;
}

auto Date::get_year() -> int
{
    return this->year;
}

auto Date::read() -> std::string
{
    std::ostringstream ss;
    ss << this->get_year() << "/" << this->get_month() << "/" << this->get_day();
    return ss.str();
}
