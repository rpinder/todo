#include <string>

class Task
{
private:
    const std::string title;
    bool completed;
    std::string description;
public:
    Task(std::string title, std::string description);

    auto get_title() -> std::string;
    auto get_description() -> std::string;
    auto is_completed() -> bool;
    auto make_completed() -> void;
};  
