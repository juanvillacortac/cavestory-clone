.PHONY:
	run

all:
	g++ -o cavestory src/**.cpp -std=c++11 -lSDL -lSDL_ttf -lm -no-pie

debug:
	g++ -o cavestory -g src/**.cpp -std=c++11 -lSDL -lSDL_ttf -lm -no-pie

run:
	./cavestory
