#ifndef JEU_H
#define JEU_H

int printJeu(SDL_Surface *ecran);
void chx_code(int code[4]);
void init_pos_chx (SDL_Rect pos[4], int n);
int is_over(int x, int y, SDL_Surface s, SDL_Rect p);
int all_fill(int code[4]);
void init_pos_opt (SDL_Rect pos[2], int n);

#endif
