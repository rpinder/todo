#include "date.hpp"
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

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

auto Date::set_day(int day) -> void
{
    this->day = day;
}

auto Date::set_month(int month) -> void
{
    this->month = month;
}

auto Date::set_year(int year) -> void
{
    this->year = year;
}

auto Date::read() -> std::string
{
    std::ostringstream ss;
    ss << this->get_year() << "/" << std::setfill('0') << std::setw(2) << std::right
       << std::to_string(this->get_month()) << "/" << std::setfill('0') << std::setw(2)
       << std::right << std::to_string(this->get_day());
    return ss.str();
}

auto compare_date(const std::unique_ptr<Date> &a, const std::unique_ptr<Date> &b) -> bool
{
    if (a->get_year() < b->get_year())
        return true;
    if (a->get_year() > b->get_year())
        return false;

    if (a->get_month() < b->get_month())
        return true;
    if (a->get_month() > b->get_month())
        return false;

    if (a->get_day() < b->get_day())
        return true;
    if (a->get_day() > b->get_day())
        return false;

    return false;
}
