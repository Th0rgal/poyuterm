./bin/poyuterm: ./src/main.cpp ./bin/grid.so ./bin/game.so ./bin/events.so ./bin/display.so
	g++ ./src/main.cpp -o ./bin/poyuterm -lncurses

./bin/grid.so: ./src/grid/grid.cpp ./src/grid/grid.h
	g++ -c ./src/grid/grid.cpp -o ./bin/grid.so

./bin/game.so: ./src/game/game.cpp ./src/game/game.h
	g++ -c ./src/game/game.cpp -o ./bin/game.so

./bin/events.so: ./src/events/events.cpp ./src/events/events.h
	g++ -c ./src/events/events.cpp -o ./bin/event.so

./bin/display.so: ./src/display/display.cpp ./src/display/display.h
	g++ -c ./src/display/display.cpp -o ./bin/display.so

lancer: ./bin/poyuterm
	./bin/poyuterm