/*********************************
*								 *
* Écran des règles				 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "regles.h"

int printRegles(SDL_Surface *ecran) {
	SDL_Surface *regles1 = IMG_Load("img/regles1.png");
	SDL_Surface *regles2 = IMG_Load("img/regles2.png");
	SDL_Surface *regles3 = IMG_Load("img/regles3.png");
	SDL_Surface *gauche = IMG_Load("img/gauche.png");
	SDL_Surface *droite = IMG_Load("img/droite.png");
	SDL_Surface *jouer = IMG_Load("img/jouer.png");
	SDL_Surface *menu = IMG_Load("img/menu.png");
	SDL_Surface *gauches = IMG_Load("img/gauches.png");
	SDL_Surface *droites = IMG_Load("img/droites.png");
	SDL_Surface *jouers = IMG_Load("img/jouers.png");
	SDL_Surface *menus = IMG_Load("img/menus.png");
	SDL_Surface *none = IMG_Load("img/none.png");
	
	SDL_Surface *regles[3] = {regles1, regles2, regles3};
	
	SDL_Rect pos = {0, 0};
	SDL_Rect pos_g = {70, 380};
	SDL_Rect pos_m = {170, 380};
	SDL_Rect pos_j = {345, 380};
	SDL_Rect pos_d = {520, 380};
	
	SDL_BlitSurface(regles[0], NULL, ecran, &pos);
	SDL_BlitSurface(droite, NULL, ecran, &pos_d);
	SDL_BlitSurface(jouer, NULL, ecran, &pos_j);
	SDL_BlitSurface(menu, NULL, ecran, &pos_m);
	
	int i = 1; // page de règles
	int x_m, y_m;
	int continuer = 1;
	int chgt = 0;
	SDL_Event event;
	
	SDL_Flip(ecran);
	
	while (continuer == 1) {
		SDL_WaitEvent(&event);
        switch (event.type) {
        	case SDL_QUIT:
        		continuer = 0;
        		break;
            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;
            	
            	if ((i == 1 || i == 2) && x_m > pos_d.x && x_m < pos_d.x+droite->w && y_m > pos_d.y && y_m < pos_d.y+droite->h) {
            		SDL_BlitSurface(droites, NULL, ecran, &pos_d);
            	} else if ((i == 2 || i == 3) && x_m > pos_g.x && x_m < pos_g.x+gauche->w && y_m > pos_g.y && y_m < pos_d.y+gauche->h) {
            		SDL_BlitSurface(gauches, NULL, ecran, &pos_g);
            	} else {
            		if (i == 1 || i == 2) {
            			SDL_BlitSurface(droite, NULL, ecran, &pos_d);
            		}
            		if (i == 2 || i == 3) {
            			SDL_BlitSurface(gauche, NULL, ecran, &pos_g);
            		}
            	}
            	if (x_m > pos_j.x && x_m < pos_j.x+jouer->w && y_m > pos_j.y && y_m < pos_j.y+jouer->h) {
            		SDL_BlitSurface(jouers, NULL, ecran, &pos_j);
            	} else if (x_m > pos_m.x && x_m < pos_m.x+menu->w && y_m > pos_m.y && y_m < pos_m.y+menu->h) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_m);
            	} else {
            		SDL_BlitSurface(jouer, NULL, ecran, &pos_j);
            		SDL_BlitSurface(menu, NULL, ecran, &pos_m);
            	}
                break;
            case SDL_MOUSEBUTTONUP:
            	x_m = event.button.x;
            	y_m = event.button.y;
            	
            	if ((i == 1 || i == 2) && x_m > pos_d.x && x_m < pos_d.x+droite->w && y_m > pos_d.y && y_m < pos_d.y+droite->h) {
            		i++;
            		chgt = 1;
            	} else if ((i == 2 || i == 3) && x_m > pos_g.x && x_m < pos_g.x+gauche->w && y_m > pos_g.y && y_m < pos_d.y+gauche->h) {
            		i--;
            		chgt = 1;
            	} else if (x_m > pos_m.x && x_m < pos_m.x+menu->w && y_m > pos_m.y && y_m < pos_m.y+menu->h) {
            		continuer = 2;
            	}
            	
            	if (chgt > 0) {
            		chgt = 0;
		        	SDL_BlitSurface(regles[i-1], NULL, ecran, &pos);
		        	SDL_BlitSurface(jouer, NULL, ecran, &pos_j);
		        	SDL_BlitSurface(menu, NULL, ecran, &pos_m);
		        	if (i == 1) {
		        		SDL_BlitSurface(droite, NULL, ecran, &pos_d);
		        		SDL_BlitSurface(none, NULL, ecran, &pos_g);
		        	} else if (i == 2) {
		        		SDL_BlitSurface(gauche, NULL, ecran, &pos_g);
		        		SDL_BlitSurface(droite, NULL, ecran, &pos_d);
		        	} else if (i == 3) {
		        		SDL_BlitSurface(gauche, NULL, ecran, &pos_g);
		        		SDL_BlitSurface(none, NULL, ecran, &pos_d);
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

