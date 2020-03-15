#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "date.hpp"

Date::Date(int year, int month, int day)
    : year(year),
      month(month),
      day(day)
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
    ss << this->get_year() << "/"
       << std::setfill('0') << std::setw(2) << std::right << std::to_string(this->get_month()) << "/" 
       << std::setfill('0') << std::setw(2) << std::right << std::to_string(this->get_day());
    return ss.str();
}
