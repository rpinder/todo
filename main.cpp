#include <iostream>
#include <memory>

#include "task.hpp"

auto main() -> int
{
    std::string title = "Washing";
    std::string desc = "Do the washing";

    std::unique_ptr<Task> task(new Task(title, desc));
    std::cout << task->getTitle() << std::endl << task->getDescription() << std::endl << task->isCompleted() << std::endl;
    task->makeCompleted();
    std::cout << task->isCompleted() << std::endl;
    return 0;
}
