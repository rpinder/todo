#include "task.hpp"

Task::Task(std::string title, std::string description) : title(title)
{
    this->description = description;
    this->completed = false;
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
