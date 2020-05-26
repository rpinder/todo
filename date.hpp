#include <memory>
#include <string>

class Date
{
  public:
    Date(int year, int month, int day);

    auto get_day() -> int;
    auto get_month() -> int;
    auto get_year() -> int;
    auto set_day(int day) -> void;
    auto set_month(int month) -> void;
    auto set_year(int year) -> void;
    auto read() -> std::string;

  private:
    int year;
    int month;
    int day;
};

auto compare_date(const std::unique_ptr<Date> &a, const std::unique_ptr<Date> &b) -> bool;
