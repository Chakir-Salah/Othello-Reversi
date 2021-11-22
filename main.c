#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constantes.h"
#include "platform.h"
#include "platform.c"

int main ( int argc, char** argv )
{
    SDL_Surface *ecran=NULL,*menu=NULL,*menu2=NULL;
    SDL_Rect position_menu;
    SDL_Event event;

    int continuer=1;

    SDL_Init(SDL_INIT_VIDEO); // initialisation de SDL_video
    if(SDL_Init(SDL_INIT_VIDEO)<0) // vérification de l'initialisation de la SDL_video
    {
        printf("Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Othello",NULL);
    SDL_WM_SetIcon(IMG_Load("icon.jpg"),NULL); // l'incone doit etre chargé avant SDL_SetVideoMode

    ecran=SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32, SDL_HWSURFACE | SDL_DOUBLEBUF); // création d'une fenetre; /* Double Buffering */ // création d'une fenetre
    if(ecran==NULL) // tester si la fenetre a été crée
    {
        printf("Erreur de la creation de la fenetre : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    menu=IMG_Load("menu.jpg");
    menu2=IMG_Load("menu2.jpg");
    position_menu.x=100;
    position_menu.y=0;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
    SDL_BlitSurface(menu,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu
    SDL_Flip(ecran); // actualisation
    SDL_Delay(2000); //attend 2 secondes
    SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
    SDL_Flip(ecran); // actualisation
    SDL_FreeSurface(menu);
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                continuer = 0;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT: // clique gauche par la souris
                if(event.button.x>=380 && event.button.x<=900)
                {
                    if(event.button.y>=200 && event.button.y<=300) // clic sur "nouvelle partie"
                    {
                        //platforme2
                        platforme2(ecran);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
                        SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
                        SDL_Flip(ecran); // actualisation
                    }
                    else if(event.button.y>=340 && event.button.y<=440) // clic sur "Reprendre"
                    {
                        //reprendre la partie sauvgardée
                        platforme_reprendre(ecran);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
                        SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
                        SDL_Flip(ecran); // actualisation
                    }
                    else if(event.button.y>=480 && event.button.y<=530) //clic sur "Quitter"
                    {
                        //quitter le jeu
                        continuer=0;
                    }
                }
                break;
            }
        }

    }
    SDL_FreeSurface(menu2);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return EXIT_SUCCESS;

}
