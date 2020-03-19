#include "task_manager.hpp"

TaskManager::TaskManager()
{
    mainwindow = std::make_unique<Window>(Window::terminal_height(), Window::terminal_width(), 0, 0); 
}

auto TaskManager::read_file(std::string name) -> void
{
    std::string line;
    std::ifstream myfile (name);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            records.push_back(string_split(line, '|'));
        } 
        myfile.close();
    }
}

auto TaskManager::create_tasks() -> void
{
    for (auto r : records) {
        std::vector<std::string> date = string_split(r[0], '/');
        std::vector<int> date_int;
        for (auto s : date) {
            date_int.push_back(std::stoi(s));
        }

        auto day = std::make_unique<Date>(date_int[0], date_int[1], date_int[2]);
        tasks.push_back(std::make_unique<Task>(r[1], r[2], std::move(day), std::stoi(r[3])));
    }

    sort_tasks();
}

auto TaskManager::sort_tasks() -> void
{
    std::sort(tasks.begin(), tasks.end(), [](const std::unique_ptr<Task>&a, const std::unique_ptr<Task> &b) {
        return compare_date(a->get_date(), b->get_date());
    });
}

auto TaskManager::loop() -> void
{
    auto mainwindow = std::make_unique<Window>(Window::terminal_height(), Window::terminal_width(), 0, 0);

    int key = 0;
    int current_item = 0;
    int row_offset = 0;
    do {
        switch (key) {
        case 'j':
            if (current_item < mainwindow->window_height() && current_item + row_offset < (int)tasks.size()-1) {
                if (current_item == mainwindow->window_height() - 1)
                    row_offset++;
                else 
                    current_item++;
            }
            break;
        case 'k':
            current_item--;
            if (current_item < 0) {
                current_item = 0;
                if (row_offset > 0)
                    row_offset--;
            }
            break;
        }
        draw_tasks(current_item, row_offset);
        refresh();
        key = getch();
    } while (key != 'q');


}

auto TaskManager::draw_tasks(int current_item, int row_offset) -> void
{
    for (int y = 0; y < Window::terminal_height() && y < (int)tasks.size(); y++) {
        std::ostringstream oss;
        oss << std::setw(11) << std::right << tasks[y + row_offset]->get_date()->read() << " | "
            << std::setw(15) << std::left << max_length(tasks[y + row_offset]->get_title(), 15) << " | "
            << std::setw(30) << std::left << max_length(tasks[y + row_offset]->get_description(), 30) << " | "
            << tasks[y + row_offset]->is_completed();
        if (y == current_item)
            wattron(stdscr, A_REVERSE);
        mvwaddstr(stdscr, y, 0, oss.str().c_str());
        wattroff(stdscr, A_REVERSE);
    }
}

