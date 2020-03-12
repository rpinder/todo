#include "ncurses_window.hpp"

NcursesWindow::NcursesWindow(int height, int width, int y, int x)
{
    this->win = newwin(height, width, y, x);
}

NcursesWindow::~NcursesWindow()
{
    delwin(this->win);
}

// NcursesWindow::operator WINDOW*()
// {
//     return win;
// }

auto NcursesWindow::get() -> WINDOW *
{
    return win;
}
