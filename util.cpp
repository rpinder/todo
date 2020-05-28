#include <iomanip>
#include <sstream>
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
        if (!getline(iss, s, delim))
            break;
        components.push_back(s);
    }

    return components;
}

auto max_length(std::string str, int max) -> std::string
{
    if (static_cast<int>(str.length()) > max) {
        str = str.substr(0, max);
        str.pop_back();
        str.pop_back();
        str.push_back('.');
        str.push_back('.');
    }
    return str;
}

auto word_wrap(std::string str, int width) -> std::vector<std::string>
{
    int col = 0;
    for (int i = 0; i < static_cast<int>(str.length()); i++, col++) {
        if (col >= width) {
            int j;
            for (j = i; str[j] != ' '; j--)
                if (j == 0) {
                    j = width;
                    break;
                }
            str.replace(j, 1, "\n");
            col = i - j;
        }
    }

    std::vector<std::string> lines = string_split(str, '\n');

    return lines;
}
