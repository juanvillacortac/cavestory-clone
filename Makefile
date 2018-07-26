.PHONY:
	run

compile:
	g++ -o cavestory src/**.cpp -lSDL -lm -L/usr/local/lib/ -lboost_filesystem

run:
	./cavestory
