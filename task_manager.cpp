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
        myfile << t.get_date().read() << "|" << t.get_title() << "|" << t.get_description()
               << "|" << t.is_completed() << "\n";
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

        Date day(date_int[0], date_int[1], date_int[2]);
        Task task(r[1], r[2], day, std::stoi(r[3]));
        tasks.push_back(task);
    }

    sort_tasks();
}

auto TaskManager::sort_tasks() -> void
{
    std::sort(tasks.begin(), tasks.end(),
              [](Task &a, Task &b) {
                  return compare_date(a.get_date(), b.get_date());
              });
}

auto TaskManager::loop() -> void
{
    Window mainwindow(
            [](int x){return x -3;},
            [](int x){return x;},
            [](int x){(void)x;return 2;},
            [](int x){(void)x;return 0;});
    Window statusbar(
            [](int x){(void)x;return 1;},
            [](int x){return x;},
            [](int x){return x - 1;},
            [](int x){(void)x;return 0;});
    Window headings(
            [](int x){(void)x;return 2;},
            [](int x){return x;},
            [](int x){(void)x;return 0;},
            [](int x){(void)x;return 0;});
   

    int key = 0;
    int current_item = 0;
    int row_offset = 0;
    do {
        switch (key) {
        case 'j':
            if (current_item < mainwindow.window_height() &&
                current_item + row_offset < static_cast<int>(tasks.size()) - 1) {
                if (current_item == mainwindow.window_height() - 1)
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
                tasks[current_item + row_offset].toggle_completed();
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
                mainwindow.erase();
            }
            break;
        case 'a':
            {
                Date day(1970, 1, 1);
                Task task("Title", "Description", day, false);
                tasks.push_back(task);
                break;
            }
        case 'o':
            statusbar.erase();
            statusbar.refresh();
            view_task(tasks[current_item + row_offset]);
            break;
        case KEY_RESIZE:
            Window::stop_ncurses();
            Window::start_ncurses();
            mainwindow.resize();
            mainwindow.refresh();
            statusbar.resize();
            statusbar.refresh();
            if (current_item >= mainwindow.window_height())
                current_item = mainwindow.window_height() - 1;

            break;
        default:
            break;
        }
        draw_tasks(current_item, row_offset, mainwindow);
        mainwindow.refresh();
        draw_statusbar(statusbar);
        statusbar.refresh();
        draw_headings(headings);
        headings.refresh();
        key = getch();
    } while (key != 'q');
}

auto TaskManager::draw_tasks(int current_item, int row_offset, Window &window)
    -> void
{
    int width = window.window_width() - 22;
    int title_width = static_cast<int>(floor(width / 3));
    int desc_width = static_cast<int>(ceil(2 * width / 3));
    for (int y = 0; y < window.window_height() && y < static_cast<int>(tasks.size()); y++) {
        std::ostringstream oss;
        oss << std::setw(11) << std::right << tasks[y + row_offset].get_date().read() << " | "
            << std::setw(title_width) << std::left
            << max_length(tasks[y + row_offset].get_title(), title_width) << " | "
            << std::setw(desc_width) << std::left
            << max_length(tasks[y + row_offset].get_description(), desc_width) << " | "
            << (tasks[y + row_offset].is_completed() ? "/" : "x") << " ";
        if (y == current_item)
            window.reverse(true);
        window.putstr(oss.str(), y, 0);
        window.reverse(false);
    }
}

auto TaskManager::draw_headings(Window &window) -> void
{
    int width = window.window_width() - 22;
    int title_width = static_cast<int>(floor(width / 3));
    int desc_width = static_cast<int>(ceil(2 * width / 3));

    std::ostringstream oss;
    oss << std::setw(11) << std::left << " Date"
        << " | " << std::setw(title_width) << std::left << max_length("Title", title_width) << " | "
        << std::setw(desc_width) << std::left << max_length("Description", desc_width) << " | "
        << "  ";

    window.putstr(oss.str(), 0, 0);
    std::ostringstream oss2;
    oss2 << std::string(12, '-') << '+' << std::string(title_width + 2, '-') << '+'
         << std::string(desc_width + 2, '-') << "+--";
    window.putstr(oss2.str(), 1, 0);
}

auto TaskManager::draw_statusbar(Window &window) -> void
{
    window.reverse(true);
    std::ostringstream tasks_completed;
    tasks_completed << " Tasks Completed: " << num_completed() << "/" << tasks.size();

    std::ostringstream oss;
    oss << tasks_completed.str()
        << std::setw(window.window_width() - static_cast<int>(tasks_completed.str().size()) - 2)
        << std::right << static_cast<int>(100 * num_completed() / static_cast<double>(tasks.size()))
        << "% ";
    window.putstr(oss.str(), 0, 0);

    window.reverse(false);
}

auto TaskManager::num_completed() -> int
{
    return std::accumulate(
        tasks.begin(), tasks.end(), 0,
        [](const int &total, Task &t) { return total + t.is_completed(); });
}

auto TaskManager::view_task(Task &task) -> void
{
    Window window(
            [](int x){return x - 1;},
            [](int x){return x;},
            [](int x){(void)x;return 0;},
            [](int x){(void)x;return 0;});
    Window statusbar(
            [](int x){(void)x;return 1;},
            [](int x){return x;},
            [](int x){return x-1;},
            [](int x){(void)x;return 0;});

    int key = 0;
    int selection = 1;
    int dselection = 1;
    bool edit = false;
    do {
        switch (key) {
        case KEY_RESIZE:
            Window::stop_ncurses();
            Window::start_ncurses();
            window.resize();
            window.refresh();
            statusbar.resize();
            statusbar.refresh();
            break;
        case 27:
            edit = false;
            break;
        case 127:
            if (edit) {
                switch (selection) {
                case 1:
                    if (task.title.length() > 0) {
                        task.title.pop_back();
                        window.erase();
                    }
                    break;
                case 4:
                    if (task.description.length() > 0) {
                        task.description.pop_back();
                        window.erase();
                    }
                    break;
                }
            }
            break;
        default:
            if ((isdigit(key) || isalpha(key) || ispunct(key) || key == ' ') && edit) {
                switch (selection) {
                case 1:
                    task.title += static_cast<char>(key);
                    break;
                case 4:
                    task.description += static_cast<char>(key);
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
                    if (!edit) {
                        task.toggle_completed();
                        window.erase();
                    }
                    break;
                case 'w':
                    if (selection == 3) {
                        auto &date = task.get_date();
                        switch (dselection) {
                        case 1:
                            date.set_year(date.get_year() + 1);
                            break;
                        case 2:
                            if (date.get_month() < 12)
                                date.set_month(date.get_month() + 1);
                            break;
                        case 3:
                            if (date.get_day() < 31)
                                date.set_day(date.get_day() + 1);
                            break;
                        }
                    }
                    break;
                case 's':
                    if (selection == 3) {
                        auto &date = task.get_date();
                        switch (dselection) {
                        case 1:
                            if (date.get_year() > 1)
                                date.set_year(date.get_year() - 1);
                            break;
                        case 2:
                            if (date.get_month() > 1)
                                date.set_month(date.get_month() - 1);
                            break;
                        case 3:
                            if (date.get_day() > 1)
                                date.set_day(date.get_day() - 1);
                            break;
                        }
                    }
                    break;
                case 'p':
                    if (selection == 3 && dselection > 1) {
                        dselection--;
                    }
                    break;
                case 'n':
                    if (selection == 3 && dselection < 3) {
                        dselection++;
                    }
                    break;
                }
            }
        }
        window.erase();
        if (edit) {
            statusbar.putstr("-- EDIT MODE --", 0, 0);
        } else {
            statusbar.putstr("               ", 0, 0);
        }
        statusbar.refresh();
        draw_task(window, task, selection, dselection);
        key = getch();
    } while (key != 'q' || edit);
}

auto TaskManager::draw_task(Window &window, Task &task, int selection,
                            int dselection) -> void
{
    int y = 0;
    if (selection == 1)
        window.reverse(true);
    if (task.get_title().size() > 0) {
        for (auto l : word_wrap(task.get_title(), window.window_width() - 2)) {
            window.putstr(l, y, 1);
            y++;
        }
    } else {
        window.putstr(" ", 0, 1);
        y++;
    }
    window.reverse(false);

    window.putstr(std::string(window.window_width(), '-'), y, 0);

    y += 2;

    if (selection == 2)
        window.reverse(true);
    window.putstr(task.is_completed() ? "Completed" : "Not Completed", y, 1);
    window.reverse(false);

    if (selection == 3) {
        if (dselection == 1)
            window.reverse(true);
        std::ostringstream out;
        out << std::setfill(' ') << std::setw(4) << std::right << task.get_date().get_year();
        window.putstr(out.str(), ++++y, 1);
        window.reverse(false);

        window.putstr("/", y, 5);

        if (dselection == 2)
            window.reverse(true);
        std::ostringstream out2;
        out2 << std::setfill('0') << std::setw(2) << std::right << task.get_date().get_month();
        window.putstr(out2.str(), y, 6);
        window.reverse(false);

        window.putstr("/", y, 8);

        if (dselection == 3)
            window.reverse(true);
        std::ostringstream out3;
        out3 << std::setfill('0') << std::setw(2) << std::right << task.get_date().get_day();
        window.putstr(out3.str(), y, 9);
        window.reverse(false);
    } else {
        window.putstr(task.get_date().read(), ++++y, 1);
    }
    y += 2;

    if (selection == 4)
        window.reverse(true);
    if (task.get_description().size() > 0) {
        for (auto l : word_wrap(task.get_description(), window.window_width() - 2)) {
            window.putstr(l, y, 1);
            y++;
        }
    } else {
        window.putstr(" ", y, 1);
    }
    window.reverse(false);

    window.refresh();
}
