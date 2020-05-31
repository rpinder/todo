#ifndef WINDOW_H
#define WINDOW_H

#include "ncurses_window.hpp"
#include <memory>
#include <functional>
extern "C" {
#include <ncurses.h>
}

class Window
{
  private:
      std::unique_ptr<NcursesWindow> win;
      std::function<int(int)> height;
      std::function<int(int)> width;
      std::function<int(int)> y;
      std::function<int(int)> x;

  public:
    Window(std::function<int(int)> height, std::function<int(int)> width,
            std::function<int(int)> y, std::function<int(int)> x);

    auto static start_ncurses() -> void;
    auto static stop_ncurses() -> void;

    auto static terminal_height() -> int;
    auto static terminal_width() -> int;

    auto resize() -> void;
    auto refresh() -> void;
    auto putstr(std::string text, int y, int x) -> void;
    auto window_width() -> int;
    auto window_height() -> int;
    auto reverse(bool b) -> void;
    auto touch() -> void;
    auto erase() -> void;
};

#endif
