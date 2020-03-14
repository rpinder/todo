#include <sstream>

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
