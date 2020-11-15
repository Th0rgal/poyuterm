poyuterm: main.cpp
	g++ `pkg-config --libs --cflags ncurses` ./src/main.cpp -o ./bin/poyuterm