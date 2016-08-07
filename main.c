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
#include "stats.h"
#include "jeu.h"
#include "credits.h"
#include "assistant.h"

int main (int argc, char **argv) {	
    SDL_Init(SDL_INIT_VIDEO);

	SDL_WM_SetIcon(IMG_Load("img/m.png"), NULL);
	SDL_WM_SetCaption("MASTERMIND", NULL);

	SDL_Surface *ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
	SDL_Surface *fond = IMG_Load("img/fond.png");
	SDL_Surface *logo = IMG_Load("img/logo.png");
	SDL_Surface *m_jouer = IMG_Load("img/m_jouer.png");
	SDL_Surface *m_jouers = IMG_Load("img/m_jouers.png");
	SDL_Surface *m_assistant = IMG_Load("img/m_assistant.png");
	SDL_Surface *m_assistants = IMG_Load("img/m_assistants.png");
	SDL_Surface *m_stat = IMG_Load("img/m_stat.png");
	SDL_Surface *m_stats = IMG_Load("img/m_stats.png");
	
	SDL_Rect posFond = {0, 0};
	SDL_Rect posLogo = {160, 20};
	SDL_Rect pos1 = {170, 150};
	SDL_Rect pos2 = {170, 250};
	SDL_Rect pos3 = {170, 350};
	
	SDL_BlitSurface(fond, NULL, ecran, &posFond);
	SDL_BlitSurface(logo, NULL, ecran, &posLogo);
	SDL_BlitSurface(m_jouer, NULL, ecran, &pos1);
	SDL_BlitSurface(m_assistant, NULL, ecran, &pos2);
	SDL_BlitSurface(m_stat, NULL, ecran, &pos3);
	
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
            
            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;
            	
            	if (is_over(x_m, y_m, *m_jouer, pos1)) {
            		SDL_BlitSurface(m_jouers, NULL, ecran, &pos1);
            	} else if (is_over(x_m, y_m, *m_assistant, pos2)) {
            		SDL_BlitSurface(m_assistants, NULL, ecran, &pos2);
            	} else if (is_over(x_m, y_m, *m_stat, pos3)) {
            		SDL_BlitSurface(m_stats, NULL, ecran, &pos3);
            	} else {
            		SDL_BlitSurface(m_jouer, NULL, ecran, &pos1);
            		SDL_BlitSurface(m_assistant, NULL, ecran, &pos2);
            		SDL_BlitSurface(m_stat, NULL, ecran, &pos3);
            	}
            	break;
            	
            case SDL_MOUSEBUTTONUP:
            	x_m = event.button.x;
            	y_m = event.button.y;
            	
            	if (is_over(x_m, y_m, *m_jouer, pos1)) {
            		continuer = printJeu(ecran);
            	} else if (is_over(x_m, y_m, *m_assistant, pos2)) {
            		continuer = printAssistant(ecran);
            	} else if (is_over(x_m, y_m, *m_stat, pos3)) {
            		continuer = printStats(ecran);
            	}
            	break;
            
            default:
            	break;
        }
        
        while (continuer != 1 && continuer != 0) {
		    if (continuer == 2) {
		    	continuer = 1;
		    	SDL_BlitSurface(fond, NULL, ecran, &posFond);
		    	SDL_BlitSurface(logo, NULL, ecran, &posLogo);
				SDL_BlitSurface(m_jouer, NULL, ecran, &pos1);
				SDL_BlitSurface(m_assistant, NULL, ecran, &pos2);
				SDL_BlitSurface(m_stat, NULL, ecran, &pos3);
			} else if (continuer == 3) {
				continuer = printJeu(ecran);
			}
		}
		
        SDL_Flip(ecran);
    }
    SDL_Quit();
 
    return EXIT_SUCCESS;
}
