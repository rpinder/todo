#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <vector>

#include "task.hpp"
#include "util.hpp"
#include "window.hpp"

class TaskManager
{
  public:
    TaskManager();

    auto read_file(std::string name) -> void;
    auto write_file(std::string name) -> void;
    auto create_tasks() -> void;
    auto loop() -> void;
    auto draw_tasks(int current_item, int row_offset, Window &window) -> void;
    auto draw_statusbar(Window &window) -> void;
    auto draw_headings(Window &window) -> void;
    auto num_completed() -> int;
    auto view_task(std::unique_ptr<Task> &task) -> void;
    auto draw_task(Window &window, std::unique_ptr<Task> &task, int selection, int dselection) -> void;

  private:
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<std::vector<std::string>> records;

    auto sort_tasks() -> void;
};

#endif
