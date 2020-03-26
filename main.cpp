#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

#include "window.hpp"
#include "util.hpp"
#include "task.hpp"
#include "task_manager.hpp"

auto main() -> int
{
    Window::start_ncurses();

    TaskManager task;
    task.read_file(".tasks");
    task.create_tasks();
    task.loop();

    Window::stop_ncurses();

    return 0;
}
