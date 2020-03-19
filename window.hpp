#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include "ncurses_window.hpp"
extern "C" {
#include <ncurses.h>
}

class Window
{
private:
    int height;
    int width;
    std::unique_ptr<NcursesWindow> win;

public:
    Window(int height, int width, int y, int x);

    auto static start_ncurses() -> void;
    auto static stop_ncurses() -> void;

    auto static terminal_height() -> int;
    auto static terminal_width() -> int;

    auto resize(int height, int width, int y, int x) -> void;
    auto refresh() -> void;
    auto putstr(std::string text, int y, int x) -> void;
    auto window_width() -> int;
    auto window_height() -> int;

};

#endif
