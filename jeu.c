/*********************************
*								 *
* Écran de jeu					 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "jeu.h"

void chx_code(int code[4]) {
	srand(time(NULL));
	int i;
	for (i = 0; i < 4; i++) {
		code[i] = rand() % 8;
	}
}

void init_pos_sec (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 230 + 50 * i;
		pos[i].y = 378 - 35 * n;
	}
}

int is_over(int x, int y, SDL_Surface s, SDL_Rect p) {
	if (x > p.x && x < p.x+(&s)->w && y > p.y && y < p.y+(&s)->h) {
		return 1;
	}
	return 0;
}

int printJeu(SDL_Surface *ecran) {

	/* Chargement des images */
	/* Préparation de l'écran de jeu */
	SDL_Surface *jeu = IMG_Load("img/jeu.png");
	
	SDL_Surface *vert = IMG_Load("img/vert.png");
	SDL_Surface *violet = IMG_Load("img/violet.png");
	SDL_Surface *rouge = IMG_Load("img/rouge.png");
	SDL_Surface *orange = IMG_Load("img/orange.png");
	SDL_Surface *noir = IMG_Load("img/noir.png");
	SDL_Surface *jaune = IMG_Load("img/jaune.png");
	SDL_Surface *bleu = IMG_Load("img/bleu.png");
	SDL_Surface *blanc = IMG_Load("img/blanc.png");
	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *secret = IMG_Load("img/secret.png");
	
	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
	
	SDL_Surface *pions[8] = { vert, violet, rouge, orange,
							  noir, jaune, bleu, blanc };
	SDL_Rect posp[8]; // position des pions
	SDL_Rect pos = {0, 0}; // position de l'écran de jeu
	SDL_Rect pos_sec = {220, 12}; // position de 'secret'
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	
	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	
	int i;
	for (i = 0; i < 8; i++) {
		posp[i].x = 70;
		posp[i].y = 46 + 45 * i;
		
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
	}
	
	init_pos_sec(pos_chx, 0);
	
	/* Jeu à proprement parler */
	/* Variables utiles */
	int continuer = 1;
	int idx = -1;
	int x_m, y_m;
	SDL_Event event;
	int n_essai = 0;
	int essai[4] = {-1, -1, -1, -1};
	
	/* Choix du code */
	int code[4];
	chx_code(code);
	SDL_BlitSurface(secret, NULL, ecran, &pos_sec);
	
	SDL_Flip(ecran);
	
	while (continuer == 1) {
    	SDL_WaitEvent(&event);
        switch (event.type) {
           	case SDL_QUIT:
               	continuer = 0;
               	break;
               	
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_m:
            			continuer = 2;
            			break;
            		default:
            			break;
            	}

            case SDL_MOUSEBUTTONDOWN:
		        x_m = event.button.x;
		       	y_m = event.button.y;
		       	
		       	for (i = 0; i < 4; i++) {
				   	if (is_over(x_m, y_m, *vide, pos_chx[i])) {
				   		if (idx > -1) {
				   			SDL_BlitSurface(pions[idx], NULL, ecran, &pos_chx[i]);
				   			essai[i] = idx;
				   		} else {
				   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
				   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
				   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
				   			essai[i] = -1;
				   		}
				   		break;
				   	}
				}	
		       	
		       	for (i = 0; i < 8; i++) {
            		if (is_over(x_m, y_m, *pions[i], posp[i])) {
            			if (idx > -1) {
            				SDL_SetColorKey(pions[idx], SDL_SRCCOLORKEY, SDL_MapRGB(pions[idx]->format, 68, 116, 212));
            				SDL_BlitSurface(pions[idx], NULL, ecran, &posp[idx]);
            				SDL_SetColorKey(pions[idx], SDL_SRCCOLORKEY, SDL_MapRGB(pions[idx]->format, 68, 116, 213));
            			}
            			
            			if (i != idx) {
		        			SDL_BlitSurface(vide, NULL, ecran, &posp[i]);
		        			idx = i;
		        		} else {
		        			 idx = -1;
		        		}
           				break;
            		}
            	}
            	
            	break;
            	
           	default:
           		break;
       	}
       	
       	SDL_Flip(ecran);
    }
	
	return continuer;
}
