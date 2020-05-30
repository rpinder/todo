#include "window.hpp"
#include <iostream>
#include <memory>

extern "C" {
#include <ncurses.h>
}

Window::Window(std::function<int(int)> height, std::function<int(int)> width,
        std::function<int(int)> y, std::function<int(int)> x)
    :win(NcursesWindow(
                height(terminal_height()),
                width(terminal_width()),
                y(terminal_height()),
                x(terminal_width())))
    {}


auto Window::resize() -> void
{
    this->win = NcursesWindow(
            height(terminal_height()),
            width(terminal_width()),
            y(terminal_height()),
            x(terminal_width()));
}

auto Window::refresh() -> void
{
    wrefresh(this->win.get());
}

auto Window::putstr(std::string text, int y, int x) -> void
{
    mvwaddstr(this->win.get(), y, x, text.c_str());
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
    return getmaxy(this->win.get());
}

auto Window::window_width() -> int
{
    return getmaxx(this->win.get());
}

auto Window::reverse(bool b) -> void
{
    if (b)
        wattron(win.get(), A_REVERSE);
    else
        wattroff(win.get(), A_REVERSE);
}

auto Window::get() -> NcursesWindow &
{
    return win;
}

auto Window::touch() -> void
{
    touchwin(win.get());
}

auto Window::erase() -> void
{
    werase(win.get());
}
