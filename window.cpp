#include "window.hpp"
#include <memory>

extern "C" {
    #include <ncurses.h>
}

Window::Window(int height, int width, int y, int x)
{
    this->win = std::make_unique<NcursesWindow>(height, width, y, x);
    this->height = height;
    this->width = width;
}

auto Window::resize(int height, int width, int y, int x) -> void
{
    this->win = std::make_unique<NcursesWindow>(height, width, y, x);
}

auto Window::refresh() -> void
{
    wrefresh(this->win.get()->get());
}

auto Window::putstr(std::string text, int y, int x) -> void
{
    mvwaddstr(this->win.get()->get(), y, x, text.c_str()); 
}

auto Window::start_ncurses() -> void
{
    initscr();
    wrefresh(stdscr);
    noecho();
    curs_set(0);
}

auto Window::stop_ncurses() -> void
{
    endwin();
}

auto Window::terminal_height() -> int
{
    return getmaxy(stdscr);
}

auto Window::terminal_width() -> int
{
    return getmaxx(stdscr);
}

auto Window::window_height() -> int
{
    return getmaxy(this->win->get());
}

auto Window::window_width() -> int
{
    return getmaxx(this->win->get());
}
