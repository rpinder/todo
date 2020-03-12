#include <iostream>
#include <memory>

extern "C" {
#include <ncurses.h>
}

#include "task.hpp"
#include "window.hpp"
#include "date.hpp"

auto main() -> int
{
    std::string title = "Washing";
    std::string desc = "Do the washing";
    auto task = std::make_unique<Task>(title, desc);

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

    auto day = std::make_unique<Date>(05,11,2019);
    std::cout << day->getDay() << day->getMonth() << day->getYear() << std::endl << day->read() << std::endl;

    return 0;
}
