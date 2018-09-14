.PHONY:
	run

compile:
	g++ -o cavestory src/**.cpp -std=c++11 -lSDL -lm -no-pie

run:
	./cavestory
