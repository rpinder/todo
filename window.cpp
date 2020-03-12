#include "window.hpp"
#include <memory>

Window::Window(int height, int width, int y, int x)
{
    this->win = std::unique_ptr<NcursesWindow>(new NcursesWindow(height, width, y, x));
    this->height = height;
    this->width = width;
}

auto Window::resize() -> void
{
    
}

auto Window::refresh() -> void
{
    wrefresh(this->win.get()->get());
}

auto Window::putstr(std::string text, int y, int x) -> void
{
    mvwaddstr(this->win.get()->get(), y, x, text.c_str()); 
}

