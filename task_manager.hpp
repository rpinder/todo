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
    auto create_tasks() -> void;
    auto loop() -> void;
    auto draw_tasks(int current_item, int row_offset,
                    std::unique_ptr<Window> &window) -> void;

  private:
    std::unique_ptr<Window> mainwindow;
    std::vector<std::unique_ptr<Task>> tasks;
    std::vector<std::vector<std::string>> records;

    auto sort_tasks() -> void;
};

#endif
