all: Mastermind

Mastermind: regles.o main.o
	gcc -O3 -o Mastermind regles.o main.o -lSDL -lSDL_image
	
main.o: main.c
	gcc -O3 -Wall -Wfatal-errors -o main.o -c main.c
	
regles.o: regles.c
	gcc -O3 -Wall -Wfatal-errors -o regles.o -c regles.c
	
run: Mastermind
	./Mastermind
	
clean:
	rm -fr *.o Mastermind
