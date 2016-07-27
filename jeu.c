/*********************************
*								 *
* Écran de jeu					 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "jeu.h"
#include "regles.h"

int * eval_code(int code[4], int prop[4]) {
	int * res = malloc(2);
	res[0] = 0; res[1] = 0;
	int st_prop[4] = {0, 0, 0, 0};
	int st_code[4] = {0, 0, 0, 0};
	int i, j;
	
	for (i = 0; i < 4; i++) {
		if (prop[i] == code[i]) {
			res[0]++;
			st_prop[i] = 1;
			st_code[i] = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		if (!st_prop[i]) {
			for (j = 0; j < 4; j++) {
				if (!st_code[j] && prop[i] == code[j]) {
					res[1]++;
					st_code[j] = 1;
					st_prop[i] = 1;
					break;
				}
			}
		}
	}
	
	return res;
}

int all_fill(int code[4]) {
	if (code[0] == -1 || code[1] == -1 || code[2] == -1 || code[3] == -1) {
		return 0;
	}
	return 1;
}

void chx_code(int code[4]) {
	srand(time(NULL));
	int i;
	for (i = 0; i < 4; i++) {
		code[i] = rand() % 8;
	}
}

void init_pos_res (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 450 + 40 * i;
		pos[i].y = 390 - 35 * n;
	}
}

void init_pos_chx (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 230 + 50 * i;
		pos[i].y = 378 - 35 * n;
	}
}

void init_pos_opt (SDL_Rect pos[2], int n) {
	int i;
	for (i = 0; i < 2; i++) {
		pos[i].x = 450 + 40 * i;
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
	
	SDL_Surface *p_rouge = IMG_Load("img/p_rouge.png");
	SDL_Surface *p_blanc = IMG_Load("img/p_blanc.png");
	SDL_Surface *rien = IMG_Load("img/rien.png");
	
	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *none = IMG_Load("img/none2.png");
	SDL_Surface *secret = IMG_Load("img/secret.png");
	SDL_Surface *mask = IMG_Load("img/code.png");
	SDL_Surface *annul = IMG_Load("img/annul.png");
	SDL_Surface *valid = IMG_Load("img/valid.png");
	
	SDL_Surface *good = IMG_Load("img/good.png");
	SDL_Surface *bad = IMG_Load("img/bad.png");
	SDL_Surface *jouer = IMG_Load("img/partie.png");
	SDL_Surface *jouers = IMG_Load("img/parties.png");
	SDL_Surface *menu = IMG_Load("img/menu2.png");
	SDL_Surface *menus = IMG_Load("img/menu2s.png");
	SDL_Surface *regle = IMG_Load("img/regle.png");
	SDL_Surface *regles = IMG_Load("img/regles.png");
	
	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
	
	SDL_Surface *pions[8] = { vert, violet, rouge, orange,
							  noir, jaune, bleu, blanc };
	SDL_Rect posp[8]; // position des pions
	SDL_Rect pos = {0, 0}; // position de l'écran de jeu
	SDL_Rect pos_sec = {220, 12}; // position de 'secret'
	SDL_Rect pos_reg = {40, 440}; // position du bouton 'Règles'
	SDL_Rect pos_jou = {240, 440}; // position du bouton 'Nouvelle partie'
	SDL_Rect pos_men = {440, 440}; // position du bouton 'Menu'
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	SDL_Rect pos_opt[2]; // position des boutons
	SDL_Rect pos_res[4]; // position des pastilles d'évaluation
	SDL_Rect pos_smiley = {480, 10};
	
	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	
	int i, j;
	for (i = 0; i < 8; i++) {
		posp[i].x = 70;
		posp[i].y = 46 + 45 * i;
		
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
	}
	for (j = 0; j < 10; j++) {
		init_pos_chx (pos_chx, j);
		for (i = 0; i < 4; i++) {
			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		}
	}
	
	init_pos_chx(pos_chx, 0);
	init_pos_opt(pos_opt, 0);
	init_pos_res(pos_res, 0);
	
	SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
	SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
	SDL_BlitSurface(regle, NULL, ecran, &pos_reg);
	SDL_BlitSurface(menu, NULL, ecran, &pos_men);
	
	/* Jeu à proprement parler */
	/* Variables utiles */
	int continuer = 1;
	int idx = -1;
	int pass = 0;
	int x_m, y_m;
	SDL_Event event;
	int n_essai = 0;
	int essai[4] = {-1, -1, -1, -1};
	int over = 0;
	
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
            		case SDLK_n:
            			continuer = 3;
            			break;
            		case SDLK_r:
            			continuer = 4;
            			break;
            		default:
            			break;
            	}
            	break;
            	
            case SDL_MOUSEMOTION:
            	x_m = event.motion.x;
            	y_m = event.motion.y;
            	
            	if (!over) {
            		if (is_over(x_m, y_m, *annul, pos_opt[0])) {
            			SDL_BlitSurface(vide, NULL, ecran, &pos_opt[0]);
            		} else if (all_fill(essai) && is_over(x_m, y_m, *valid, pos_opt[1])) {
            			SDL_BlitSurface(vide, NULL, ecran, &pos_opt[1]);
            		} else if (all_fill(essai)) {
            			SDL_BlitSurface(valid, NULL, ecran, &pos_opt[1]);
            			SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
            		} else {
            			SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
            		}
            	}
            	
            	if (is_over(x_m, y_m, *jouer, pos_jou)) {
            		SDL_BlitSurface(jouers, NULL, ecran, &pos_jou);
            	} else if (is_over(x_m, y_m, *menu, pos_men)) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_men);
            	} else if (is_over(x_m, y_m, *regle, pos_reg)) {
            		SDL_BlitSurface(regles, NULL, ecran, &pos_reg);
            	} else {
            		SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(regle, NULL, ecran, &pos_reg);
            	}
            	
            	break;

            case SDL_MOUSEBUTTONUP:
		        x_m = event.button.x;
		       	y_m = event.button.y;
		       	
		       	if (is_over(x_m, y_m, *jouer, pos_jou)) {
            		continuer = 3;
            		pass = 1;
            	} else if (is_over(x_m, y_m, *menu, pos_men)) {
            		continuer = 2;
            		pass = 1;
            	} else if (is_over(x_m, y_m, *regle, pos_reg)) {
            		continuer = 4;
            		pass = 1;
            	} else {
            		SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(regle, NULL, ecran, &pos_reg);
            	}
		       	
		       	/* Bouton 'effacer' */
		       	if (!pass && !over) {
		        	if (is_over(x_m, y_m, *annul, pos_opt[0])) {
		        		SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
		        		for (i = 0; i < 4; i++) {
		        			essai[i] = -1;
		        			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		        		}
		        		SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
		        		pass = 1;
		        	}
		        }
		        
		        /* Bouton 'valider' */
		        if (!pass && !over) {
		        	if (is_over(x_m, y_m, *valid, pos_opt[1])) {
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[0]);
		        		SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
		        		int * res = malloc(2);
		        		res = eval_code(code, essai);
						if (n_essai == 9 || res[0] == 4) {
		        			SDL_BlitSurface(mask, NULL, ecran, &pos_sec);
		        			for (i = 0; i < 4; i++) {
								pos_chx[i].x = 230 + 50 * i;
								pos_chx[i].y = 17;
									
								SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
								SDL_BlitSurface(pions[code[i]], NULL, ecran, &pos_chx[i]);
							}
							if (res[0] == 4) {
								SDL_BlitSurface(good, NULL, ecran, &pos_smiley);
							} else {
								SDL_BlitSurface(bad, NULL, ecran, &pos_smiley);
							}
							over = 1;
		        		} else {
		        			if (res[0] == 0 && res[1] == 0) {
		        				SDL_BlitSurface(rien, NULL, ecran, &pos_res[0]);
		        			} else {
				    			j = 0;
				    			for (i = 0; i < res[0]; i++) {
				    				SDL_BlitSurface(p_rouge, NULL, ecran, &pos_res[j++]);
				    			}
				    			for (i = 0; i < res[1]; i++) {
				    				SDL_BlitSurface(p_blanc, NULL, ecran, &pos_res[j++]);
				    			}
				    		}
		        			n_essai++;
		        			init_pos_chx(pos_chx, n_essai);
							init_pos_opt(pos_opt, n_essai);
							init_pos_res(pos_res, n_essai);
							
							SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
							for (i = 0; i < 4; i++) { essai[i] = -1; }
		        		}
		        		pass = 1;
		        	}
		        }
		       	
		       	/* Apposition d'une couleur */
		       	if (!pass && !over) {
				   	for (i = 0; i < 4; i++) {
					   	if (is_over(x_m, y_m, *vide, pos_chx[i])) {
					   		if (idx > -1) {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(pions[idx], NULL, ecran, &pos_chx[i]);
					   			essai[i] = idx;
					   			
					   			if (all_fill(essai)) {
					   				SDL_BlitSurface(valid, NULL, ecran, &pos_opt[1]);
					   			}
					   				
					   		} else {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			essai[i] = -1;
					   			SDL_BlitSurface(none, NULL, ecran, &pos_opt[1]);
					   		}
					   		pass = 1;
					   		break;
					   	}
					}
				}
		       	
		       	/* Sélection d'une couleur */
		       	if (!pass && !over) {
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
				    		pass = 1;
		       				break;
		        		}
		        	}
		        }
		        
		        pass = 0;
            	break;
            	
           	default:
           		break;
       	}
       	SDL_Flip(ecran);
    }
	
	return continuer;
}
