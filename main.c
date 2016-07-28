/*********************************
*								 *
* Jeu de MASTERMIND				 *
* Auteur : Antoine Planchot		 *
* Début le 18/07/2016			 *
*								 *
*********************************/

/*********************************
*								 *
* Fichier principal				 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "regles.h"
#include "jeu.h"
#include "credits.h"

int main (int argc, char **argv) {	
    SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetIcon(IMG_Load("img/m.png"), NULL);
	SDL_WM_SetCaption("MASTERMIND", NULL);

	SDL_Surface *ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	SDL_Surface *fond = IMG_Load("img/fond.png");
	SDL_Surface *logo = IMG_Load("img/logo.png");
	SDL_Surface *option1a = IMG_Load("img/option1.png");
	SDL_Surface *option1b = IMG_Load("img/option1s.png");
	SDL_Surface *option2a = IMG_Load("img/option2.png");
	SDL_Surface *option2b = IMG_Load("img/option2s.png");	
	SDL_Surface *option3a = IMG_Load("img/option3.png");
	SDL_Surface *option3b = IMG_Load("img/option3s.png");
	
	SDL_Rect posFond = {0, 0};
	SDL_Rect posLogo = {160, 20};
	SDL_Rect pos1 = {170, 150};
	SDL_Rect pos2 = {170, 250};
	SDL_Rect pos3 = {170, 350};
	
	SDL_BlitSurface(fond, NULL, ecran, &posFond);
	SDL_BlitSurface(logo, NULL, ecran, &posLogo);
	SDL_BlitSurface(option1a, NULL, ecran, &pos1);
	SDL_BlitSurface(option2a, NULL, ecran, &pos2);
	SDL_BlitSurface(option3a, NULL, ecran, &pos3);
	
	SDL_Flip(ecran);
	
    int continuer = 1;
    int x_m, y_m;
    SDL_Event event;
 
    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
                
            case SDL_KEYDOWN:
            	switch (event.key.keysym.sym) {
            		case SDLK_ESCAPE:
            			continuer = 0;
            			break;
            		case SDLK_r:
            			continuer = printRegles(ecran);
            			break;
            		case SDLK_j:
            			continuer = printJeu(ecran);
            			break;/*
            		case SDLK_a:
            			continuer = printCredits(ecran);
            			break;*/
            		default:
            			break;
            	}
            	break;
            
            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;
            	
            	if (is_over(x_m, y_m, *option1a, pos1)) {
            		SDL_BlitSurface(option1b, NULL, ecran, &pos1);
            	} else if (is_over(x_m, y_m, *option2a, pos2)) {
            		SDL_BlitSurface(option2b, NULL, ecran, &pos2);
            	} else if (is_over(x_m, y_m, *option3a, pos3)) {
            		SDL_BlitSurface(option3b, NULL, ecran, &pos3);
            	} else {
            		SDL_BlitSurface(option1a, NULL, ecran, &pos1);
            		SDL_BlitSurface(option2a, NULL, ecran, &pos2);
            		SDL_BlitSurface(option3a, NULL, ecran, &pos3);
            	}
            	break;
            	
            case SDL_MOUSEBUTTONUP:
            	x_m = event.button.x;
            	y_m = event.button.y;
            	
            	if (is_over(x_m, y_m, *option1a, pos1)) {
            		continuer = printRegles(ecran);
            	} else if (is_over(x_m, y_m, *option2a, pos2)) {
            		continuer = printJeu(ecran);
            	} /*else if (is_over(x_m, y_m, *option2a, pos3)) {
            		continuer = printCredits(ecran);
            	}*/
            	break;
            
            default:
            	break;
        }
        
        while (continuer != 1 && continuer != 0) {
		    if (continuer == 2) {
		    	continuer = 1;
		    	SDL_BlitSurface(fond, NULL, ecran, &posFond);
		    	SDL_BlitSurface(logo, NULL, ecran, &posLogo);
				SDL_BlitSurface(option1a, NULL, ecran, &pos1);
				SDL_BlitSurface(option2a, NULL, ecran, &pos2);
				SDL_BlitSurface(option3a, NULL, ecran, &pos3);
			} else if (continuer == 3) {
				continuer = printJeu(ecran);
			} else if (continuer == 4) {
				continuer = printRegles(ecran);
			}
		}
		
        SDL_Flip(ecran);
    }
    
    SDL_FreeSurface(fond);
    SDL_FreeSurface(ecran);
    SDL_Quit();
 
    return EXIT_SUCCESS;
}
