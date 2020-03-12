#include <iostream>
#include <memory>

extern "C" {
#include <ncurses.h>
}

#include "task.hpp"
#include "window.hpp"

auto main() -> int
{
    std::string title = "Washing";
    std::string desc = "Do the washing";
    auto day = std::make_unique<Date>(05,11,2019);
    auto task = std::make_unique<Task>(title, desc, std::move(day));

    std::cout << task->get_title() << " " << task->get_date()->read() << " " << task->is_completed()
              << std::endl << task->get_description() << std::endl;

    // initscr();
    // refresh();
    // noecho();
    // curs_set(0);

    // int height, width;
    // getmaxyx(stdscr, height, width);

    // auto mainwindow = std::make_unique<Window>(height, width, 0, 0);
    // mainwindow->putstr(task->get_title(), 0, 0);
    // mainwindow->refresh();
    
    // getch();
    // endwin();


    return 0;
}
