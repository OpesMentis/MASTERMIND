/*********************************
*								 *
* Écran des règles				 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "jeu.h"

int printCredits(SDL_Surface *ecran) {
	SDL_Surface *credits = IMG_Load("img/credits.png");
	SDL_Surface *menu = IMG_Load("img/menu.png");
	SDL_Surface *menus = IMG_Load("img/menus.png");
	
	SDL_Rect pos = {0, 0};
	SDL_Rect pos_m = {258, 380};
	
	SDL_BlitSurface(credits, NULL, ecran, &pos);
	SDL_BlitSurface(menu, NULL, ecran, &pos_m);
	SDL_Flip(ecran);
	
	int continuer = 1;
	int x_m, y_m;
	SDL_Event event;
	
	while (continuer == 1) {
		SDL_WaitEvent(&event);
        switch (event.type) {
        	case SDL_QUIT:
        		continuer = 0;
        		break;
            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;
            	
            	if (is_over(x_m, y_m, *menu, pos_m)) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_m);
            	} else {
            		SDL_BlitSurface(menu, NULL, ecran, &pos_m);
            	}
            	break;
            case SDL_MOUSEBUTTONUP:
            	x_m = event.button.x;
            	y_m = event.button.y;
            	
            	if (is_over(x_m, y_m, *menu, pos_m)) {
            		continuer = 2;
            	}
            	break;
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_m:
            			continuer = 2;
            			break;
            		default:
            			break;
            	}
            	break;
            default:
            	break;
    	}
    	
    	SDL_Flip(ecran);
	}
	
	return continuer;
}
