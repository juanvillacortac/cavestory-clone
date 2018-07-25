.PHONY:
	run

compile:
	g++ -o gen/cavestory src/**.cpp -lSDL -L/usr/local/lib/ -lboost_filesystem

run:
	gen/cavestory
