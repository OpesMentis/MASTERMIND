#ifndef HELPER_H
#define HELPER_H

int printAssistant(SDL_Surface *ecran);
void init_pos_fle (SDL_Rect pos[4], int n);
void init_pos_eva (SDL_Rect pos[2], int n);
void init_pos_evo (SDL_Rect pos[2], int n);
void init_pos_nb (SDL_Rect pos[4], int n);
int ready_togo (int code[4], int n_past[2], int n, int sens);
void assist (int * tab[10][2], int n, int * poss, int s, int conseil[4]);
int nb_remain (int * tab[10][2], int n, int * poss);
void decode(int code, int a[4]);
void nb_decompo(int nb, int a[4]);

#endif
