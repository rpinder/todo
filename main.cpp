#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "task.hpp"
#include "task_manager.hpp"
#include "util.hpp"
#include "window.hpp"

auto main() -> int
{

    std::string file = getenv("HOME");
    file += "/.tasks";

    Window::start_ncurses();

    TaskManager task;
    task.read_file(file);
    task.create_tasks();
    task.loop();

    Window::stop_ncurses();
    task.write_file(file);

    return 0;
}
