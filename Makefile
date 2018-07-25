.PHONY:
	run

compile:
	g++ -o cavestory src/**.cpp -lSDL -L/usr/local/lib/ -lboost_filesystem

run:
	./cavestory
