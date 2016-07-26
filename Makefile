all: Mastermind

Mastermind: regles.o jeu.o credits.o main.o
	gcc -O3 -o Mastermind regles.o jeu.o credits.o main.o -lSDL -lSDL_image
	
main.o: main.c
	gcc -O3 -Wall -Wfatal-errors -o main.o -c main.c
	
regles.o: regles.c regles.h
	gcc -O3 -Wall -Wfatal-errors -o regles.o -c regles.c
	
jeu.o: jeu.c jeu.h
	gcc -O3 -Wall -Wfatal-errors -o jeu.o -c jeu.c
	
credits.o: credits.c credits.h
	gcc -O3 -Wall -Wfatal-errors -o credits.o -c credits.c
	
run: Mastermind
	./Mastermind
	
clean:
	rm -fr *.o Mastermind
