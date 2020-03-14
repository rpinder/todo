#include <string>

class Date
{
public:
    Date(int year, int month, int day);

    auto get_day() -> int;
    auto get_month() -> int;
    auto get_year() -> int;
    auto read() -> std::string;
private:
    const int year;
    const int month;
    const int day;
}; 
