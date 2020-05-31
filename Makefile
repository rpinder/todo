CPPFLAGS=-Wall -pedantic -Wextra -Wconversion -std=c++17

todo: task.o window.o ncurses_window.o date.o util.o task_manager.o main.cpp
	g++ $(CPPFLAGS) -lncurses -o todo main.cpp task.o window.o ncurses_window.o date.o util.o task_manager.o

task.o: task.cpp task.hpp date.hpp
	g++ $(CPPFLAGS) -c task.cpp

window.o: window.cpp window.hpp ncurses_window.hpp
	g++ $(CPPFLAGS) -lncurses -c window.cpp

ncurses_window.o: ncurses_window.cpp ncurses_window.hpp
	g++ $(CPPFLAGS) -lncurses -c ncurses_window.cpp

date.o: date.cpp date.hpp
	g++ $(CPPFLAGS) -c date.cpp

util.o: util.cpp util.hpp
	g++ $(CPPFLAGS) -c util.cpp

task_manager.o: task_manager.cpp task_manager.hpp util.hpp window.hpp
	g++ $(CPPFLAGS) -c task_manager.cpp
