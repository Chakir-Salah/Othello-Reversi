/*
    Nom du fichier : platform.c
    Auteur         : Chakir Salah Eddine
    Date           : 25/05/2021
    Role           : contient les fonctions qui affichent les images avant le début du jeu

*/

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "platform.h"
#include "jeu.h"
#include "jeu.c"

void platforme2(SDL_Surface* ecran)
{
    SDL_Surface *menu3=NULL;
    SDL_Event event2;
    SDL_Rect position_menu;
    int continuer2=1;
    menu3=IMG_Load("menu3.jpg");
    position_menu.x=100;
    position_menu.y=0;
    //afficher "Vs joueur" ou "Vs bot"
    while(continuer2)
    {
        SDL_BlitSurface(menu3,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu
        SDL_Flip(ecran); // actualisation
        SDL_WaitEvent(&event2); //attendre un clic
        switch(event2.type)
        {
        case SDL_QUIT: // clic sur "Fermer" "X"
            continuer2=0;
            break;
        case SDL_KEYDOWN: // clic sur un bouton
            switch(event2.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                continuer2 = 0;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP: //clic sur un boutton de la souris
            switch(event2.button.button)
            {
            case SDL_BUTTON_LEFT: // clic gauche par la souris
                if(event2.button.x>=380 && event2.button.x<=900) //clic dans le menu3
                {
                    if(event2.button.y>=200 && event2.button.y<=300) // clic sur "Vs joueur"
                    {
                        //début de la partie joueur vs joueur
                        //appel de la fonction jouer()
                        jouer(ecran,0);
                        continuer2=0;
                    }
                    else if(event2.button.y>=350 && event2.button.y<=450) // clic sur "Vs bot"
                    {
                        //début de la partie joueur vs ordinateur
                        //appel de la fonction jouer()
                        jouer_vs_bot(ecran,0);
                        continuer2=0;

                    }
                }
                break;
            }
            break;
        }
    }
    SDL_FreeSurface(menu3);
}

void platforme_reprendre(SDL_Surface *ecran)
{
    int vs;
    FILE *fichier=fopen(FICHIER,"r");
    fscanf(fichier,"%d",&vs);
    fclose(fichier);
    if(vs==HUMAIN) jouer(ecran,1);
    else if(vs==BOT) jouer_vs_bot(ecran,1);
}
