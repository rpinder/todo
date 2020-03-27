#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <string>
#include <vector>

#include "task.hpp"

auto string_split(std::string total, char delim) -> std::vector<std::string>;
auto start_ncurses() -> void;
auto draw_tasks(std::vector<std::unique_ptr<Task>> &tasks, int current_item, int row_offset)
    -> void;
auto max_length(std::string str, int max) -> std::string;

#endif
