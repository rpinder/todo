#include <iostream>
#include <memory>

extern "C" {
#include <ncurses.h>
}

#include "task.hpp"

auto main() -> int
{
    std::string title = "Washing";
    std::string desc = "Do the washing";

    std::unique_ptr<Task> task(new Task(title, desc));

    initscr();
    addstr(task->getTitle().c_str());
    refresh();
    getch();
    endwin();
    
    return 0;
}
