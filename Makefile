all: Mastermind

Mastermind: stats.o jeu.o assistant.o main.o
	gcc -O3 -o Mastermind stats.o jeu.o assistant.o main.o -lSDL -lSDL_image
	
main.o: main.c
	gcc -O3 -Wall -Wfatal-errors -o main.o -c main.c
	
regles.o: stats.c stats.h
	gcc -O3 -Wall -Wfatal-errors -o stats.o -c stats.c
	
jeu.o: jeu.c jeu.h
	gcc -O3 -Wall -Wfatal-errors -o jeu.o -c jeu.c
	
assistant.o: assistant.c assistant.h
	gcc -O3 -Wall -Wfatal-errors -o assistant.o -c assistant.c
	
run: Mastermind
	./Mastermind
	
clean:
	rm -fr *.o Mastermind
