#include "task_manager.hpp"
#include <math.h>

TaskManager::TaskManager()
{
    this->mainwindow = std::make_unique<Window>(Window::terminal_height(),
                                                Window::terminal_width(), 0, 0);
}

auto TaskManager::read_file(std::string name) -> void
{
    std::string line;
    std::ifstream myfile(name);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            records.push_back(string_split(line, '|'));
        }
        myfile.close();
    }
}

auto TaskManager::write_file(std::string name) -> void
{
    std::ofstream myfile;
    myfile.open(name);
    for (auto &t : tasks) {
        myfile << t->get_date()->read() << "|" << t->get_title() << "|"
               << t->get_description() << "|" << t->is_completed() << "\n";
    }
    myfile.close();
}

auto TaskManager::create_tasks() -> void
{
    for (auto r : records) {
        std::vector<std::string> date = string_split(r[0], '/');
        std::vector<int> date_int;
        for (auto s : date) {
            date_int.push_back(std::stoi(s));
        }

        auto day =
            std::make_unique<Date>(date_int[0], date_int[1], date_int[2]);
        tasks.push_back(std::make_unique<Task>(r[1], r[2], std::move(day),
                                               std::stoi(r[3])));
    }

    sort_tasks();
}

auto TaskManager::sort_tasks() -> void
{
    std::sort(
        tasks.begin(), tasks.end(),
        [](const std::unique_ptr<Task> &a, const std::unique_ptr<Task> &b) {
            return compare_date(a->get_date(), b->get_date());
        });
}

auto TaskManager::loop() -> void
{
    auto mainwindow = std::make_unique<Window>(Window::terminal_height(),
                                               Window::terminal_width(), 0, 0);

    int key = 0;
    int current_item = 0;
    int row_offset = 0;
    do {
        switch (key) {
        case 'j':
            if (current_item < mainwindow->window_height() &&
                current_item + row_offset < (int)tasks.size() - 1) {
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
        case 'm':
            tasks[current_item + row_offset]->toggle_completed();
            break;
        case 'd':
            tasks.erase(tasks.begin() + current_item + row_offset);
            if (current_item > 0) {
                current_item--;
            } else {
                if (row_offset > 0)
                    row_offset--;
            }
            mainwindow->erase();
            break;
        case KEY_RESIZE:
            Window::stop_ncurses();
            Window::start_ncurses();
            mainwindow->resize(Window::terminal_height(),
                               Window::terminal_width(), 0, 0);
            mainwindow->refresh();
        default:
            break;
        }
        draw_tasks(current_item, row_offset, mainwindow);
        mainwindow->refresh();
        key = getch();
    } while (key != 'q');
}

auto TaskManager::draw_tasks(int current_item, int row_offset,
                             std::unique_ptr<Window> &window) -> void
{
    int width = mainwindow->window_width() - 22;
    int title_width = int(floor(width / 3));
    int desc_width = int(ceil(2 * width / 3));
    for (int y = 0; y < mainwindow->window_height() && y < (int)tasks.size();
         y++) {
        std::ostringstream oss;
        oss << std::setw(11) << std::right
            << tasks[y + row_offset]->get_date()->read() << " | "
            << std::setw(title_width) << std::left
            << max_length(tasks[y + row_offset]->get_title(), title_width)
            << " | " << std::setw(desc_width) << std::left
            << max_length(tasks[y + row_offset]->get_description(), desc_width)
            << " | " << tasks[y + row_offset]->is_completed() << " ";
        if (y == current_item)
            window->reverse(true);
        window->putstr(oss.str(), y, 0);
        window->reverse(false);
    }
}
