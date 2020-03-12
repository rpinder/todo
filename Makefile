all: main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp
	g++ -Wall -pedantic -lncurses -o todo main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp
