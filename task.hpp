#ifndef TASK_H
#define TASK_H

#include <memory>
#include <string>

#include "date.hpp"

class Task
{
  private:
    bool completed;
    Date day;

  public:
    Task(std::string title, std::string description, Date day, bool completed);

    std::string title;
    std::string description;
    auto get_title() -> std::string;
    auto get_description() -> std::string;
    auto is_completed() -> bool;
    auto make_completed() -> void;
    auto toggle_completed() -> void;
    auto get_date() -> Date &;
};

#endif
