#include "task_manager.hpp"
#include <algorithm>
#include <ctype.h>
#include <math.h>
#include <numeric>

TaskManager::TaskManager() {}

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
        myfile << t->get_date()->read() << "|" << t->get_title() << "|" << t->get_description()
               << "|" << t->is_completed() << "\n";
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

        auto day = std::make_unique<Date>(date_int[0], date_int[1], date_int[2]);
        tasks.push_back(std::make_unique<Task>(r[1], r[2], std::move(day), std::stoi(r[3])));
    }

    sort_tasks();
}

auto TaskManager::sort_tasks() -> void
{
    std::sort(tasks.begin(), tasks.end(),
              [](const std::unique_ptr<Task> &a, const std::unique_ptr<Task> &b) {
                  return compare_date(a->get_date(), b->get_date());
              });
}

auto TaskManager::loop() -> void
{
    auto mainwindow =
        std::make_unique<Window>(Window::terminal_height() - 1, Window::terminal_width(), 0, 0);
    auto statusbar =
        std::make_unique<Window>(1, Window::terminal_width(), Window::terminal_height() - 1, 0);

    int key = 0;
    int current_item = 0;
    int row_offset = 0;
    do {
        switch (key) {
        case 'j':
            if (current_item < mainwindow->window_height() &&
                current_item + row_offset < static_cast<int>(tasks.size()) - 1) {
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
            if (tasks.size() > 0)
                tasks[current_item + row_offset]->toggle_completed();
            break;
        case 'd':
            if (tasks.size() > 0) {
                tasks.erase(tasks.begin() + current_item + row_offset);
                if (current_item > 0) {
                    current_item--;
                } else {
                    if (row_offset > 0)
                        row_offset--;
                }
                mainwindow->erase();
            }
            break;
        case 'o':
            statusbar->erase();
            statusbar->refresh();
            view_task(tasks[current_item + row_offset]);
            break;
        case KEY_RESIZE:
            Window::stop_ncurses();
            Window::start_ncurses();
            mainwindow->resize(Window::terminal_height() - 1, Window::terminal_width(), 0, 0);
            mainwindow->refresh();
            if (current_item >= mainwindow->window_height())
                current_item = mainwindow->window_height() - 1;

            statusbar->resize(1, Window::terminal_width(), Window::terminal_height() - 1, 0);
            statusbar->refresh();
            break;
        default:
            break;
        }
        draw_tasks(current_item, row_offset, mainwindow);
        mainwindow->refresh();
        draw_statusbar(statusbar);
        statusbar->refresh();
        key = getch();
    } while (key != 'q');
}

auto TaskManager::draw_tasks(int current_item, int row_offset, std::unique_ptr<Window> &window)
    -> void
{
    int width = window->window_width() - 22;
    int title_width = static_cast<int>(floor(width / 3));
    int desc_width = static_cast<int>(ceil(2 * width / 3));
    for (int y = 0; y < window->window_height() && y < static_cast<int>(tasks.size()); y++) {
        std::ostringstream oss;
        oss << std::setw(11) << std::right << tasks[y + row_offset]->get_date()->read() << " | "
            << std::setw(title_width) << std::left
            << max_length(tasks[y + row_offset]->get_title(), title_width) << " | "
            << std::setw(desc_width) << std::left
            << max_length(tasks[y + row_offset]->get_description(), desc_width) << " | "
            << (tasks[y + row_offset]->is_completed() ? "/" : "x") << " ";
        if (y == current_item)
            window->reverse(true);
        window->putstr(oss.str(), y, 0);
        window->reverse(false);
    }
}

auto TaskManager::draw_statusbar(std::unique_ptr<Window> &window) -> void
{
    window->reverse(true);
    std::ostringstream tasks_completed;
    tasks_completed << " Tasks Completed: " << num_completed() << "/" << tasks.size();

    std::ostringstream oss;
    oss << tasks_completed.str()
        << std::setw(window->window_width() - static_cast<int>(tasks_completed.str().size()) - 2)
        << std::right << static_cast<int>(100 * num_completed() / static_cast<double>(tasks.size()))
        << "% ";
    window->putstr(oss.str(), 0, 0);

    window->reverse(false);
}

auto TaskManager::num_completed() -> int
{
    return std::accumulate(
        tasks.begin(), tasks.end(), 0,
        [](const int &total, const std::unique_ptr<Task> &t) { return total + t->is_completed(); });
}

auto TaskManager::view_task(std::unique_ptr<Task> &task) -> void
{
    Window window(Window::terminal_height() - 1, Window::terminal_width(), 0, 0);

    int key = 0;
    int selection = 1;
    bool edit = false;
    do {
        switch (key) {
        case KEY_RESIZE:
            Window::stop_ncurses();
            Window::start_ncurses();
            window.resize(Window::terminal_height() - 1, Window::terminal_width(), 0, 0);
            window.refresh();
            break;
        case 27:
            edit = false;
            break;
        case 127:
            if (edit) {
                switch (selection) {
                case 1:
                    if (task->title.length() > 0) {
                        task->title.pop_back();
                        window.erase();
                    }
                    break;
                case 4:
                    if (task->description.length() > 0) {
                        task->description.pop_back();
                        window.erase();
                    }
                    break;
                }
            }
            break;
        default:
            if ((isdigit(key) || isalpha(key)) && edit) {
                switch (selection) {
                case 1:
                    task->title += static_cast<char>(key);
                    break;
                case 4:
                    task->description += static_cast<char>(key);
                    window.erase();
                    break;
                }
            } else {
                switch (key) {
                case 'j':
                    selection++;
                    if (selection > 4)
                        selection = 4;
                    break;
                case 'k':
                    selection--;
                    if (selection < 1)
                        selection = 1;
                    break;
                case 'i':
                    edit = true;
                    break;
                case 'm':
                    if (selection == 2) {
                        task->toggle_completed();
                        window.erase();
                    }
                    break;
                }
            }
        }
        if (edit) {
            window.putstr("-- EDIT MODE --", window.window_height() - 1, 1);
        } else {
            window.putstr("               ", window.window_height() - 1, 1);
        }
        draw_task(window, task, selection);
        key = getch();
    } while (key != 'q' || (key == 'q' && edit));
}

auto TaskManager::draw_task(Window &window, std::unique_ptr<Task> &task, int selection) -> void
{
    if (selection == 1)
        window.reverse(true);
    if (task->get_title().size() > 0) {
        window.putstr(task->get_title(), 0, 1);
    } else {
        window.putstr(" ", 0, 1);
    }
    window.reverse(false);

    window.putstr(std::string(std::max(static_cast<int>(task->get_title().size()), 3), '-'), 1, 1);

    if (selection == 2)
        window.reverse(true);
    window.putstr(task->is_completed() ? "Completed" : "Not Completed", 3, 1);
    window.reverse(false);

    if (selection == 3)
        window.reverse(true);
    window.putstr(task->get_date()->read(), 5, 1);
    window.reverse(false);

    if (selection == 4)
        window.reverse(true);
    if (task->get_description().size() > 0) {
        int y = 7;
        for (auto l : word_wrap(task->get_description(), window.window_width() - 2)) {
            window.putstr(l, y, 1);
            y++;
        }
    } else {
        window.putstr(" ", 7, 1);
    }
    window.reverse(false);

    window.refresh();
}
