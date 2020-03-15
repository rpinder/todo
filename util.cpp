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

auto draw_tasks(std::vector<std::unique_ptr<Task>>& tasks, int current_item) -> void
{
    int max = getmaxy(stdscr);
    for (int y = 0; y < max && y < (int)tasks.size(); y++) {
        std::ostringstream oss;
        oss << std::setw(11) << std::right << tasks[y]->get_date()->read() << " | "
            << std::setw(15) << std::left << max_length(tasks[y]->get_title(), 15) << " | "
            << std::setw(30) << std::left << max_length(tasks[y]->get_description(), 30) << " | "
            << tasks[y]->is_completed();
        if (y == current_item)
            wattron(stdscr, A_REVERSE);
        mvwaddstr(stdscr, y, 0, oss.str().c_str());
        wattroff(stdscr, A_REVERSE);
    }
}

auto max_length(std::string str, int max) -> std::string
{
    if ((int)str.length() > max) {
        str = str.substr(0,max);
        str.pop_back();
        str.pop_back();
        str.push_back('.');
        str.push_back('.');
    }
    return str;
}
