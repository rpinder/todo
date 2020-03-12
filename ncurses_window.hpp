extern "C" {
#include <ncurses.h>
}

class NcursesWindow
{
private:
    WINDOW *win;
public:
    NcursesWindow(int height, int width, int y, int x);
    ~NcursesWindow();
    WINDOW *get();
}; 
