#include <string>

class Date
{
public:
    Date(int day, int month, int year);

    auto get_day() -> int;
    auto get_month() -> int;
    auto get_year() -> int;
    auto read() -> std::string;
private:
    const int day;
    const int month;
    const int year;
}; 
