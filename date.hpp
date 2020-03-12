#include <string>

class Date
{
public:
    Date(int day, int month, int year);

    auto getDay() -> int;
    auto getMonth() -> int;
    auto getYear() -> int;
    auto read() -> std::string;
private:
    const int day;
    const int month;
    const int year;
}; 
