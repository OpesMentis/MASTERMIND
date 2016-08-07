/*********************************
*								 *
* Écran des stats				 *
*								 *
*********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stats.h"
/*
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
*/
/* Renvoie 'a' le nombres de parties,
   'b' le nombre de victoires,
   'c' le nombre de victoires sans aide */
void read_stats (char data[3][6]) {
	FILE *f_stats = fopen("DATA", "r");
	if (f_stats == NULL) {
		exit(EXIT_FAILURE);
	}
	
	int i = 0;
	int l = 0;
	char c = (char)fgetc(f_stats);
	
	while (!feof(f_stats)) {
		if (l < 5 && strchr("0123456789", (int)c)) {
			data[i][l] = c;
			data[i][l+1] = '\0';
			l++;
		} else if (i < 2 && c == ' ') {
			i++;
			l = 0;
		} else if (!(i == 2 && c == '\n')) {
			fclose(f_stats);
			reset_stats();
			strcpy(data[0], "0");
			strcpy(data[1], "0");
			strcpy(data[2], "0");
			return;
		}
		
		c = (char)fgetc(f_stats);
	}
	fclose(f_stats);
}

void write_stats (char data[3][6]) {
	FILE *f_stats = fopen("DATA", "w");
	if (f_stats == NULL) {
		exit(EXIT_FAILURE);
	}
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; data[i][j] != '\0'; j++) {
			fputc((int)data[i][j], f_stats);
		}
		if (i != 2) {
			fputc(' ', f_stats);
		}
	}
	fclose(f_stats);
}

void inc_stats (int a, int b, int c) {
	char data[3][6];
	read_stats(data);
	sprintf(data[0], "%i", atoi(data[0])+a);
	sprintf(data[1], "%i", atoi(data[1])+b);
	sprintf(data[2], "%i", atoi(data[2])+c);
	write_stats(data);
}

void reset_stats () {
	FILE *f_stats = fopen("DATA", "w");
	if (f_stats == NULL) {
		exit(EXIT_FAILURE);
	}
	fwrite("0 0 0", 5, sizeof(char), f_stats);
	fclose(f_stats);
}

/*
int printStats(SDL_Surface *ecran) {
	SDL_Surface *jeu = IMG_Load("img/fond.png");
	SDL_Surface *nb0 = IMG_Load("img/nb0.png");
	SDL_Surface *nb1 = IMG_Load("img/nb1.png");
	SDL_Surface *nb2 = IMG_Load("img/nb2.png");
	SDL_Surface *nb3 = IMG_Load("img/nb3.png");
	SDL_Surface *nb4 = IMG_Load("img/nb4.png");
	SDL_Surface *nb5 = IMG_Load("img/nb5.png");
	SDL_Surface *nb6 = IMG_Load("img/nb6.png");
	SDL_Surface *nb7 = IMG_Load("img/nb7.png");
	SDL_Surface *nb8 = IMG_Load("img/nb8.png");
	SDL_Surface *nb9 = IMG_Load("img/nb9.png");
	SDL_Surface *menu = IMG_Load("img/menu2.png");
	SDL_Surface *menus = IMG_Load("img/menu2s.png");
	SDL_Surface *reset = IMG_Load("img/reset.png");
	SDL_Surface *resets = IMG_Load("img/resets.png");
}
*/
