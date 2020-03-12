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

    auto resize() -> void;
    auto refresh() -> void;
    auto putstr(std::string text, int y, int x) -> void;
};
