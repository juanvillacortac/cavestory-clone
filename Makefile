.PHONY:
	run

compile:
	g++ -o cavestory src/**.cpp -std=c++11 -lSDL -lSDL_ttf -lm -no-pie

run:
	./cavestory
