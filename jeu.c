/*********************************
*								 *
* Écran de jeu					 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "jeu.h"

int printJeu(SDL_Surface *ecran) {
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
	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
	
	SDL_Surface *pions[8] = { vert, violet, rouge, orange,
							  noir, jaune, bleu, blanc };
	SDL_Rect posp[8];
	SDL_Rect pos = {0, 0};
	
	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	
	int i;
	for (i = 0; i < 8; i++) {
		posp[i].x = 70;
		posp[i].y = 46 + 45 * i;
		
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
	}
	
	SDL_Flip(ecran);
	
	int continuer = 1;
	int idx = -1;
	int x_m, y_m;
	SDL_Event event;
	
	while (continuer) {
    	SDL_WaitEvent(&event);
        switch (event.type) {
           	case SDL_QUIT:
               	continuer = 0;
               	break;

            case SDL_MOUSEBUTTONDOWN:
		        x_m = event.button.x;
		       	y_m = event.button.y;
		       	
		       	for (i = 0; i < 8; i++) {
            		if (x_m > posp[i].x && x_m < posp[i].x+pions[i]->w && y_m > posp[i].y && y_m < posp[i].y+pions[i]->h) {
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
