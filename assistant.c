/*********************************
*								 *
* Assistant de jeu				 *
*								 *
*********************************/

#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <time.h>
#include "assistant.h"
#include "jeu.h"

void init_pos_fle (SDL_Rect pos[4], int n) {
	int i;
	pos[0].x = 445;
	pos[1].x = 480;
	pos[2].x = 515;
	pos[3].x = 550;
	
	for (i = 0; i < 4; i++) {
		pos[i].y = 378 - 35*n;
	}
}

void init_pos_eva (SDL_Rect pos[2], int n) {
	int i;
	for (i = 0; i < 2; i++) {
		pos[i].x = 460 + 70 * i;
		pos[i].y = 378 - 35 * n;
	}
}

void init_pos_evo (SDL_Rect pos[2], int n) {
	int i;
	for (i = 0; i < 2; i++) {
		pos[i].x = 140 + 40 * i;
		pos[i].y = 378 - 35 * n;
	}
}

void init_pos_nb (SDL_Rect pos[4], int n) {
	int i;
	for (i = 0; i < 4; i++) {
		pos[i].x = 150 + 15 * i;
		pos[i].y = 378 - 35 * n;
	}
}

int ready_togo (int code[4], int n_past[2], int n, int sens) { /* 0 = haut, 1 = bas */
	if (sens == 0) {
		if (all_fill(code) && n_past[0] + n_past[1] <= 4 && n < 9) {
			return 1;
		}
		return 0;
	}
	if (n > 0) {
		return 1;
	}
	return 0;
}

void tabcpy(int * dest, int * src, int s) {
	int i;
	for (i = 0; i < s; i++) {
		dest[i] = src[i];
	}
}

/* Nombre de possibilités */
int nb_remain (int * tab[10][2], int n, int * poss) {
	int blank4[4];
	int blank2[2];
	int i, j;
	
	int s = 0;
	
	for (i = 0; i < pow(8, 4); i++) {
		poss[i] = 1;
		for (j = 0; j < n; j++) {
			decode(i, blank4);
			eval_code(blank4, tab[j][0], blank2);
		
			if (blank2[0] != tab[j][1][0] || blank2[1] != tab[j][1][1]) {
				poss[i] = 0;
				break;
			}
		}
		s += poss[i];
	}
	
	return s;
}

/* Conseil */
void assist (int * tab[10][2], int n, int * poss, int s, int conseil[4]) {
	srand(time(NULL));
	int i = rand() % s;
	int j = 0;
	int k = -1;
	
	while (j < i) {
		if (poss[++k] == 1) {
			j++;
		}
	}
	
	decode(k, conseil);
}

void decode(int code, int a[4]) {
	a[3] = code / pow(8, 3);
	code -= a[3] * pow(8, 3);
	a[2] = code / pow(8, 2);
	code -= a[2] * pow(8, 2);
	a[1] = code / pow(8, 1);
	code -= a[1] * 8;
	a[0] = code;
}

void nb_decompo(int nb, int a[4]) {
	a[0] = nb / 1000;
	nb -= 1000 * a[0];
	a[1] = nb / 100;
	nb -= 100 * a[1];
	a[2] = nb / 10;
	nb -= 10 * a[2];
	a[3] = nb;
}

int printAssistant(SDL_Surface *ecran) {

	/* Chargement des images */
	/* Préparation de l'écran de jeu */
	SDL_Surface *jeu = IMG_Load("img/fond.png");
	
	SDL_Surface *vert = IMG_Load("img/vert.png");
	SDL_Surface *violet = IMG_Load("img/violet.png");
	SDL_Surface *rouge = IMG_Load("img/rouge.png");
	SDL_Surface *orange = IMG_Load("img/orange.png");
	SDL_Surface *noir = IMG_Load("img/noir.png");
	SDL_Surface *jaune = IMG_Load("img/jaune.png");
	SDL_Surface *bleu = IMG_Load("img/bleu.png");
	SDL_Surface *blanc = IMG_Load("img/blanc.png");
	
	SDL_Surface *p_rouge0 = IMG_Load("img/p_rouge0.png");
	SDL_Surface *p_rouge1 = IMG_Load("img/p_rouge1.png");
	SDL_Surface *p_rouge2 = IMG_Load("img/p_rouge2.png");
	SDL_Surface *p_rouge3 = IMG_Load("img/p_rouge3.png");
	SDL_Surface *p_rouge4 = IMG_Load("img/p_rouge4.png");
	SDL_Surface *p_blanc0 = IMG_Load("img/p_blanc0.png");
	SDL_Surface *p_blanc1 = IMG_Load("img/p_blanc1.png");
	SDL_Surface *p_blanc2 = IMG_Load("img/p_blanc2.png");
	SDL_Surface *p_blanc3 = IMG_Load("img/p_blanc3.png");
	SDL_Surface *p_blanc4 = IMG_Load("img/p_blanc4.png");
	SDL_Surface *p_gauche = IMG_Load("img/p_gauche.png");
	SDL_Surface *p_droite = IMG_Load("img/p_droite.png");
	SDL_Surface *p_none = IMG_Load("img/p_none.png");
	
	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *none = IMG_Load("img/none2.png");
	SDL_Surface *haut = IMG_Load("img/haut.png");
	SDL_Surface *bas = IMG_Load("img/bas.png");
	SDL_Surface *hauts = IMG_Load("img/hauts.png");
	SDL_Surface *bass = IMG_Load("img/bass.png");
	
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
	SDL_Surface *aide = IMG_Load("img/aide.png");
	SDL_Surface *aides = IMG_Load("img/aides.png");
	SDL_Surface *aide1 = IMG_Load("img/assist1.png");
	SDL_Surface *aide2 = IMG_Load("img/assist2.png");
	SDL_Surface *none_a1 = IMG_Load("img/none_a1.png");
	SDL_Surface *none_a2 = IMG_Load("img/none_a2.png");
	
	SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
	
	SDL_Surface *pions[8] = { vert, violet, rouge, orange,
							  noir, jaune, bleu, blanc };
	SDL_Surface *p_rouge[5] = { p_rouge0, p_rouge1, p_rouge2,
								p_rouge3, p_rouge4};
	SDL_Surface *p_blanc[5] = { p_blanc0, p_blanc1, p_blanc2,
								p_blanc3, p_blanc4};
	SDL_Surface *nb[10] = { nb0, nb1, nb2, nb3, nb4,
							nb5, nb6, nb7, nb8, nb9};
							  
	SDL_Rect posp[8]; // position des pions
	SDL_Rect pos = {0, 0}; // position de l'écran de jeu
	SDL_Rect pos_men = {440, 440}; // position du bouton 'Menu'
	SDL_Rect pos_reg = {40, 440};
	SDL_Rect pos_reset = {240, 440};
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	SDL_Rect pos_eva[2]; // position des pastilles d'évaluation
	SDL_Rect pos_fle[4]; // position des fléchettes
	SDL_Rect pos_evo[2]; // position des flèches haut/bas
	SDL_Rect pos_nb[4]; // position du nombre de combinaisons restantes
	SDL_Rect pos_aide1 = {450, 5};
	SDL_Rect pos_aide2 = {110, 5};
	
	SDL_BlitSurface(jeu, NULL, ecran, &pos);
	
	int i, j;
	for (i = 0; i < 8; i++) {
		posp[i].x = 70;
		posp[i].y = 46 + 45 * i;
		
		SDL_SetColorKey(pions[i], SDL_SRCCOLORKEY, SDL_MapRGB(pions[i]->format, 68, 116, 213));
		SDL_BlitSurface(pions[i], NULL, ecran, &posp[i]);
	}
	for (j = 0; j < 10; j++) {
		init_pos_chx (pos_chx, j);
		for (i = 0; i < 4; i++) {
			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
		}
	}
	
	init_pos_chx(pos_chx, 0);
	init_pos_fle(pos_fle, 0);
	init_pos_eva(pos_eva, 0);
	init_pos_evo(pos_evo, 0);
	init_pos_nb(pos_nb, 0);

	SDL_BlitSurface(menu, NULL, ecran, &pos_men);
	SDL_BlitSurface(aide, NULL, ecran, &pos_reg);
	SDL_BlitSurface(reset, NULL, ecran, &pos_reset);
	
	SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_eva[0]);
	SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_eva[1]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
	
	/* Jeu à proprement parler */
	/* Variables utiles */
	SDL_Event event;
	
	int continuer = 1;
	int idx = -1;
	int pass = 0;
	int x_m, y_m;
	int n = 0;
	int chgt = 0;
	int blank4[4];
	
	int * poss = malloc(pow(8, 4) * sizeof(int));
	int s_possible = 0;
	int conseil[4];

	int *tab[10][2];
	for (j = 0; j < 10; j++) {
		tab[j][0] = malloc(4);
		for (i = 0; i < 4; i++) {
			tab[j][0][i] = -1;
		}
		tab[j][1] = malloc(2);
		for (i = 0; i < 2; i++) {
			tab[j][1][i] = 0;
		}
	}

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
            	
            	if (is_over(x_m, y_m, *menu, pos_men)) {
            		SDL_BlitSurface(menus, NULL, ecran, &pos_men);
            	} else if (is_over(x_m, y_m, *reset, pos_reset)) {
            		SDL_BlitSurface(resets, NULL, ecran, &pos_reset);
            	} else if (is_over(x_m, y_m, *aide, pos_reg)) {
            		SDL_BlitSurface(aides, NULL, ecran, &pos_reg);
            		SDL_BlitSurface(aide1, NULL, ecran, &pos_aide1);
            		SDL_BlitSurface(aide2, NULL, ecran, &pos_aide2);
            	} else if (ready_togo(tab[n][0], tab[n][1], n, 0) && is_over(x_m, y_m, *haut, pos_evo[0])) {
            		SDL_BlitSurface(hauts, NULL, ecran, &pos_evo[0]);
            	} else if (ready_togo(tab[n][0], tab[n][1], n, 1) && is_over(x_m, y_m, *haut, pos_evo[1])) {
            		SDL_BlitSurface(bass, NULL, ecran, &pos_evo[1]);
            	} else {
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            		SDL_BlitSurface(aide, NULL, ecran, &pos_reg);
            		SDL_BlitSurface(reset, NULL, ecran, &pos_reset);
            		SDL_BlitSurface(none_a1, NULL, ecran, &pos_aide1);
            		SDL_BlitSurface(none_a2, NULL, ecran, &pos_aide2);
            		
            		if (ready_togo(tab[n][0], tab[n][1], n, 0)) {
            			SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
            		}
            		if (ready_togo(tab[n][0], tab[n][1], n, 1)) {
            			SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
            		}
            	}
            	break;
            	
            case SDL_MOUSEBUTTONUP:
		        x_m = event.button.x;
		       	y_m = event.button.y;
		       	
		       	/* Bouton menu */
		       	if (is_over(x_m, y_m, *menu, pos_men)) {
            		continuer = 2;
            		pass = 1;
            	} else {
            		SDL_BlitSurface(menu, NULL, ecran, &pos_men);
            	}
		       	
		       	/* Apposition d'une couleur */
		       	if (!pass) {
				   	for (i = 0; i < 4; i++) {
					   	if (is_over(x_m, y_m, *vide, pos_chx[i])) {
					   		if (idx > -1) {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(pions[idx], NULL, ecran, &pos_chx[i]);
					   			tab[n][0][i] = idx;
					   			if (ready_togo(tab[n][0], tab[n][1], n, 0)) {
					   				SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
					   			}
					   		} else {
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
					   			SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
					   			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
					   			SDL_BlitSurface(none, NULL, ecran, &pos_evo[0]);
					   			tab[n][0][i] = -1;
					   		}
					   		pass = 1;
					   		break;
					   	}
					}
				}
		       	
		       	/* Sélection d'une couleur */
		       	if (!pass) {
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
		        
		        /* Flèches des pastilles */
		        if (!pass) {
		        	if (is_over(x_m, y_m, *p_droite, pos_fle[1]) && tab[n][1][0] < 4) {
		        		SDL_BlitSurface(p_rouge[++tab[n][1][0]], NULL, ecran, &pos_eva[0]);
		        		SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[0]);
		        		if (tab[n][1][0] == 4) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[1]);
		        		}
		        		pass = 1;
		        	} else if (is_over(x_m, y_m, *p_gauche, pos_fle[0]) && tab[n][1][0] > 0) {
		        		SDL_BlitSurface(p_rouge[--tab[n][1][0]], NULL, ecran, &pos_eva[0]);
		        		SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
		        		if (tab[n][1][0] == 0) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[0]);
		        		}
		        		pass = 1;
		        	} else if (is_over(x_m, y_m, *p_droite, pos_fle[3]) && tab[n][1][1] < 4) {
		        		SDL_BlitSurface(p_blanc[++tab[n][1][1]], NULL, ecran, &pos_eva[1]);
		        		SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[2]);
		        		if (tab[n][1][1] == 4) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[3]);
		        		}
		        		pass = 1;
		        	} else if (is_over(x_m, y_m, *p_gauche, pos_fle[2]) && tab[n][1][1] > 0) {
		        		SDL_BlitSurface(p_blanc[--tab[n][1][1]], NULL, ecran, &pos_eva[1]);
		        		SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
		        		if (tab[n][1][1] == 0) {
		        			SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[2]);
		        		}
		        	}
		        	
		        	if (ready_togo(tab[n][0], tab[n][1], n, 0)) {
						SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
					} else {
						SDL_BlitSurface(none, NULL, ecran, &pos_evo[0]);
					}
					if (ready_togo(tab[n][0], tab[n][1], n, 1)) {
						SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
					} else {
						SDL_BlitSurface(none, NULL, ecran, &pos_evo[1]);
					}
					
		        }
		        
		        /* Flèches d'évolution */
			    if (!pass) {
			    	if (ready_togo(tab[n][0], tab[n][1], n, 0) && is_over(x_m, y_m, *haut, pos_evo[0])) {
			    		chgt = 1;
			    	} else if (ready_togo(tab[n][0], tab[n][1], n, 1) && is_over(x_m, y_m, *bas, pos_evo[1])) {
			    		chgt = -1;
			    	}
			    	
			    	if (chgt != 0) {
						for (i = 0; i < 4; i++) {
							SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[i]);
						}
						for (i = 0; i < 2; i++) {
							SDL_BlitSurface(none, NULL, ecran, &pos_evo[i]);
						}

						n += chgt;
						
						if (chgt > 0) {
							s_possible = nb_remain (tab, n, poss);
							assist(tab, n, poss, s_possible, conseil);
							printf("%i-%i-%i-%i\n", conseil[0], conseil[1], conseil[2], conseil[3]);
							nb_decompo(s_possible, blank4);
							
							j = 0;
							for (i = 0; i < 4; i++) {
								if (j == 0) {
									if (blank4[i] > 0 || i == 3) {
										SDL_BlitSurface(nb[blank4[i]], NULL, ecran, &pos_nb[i]);
										j = 1;
									}
								} else {
									SDL_BlitSurface(nb[blank4[i]], NULL, ecran, &pos_nb[i]);
								}
							}
							init_pos_nb(pos_nb, n);
							
						} else {
							init_pos_nb(pos_nb, n);
							SDL_BlitSurface(none, NULL, ecran, &pos_nb[0]);
							SDL_BlitSurface(none, NULL, ecran, &pos_nb[2]);
						}
						
						chgt = 0;
						
			    		init_pos_chx(pos_chx, n);
						init_pos_fle(pos_fle, n);
						init_pos_eva(pos_eva, n);
						init_pos_evo(pos_evo, n);
						
						if (tab[n][1][0] == 0 && tab[n][1][1] == 0) {
							SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_eva[0]);
							SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_eva[1]);
						}
						if (tab[n][1][0] > 0) {
							SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[0]);
						}
						if (tab[n][1][0] < 4) {
							SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
						}
						if (tab[n][1][1] > 0) {
							SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[2]);
						}
						if (tab[n][1][1] < 4) {
							SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
						}
						if (ready_togo(tab[n][0], tab[n][1], n, 0)) {
							SDL_BlitSurface(haut, NULL, ecran, &pos_evo[0]);
						}
						if (ready_togo(tab[n][0], tab[n][1], n, 1)) {
							SDL_BlitSurface(bas, NULL, ecran, &pos_evo[1]);
						}
						
						pass = 1;
					}
	        	}
	        	
	        	/* Réinitialisation */
	        	if (!pass) {
	        		if (is_over(x_m, y_m, *reset, pos_reset)) {
	        			
	        			SDL_BlitSurface(none, NULL, ecran, &pos_evo[0]);
	        			
	        			SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 212));
						for (n = 9; n >= 0; n--) {
							init_pos_chx(pos_chx, n);
							init_pos_fle(pos_fle, n);
							init_pos_nb(pos_nb, n);
							init_pos_eva(pos_eva, n);
							for (i = 0; i < 4; i++) {
								tab[n][0][i] = -1;
								if (i < 2) {
									tab[n][1][i] = 0;
									SDL_BlitSurface(none, NULL, ecran, &pos_eva[i]);
									SDL_BlitSurface(none, NULL, ecran, &pos_nb[2 * i]);
								}
								SDL_BlitSurface(vide, NULL, ecran, &pos_chx[i]);
								SDL_BlitSurface(p_none, NULL, ecran, &pos_fle[i]);
								SDL_BlitSurface(p_none, NULL, ecran, &pos_nb[i]);
							}
						}
						SDL_SetColorKey(vide, SDL_SRCCOLORKEY, SDL_MapRGB(vide->format, 68, 116, 213));
						
						n = 0;
						init_pos_nb(pos_evo, n);
							
						SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_eva[0]);
						SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_eva[1]);
						SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
						SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
	        		}
	        	}
		        
		        pass = 0;
            	
           	default:
           		break;
       	}
       	SDL_Flip(ecran);
    }
    
	SDL_FreeSurface(jeu);
	
	SDL_FreeSurface(vert);
	SDL_FreeSurface(violet);
	SDL_FreeSurface(rouge);
	SDL_FreeSurface(orange);
	SDL_FreeSurface(noir);
	SDL_FreeSurface(jaune);
	SDL_FreeSurface(bleu);
	SDL_FreeSurface(blanc);
	
	SDL_FreeSurface(p_rouge0);
	SDL_FreeSurface(p_rouge1);
	SDL_FreeSurface(p_rouge2);
	SDL_FreeSurface(p_rouge3);
	SDL_FreeSurface(p_rouge4);
	SDL_FreeSurface(p_blanc0);
	SDL_FreeSurface(p_blanc1);
	SDL_FreeSurface(p_blanc2);
	SDL_FreeSurface(p_blanc3);
	SDL_FreeSurface(p_blanc4);
	SDL_FreeSurface(p_gauche);
	SDL_FreeSurface(p_droite);
	SDL_FreeSurface(p_none);
	
	SDL_FreeSurface(vide);
	SDL_FreeSurface(none);
	SDL_FreeSurface(haut);
	SDL_FreeSurface(bas);
	SDL_FreeSurface(hauts);
	SDL_FreeSurface(bass);
	
	SDL_FreeSurface(menu);
	SDL_FreeSurface(menus);
	
	return continuer;
}
