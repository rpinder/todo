all: main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp util.cpp task_manager.cpp
	g++ -Wall -pedantic -Wextra -Wconversion -std=c++17 -lncurses -o todo main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp util.cpp task_manager.cpp
