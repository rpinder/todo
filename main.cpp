#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>

extern "C" {
#include <ncurses.h>
}

#include "task.hpp"
#include "window.hpp"
#include "util.hpp"

auto main() -> int
{
    std::vector<std::vector<std::string>> records;
    std::vector<std::unique_ptr<Task>> tasks;

    std::string line;
    std::ifstream myfile (".tasks");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            records.push_back(string_split(line, '|'));
        } 
        myfile.close();
    }

    for (auto r : records) {
        std::istringstream iss(r[0]);
        std::vector<std::string> date = string_split(r[0], '/');

        std::vector<int> date_int;
        for (auto s : date) {
            date_int.push_back(std::stoi(s));
        }

        auto day = std::make_unique<Date>(date_int[0], date_int[1], date_int[2]);
        tasks.push_back(std::make_unique<Task>(r[1], r[2], std::move(day), std::stoi(r[3])));
    }

    for (auto const &t : tasks) {
        std::cout << t->get_date()->read() << " " << t->get_title() << " "
                  << t->get_description() << " " << t->is_completed() << std::endl;
    }

    return 0;
}
