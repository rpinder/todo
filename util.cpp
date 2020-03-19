#include <sstream>
#include <iomanip>
extern "C" {
#include <ncurses.h>
}

#include "util.hpp"

auto string_split(std::string total, char delim) -> std::vector<std::string>
{
    std::istringstream iss(total);
    std::vector<std::string> components;

    while (iss) {
        std::string s;
        if (!getline(iss, s, delim)) break;
        components.push_back(s);
    }

    return components;
}

auto max_length(std::string str, int max) -> std::string
{
    if ((int)str.length() > max) {
        str = str.substr(0,max);
        str.pop_back();
        str.pop_back();
        str.push_back('.');
        str.push_back('.');
    }
    return str;
}
