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
    auto task = std::unique_ptr<Task>(new Task(title, desc));

    initscr();
    refresh();
    noecho();
    curs_set(0);

    int height, width;
    getmaxyx(stdscr, height, width);

    auto mainwindow = std::unique_ptr<Window>(new Window(height, width, 0, 0));
    mainwindow->putstr(task->get_title(), 0, 0);
    mainwindow->refresh();
    
    getch();
    endwin();
    return 0;
}
