/*********************************
*								 *
* Assistant de jeu				 *
*								 *
*********************************/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "assistant.h"
#include "jeu.h"

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
	SDL_Surface *rien = IMG_Load("img/rien.png");
	
	SDL_Surface *vide = IMG_Load("img/vide.png");
	SDL_Surface *none = IMG_Load("img/none2.png");
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
	SDL_Rect pos_reg = {40, 440}; // position du bouton 'Règles'
	SDL_Rect pos_jou = {240, 440}; // position du bouton 'Nouvelle partie'
	SDL_Rect pos_men = {440, 440}; // position du bouton 'Menu'
	SDL_Rect pos_chx[4]; // position des réceptacles des pions
	SDL_Rect pos_opt[2]; // position des boutons
	SDL_Rect pos_res[2] = {{460, 390}, {530, 390}}; // position des pastilles d'évaluation
	SDL_Rect pos_fle[4] = {{450, 390}, {480, 390}, {520, 390}, {550, 390}}; // position des fléchettes
	
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
//	init_pos_opt(pos_opt, 0);
//	init_pos_res(pos_res, 0);
	
//	SDL_BlitSurface(annul, NULL, ecran, &pos_opt[0]);
	SDL_BlitSurface(jouer, NULL, ecran, &pos_jou);
	SDL_BlitSurface(regle, NULL, ecran, &pos_reg);
	SDL_BlitSurface(menu, NULL, ecran, &pos_men);
	
	SDL_BlitSurface(p_rouge0, NULL, ecran, &pos_res[0]);
	SDL_BlitSurface(p_blanc0, NULL, ecran, &pos_res[1]);
	SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[0]);
	SDL_BlitSurface(p_gauche, NULL, ecran, &pos_fle[2]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[1]);
	SDL_BlitSurface(p_droite, NULL, ecran, &pos_fle[3]);
	
	/* Jeu à proprement parler */
	/* Variables utiles */
	int continuer = 1;
	int idx = -1;
	int pass = 0;
//	int x_m, y_m;
	SDL_Event event;
	int n_essai = 0;
	int essai[4] = {-1, -1, -1, -1};
	int over = 0;
	
	/* Choix du code */
	int code[4];
	chx_code(code);
	
	SDL_Flip(ecran);
	
	while (continuer == 1) {
    	SDL_WaitEvent(&event);
        switch (event.type) {
           	case SDL_QUIT:
               	continuer = 0;
               	break;
            	
           	default:
           		break;
       	}
       	SDL_Flip(ecran);
    }
	
	return continuer;
}
