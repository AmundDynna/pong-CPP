all: debug

debug: compile link clean open 
release: compileRelease linkRelease clean openRelease

compile:
	g++ -c src\\*.cpp -std=c++17 -g -Wall -m64 -I include -I C:\\SDL2-w64\\include

link:
	g++ *.o -o bin\\debug\\main -L C:\\SDL2-w64\\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

open:
	./bin\\debug\main



compileRelease:
	g++ -c src\\*.cpp -std=c++17 -O3 -Wall -m64 -I include -I C:\\SDL2-w64\\include

linkRelease:
	g++ *.o -o bin\\release\\main -s -L C:\\SDL2-w64\\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows 

openRelease:
	./bin\\release\main

clean:
	del *.o