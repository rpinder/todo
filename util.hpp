#ifndef UTIL_H
#define UTIL_H

#include <vector>
#include <string>
#include <memory>

#include "task.hpp"

auto string_split(std::string total, char delim) -> std::vector<std::string>;
auto start_ncurses() -> void;
auto draw_tasks(std::vector<std::unique_ptr<Task>>& tasks) -> void;

#endif
