#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

#include "window.hpp"
#include "util.hpp"
#include "task.hpp"

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
        std::vector<std::string> date = string_split(r[0], '/');
        std::vector<int> date_int;
        for (auto s : date) {
            date_int.push_back(std::stoi(s));
        }

        auto day = std::make_unique<Date>(date_int[0], date_int[1], date_int[2]);
        tasks.push_back(std::make_unique<Task>(r[1], r[2], std::move(day), std::stoi(r[3])));
    }

    std::sort(tasks.begin(), tasks.end(), [](const std::unique_ptr<Task>&a, const std::unique_ptr<Task> &b) {
        return compare_date(a->get_date(), b->get_date());
    });

    start_ncurses();
    auto& tasklist = tasks;

    int key;
    int current_item = 0;
    do {
        switch (key) {
        case 'j':
            if (current_item < (int)tasks.size()-1)
                current_item++;
            break;
        case 'k':
            if (current_item > 0)
                current_item--;
            break;
        }
        draw_tasks(tasklist, current_item);
        refresh();
        key = getch();
    } while (key != 'q');

    endwin();

    return 0;
}
