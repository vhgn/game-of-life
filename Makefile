run: game
	./game

game: main.c
	gcc -o game main.c -pedantic -Wall -std=c99
