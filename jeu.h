/*
    Nom du fichier : jeu.h
    Auteur         : Chakir Salah Eddine
    Date           : 25/05/2021
    Role           : contient les prototypes des fonctions du fichier .c et le tableau qui représente la grille 8x8

*/



#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

int grille[8][8];
void afficher_coup_joue_et_resultat(SDL_Surface *ecran);
void affihcer_coup_propose(SDL_Surface *ecran);
void affihcer_gagnant(SDL_Surface *ecran);
void jouer(SDL_Surface *ecran,int reprendre);
void jouer_vs_bot(SDL_Surface *ecran,int reprendre);

#endif // JEU_H_INCLUDED
