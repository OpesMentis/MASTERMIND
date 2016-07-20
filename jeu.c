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
	
	SDL_Rect pos = {0, 0};
	
	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	SDL_BlitSurface(rouge, NULL, ecran, &pok);
	
	SDL_Flip(ecran);
	
	int continuer = 1;
	SDL_Event event;
	
	while (continuer) {
    	SDL_WaitEvent(&event);
        switch (event.type) {
           	case SDL_QUIT:
               	continuer = 0;
               	break;
                
           	default:
           		break;
       	}
    }
	
	return continuer;
}
