#include <sstream>
#include <iomanip>
extern "C" {
#include <ncurses.h>
}

#include "util.hpp"

auto string_split(std::string total, char delim) -> std::vector<std::string>
{
    std::istringstream iss(total);
    std::vector<std::string> components;

    while (iss) {
        std::string s;
        if (!getline(iss, s, delim)) break;
        components.push_back(s);
    }

    return components;
}

auto start_ncurses() -> void
{
    initscr();
    refresh();
    noecho();
    curs_set(0);
}

auto draw_tasks(std::vector<std::unique_ptr<Task>>& tasks) -> void
{
    int max = getmaxy(stdscr);
    for (int y = 0; y < max && y < tasks.size(); y++) {
        std::ostringstream oss;
        oss << std::setw(10) << std::left << tasks[y]->get_date()->read() << " | "
            << std::setw(15) << std::left << tasks[y]->get_title() << " | "
            << std::setw(30) << std::left << tasks[y]->get_description() << " | "
            << tasks[y]->is_completed();
        mvwaddstr(stdscr, y, 0, oss.str().c_str());
    }
}
