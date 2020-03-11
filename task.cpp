#include "task.hpp"

Task::Task(std::string title, std::string description) : title(title)
{
    this->description = description;
    this->completed = false;
}

auto Task::getTitle() -> std::string
{
    return this->title;
}

auto Task::getDescription() -> std::string
{
    return this->description;
}

auto Task::isCompleted() -> bool
{
    return completed;
}

auto Task::makeCompleted() -> void
{
    this->completed = true;
}
