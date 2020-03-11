all: main.cpp task.cpp
	g++ -Wall -pedantic -lncurses -o todo main.cpp task.cpp
