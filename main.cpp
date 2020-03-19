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
    TaskManager task;
    task.read_file(".tasks");
    task.create_tasks();
    
    Window::start_ncurses();
    task.loop();
    Window::stop_ncurses();

    return 0;
}
