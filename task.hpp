#ifndef TASK_H
#define TASK_H

#include <string>
#include <memory>

#include "date.hpp"

class Task
{
private:
    const std::string title;
    bool completed;
    std::unique_ptr<Date> day;
    std::string description;
public:
    Task(std::string title, std::string description, std::unique_ptr<Date> day, bool completed);

    auto get_title() -> std::string;
    auto get_description() -> std::string;
    auto is_completed() -> bool;
    auto make_completed() -> void;
    auto get_date() -> std::unique_ptr<Date>&;
};  

#endif
