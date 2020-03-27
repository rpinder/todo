#ifndef UTIL_H
#define UTIL_H

#include <memory>
#include <string>
#include <vector>

#include "task.hpp"

auto string_split(std::string total, char delim) -> std::vector<std::string>;
auto max_length(std::string str, int max) -> std::string;
auto word_wrap(std::string str, int width) -> std::vector<std::string>;

#endif
