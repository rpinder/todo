#include <string>

class Task
{
private:
    const std::string title;
    bool completed;
    std::string description;
public:
    Task(std::string title, std::string description);

    auto getTitle() -> std::string;
    auto getDescription() -> std::string;
    auto isCompleted() -> bool;
    auto makeCompleted() -> void;
};  
