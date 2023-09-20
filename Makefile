all:
	gcc -Wall -std=c99 src/*.c -lSDL2 -o mainlinux
	g++ -Iinclude -Llib src/*.c -o mainwin -lmingw32 -lSDL2main -lSDL2
	