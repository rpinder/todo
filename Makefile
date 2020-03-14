all: main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp util.cpp
	g++ -Wall -pedantic -lncurses -o todo main.cpp task.cpp window.cpp ncurses_window.cpp date.cpp util.cpp
