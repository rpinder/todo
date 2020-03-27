#include "task.hpp"

Task::Task(std::string title, std::string description, std::unique_ptr<Date> day, bool completed)
    : title(title), day(std::move(day))
{
    this->description = description;
    this->completed = completed;
}

auto Task::get_title() -> std::string
{
    return this->title;
}

auto Task::get_description() -> std::string
{
    return this->description;
}

auto Task::is_completed() -> bool
{
    return completed;
}

auto Task::make_completed() -> void
{
    this->completed = true;
}

auto Task::toggle_completed() -> void
{
    this->completed = !this->completed;
}

auto Task::get_date() -> std::unique_ptr<Date> &
{
    return day;
}
