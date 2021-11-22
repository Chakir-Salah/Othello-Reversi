/*
    Nom du fichier : jeu.c
    Auteur         : Chakir Salah Eddine
    Date           : 25/05/2021
    Role           : contient les fonctions qui gèrent les images après le début d'une partie

*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h> //pour donner aléatoirement  les noires soit au joueur soit au bot dans la partie joueur vs bot

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "jeu.h"
#include "constantes.h"
#include "gestion.h"
#include "gestion.c"

void charger(int *coup_a,int *debut_a,int *difficulte)
{
    int contre;
    FILE *fichier=fopen(FICHIER,"r");
    fscanf(fichier,"%d",&contre);
    fscanf(fichier,"%d",coup_a);
    fscanf(fichier,"%d",debut_a);
    fscanf(fichier,"%d",difficulte);
    for(int j=a; j<=h; j++)
    {
        for(int i=0; i<8; i++)
        {
            fscanf(fichier,"%d",&grille[i][j]);
        }
    }
    fclose(fichier);
}

void sauvgarder(int contre,int coup_a,int debut_a,int difficulte)
{
    FILE *fichier=fopen(FICHIER,"w");
    if(contre==HUMAIN)
    {
        fprintf(fichier,"%d ",HUMAIN);
        if(coup_a==NOIR)
            fprintf(fichier,"%d ",NOIR);
        else
            fprintf(fichier,"%d ",BLANC);
        fprintf(fichier,"%d ",debut_a); //dans cette partie il n'y a pas d'utilité de la variable debut_a
        fprintf(fichier,"%d ",difficulte);  //dans cette partie il n'y a pas d'utilité de la variable difficulte
    }
    else
    {
        fprintf(fichier,"%d ",BOT);
        if(coup_a==NOIR)
            fprintf(fichier,"%d ",NOIR);
        else
            fprintf(fichier,"%d ",BLANC);
        if(debut_a=HUMAIN)
            fprintf(fichier,"%d ",HUMAIN);
        else
            fprintf(fichier,"%d ",BOT);
        fprintf(fichier,"%d ",difficulte);
    }
    for(int j=a; j<=h; j++)
    {
        for(int i=0; i<8; i++)
        {
            fprintf(fichier,"%d ",grille[i][j]);
        }
    }
    fclose(fichier);
}
void afficher_coup_joue_et_resultat(SDL_Surface *ecran)
{
    SDL_Surface *texte_nb_pion_blanc=NULL,*texte_nb_pion_noir=NULL;
    SDL_Rect position_texte_blanc,position_texte_noir;

    position_texte_blanc.x=200;
    position_texte_blanc.y=20;

    position_texte_noir.x=1170;
    position_texte_noir.y=20;

    SDL_Surface *pion_blanc=NULL,*pion_noir=NULL,*board=NULL,*resultat_blanc=NULL,*resultat_noir=NULL;
    SDL_Rect position_board,position_pion,position_resultat_blanc,position_resultat_noir;

    TTF_Init();
    TTF_Font *police=NULL;
    police=TTF_OpenFont("police.ttf",40);
    SDL_Color couleurBlanche = {255, 255, 255};
    char resultat[3];

    pion_blanc=IMG_Load("pion_blanc.jpg");
    pion_noir=IMG_Load("pion_noir.jpg");
    board=IMG_Load("grille.jpg");
    resultat_blanc=IMG_Load("resultat_blanc.jpg");
    resultat_noir=IMG_Load("resultat_noir.jpg");

    position_board.x=280;
    position_board.y=0;

    position_resultat_blanc.x=32;
    position_resultat_blanc.y=0;

    position_resultat_noir.x=1000;
    position_resultat_noir.y=0;

    SDL_BlitSurface(board,NULL,ecran,&position_board); // poser sur l'écran noir l'image de la grille
    SDL_BlitSurface(resultat_blanc,NULL,ecran,&position_resultat_blanc);
    SDL_BlitSurface(resultat_noir,NULL,ecran,&position_resultat_noir);

    sprintf(resultat,"%d",nb_poin_blanc(grille));
    texte_nb_pion_blanc=TTF_RenderText_Blended(police,resultat,couleurBlanche);
    SDL_BlitSurface(texte_nb_pion_blanc,NULL,ecran,&position_texte_blanc);
    sprintf(resultat,"%d",nb_poin_noir(grille));
    texte_nb_pion_noir=TTF_RenderText_Blended(police,resultat,couleurBlanche);
    SDL_BlitSurface(texte_nb_pion_noir,NULL,ecran,&position_texte_noir);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(grille[i][j]==BLANC)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_blanc,NULL,ecran,&position_pion);
            }
            if(grille[i][j]==NOIR)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_noir,NULL,ecran,&position_pion);
            }
        }
    }
    SDL_Flip(ecran);

    SDL_FreeSurface(pion_blanc);
    SDL_FreeSurface(pion_noir);
    SDL_FreeSurface(resultat_blanc);
    SDL_FreeSurface(resultat_noir);
    SDL_FreeSurface(board);
    SDL_FreeSurface(texte_nb_pion_blanc);
    SDL_FreeSurface(texte_nb_pion_noir);

    TTF_CloseFont(police);
    TTF_Quit();
}

void affihcer_coup_propose(SDL_Surface *ecran)
{
    SDL_Surface *pion_blanc_propose=NULL,*pion_noir_propose=NULL;
    SDL_Rect position_pion;

    pion_blanc_propose=IMG_Load("pion_blanc.jpg");
    pion_noir_propose=IMG_Load("pion_noir.jpg");

    SDL_SetAlpha(pion_blanc_propose, SDL_SRCALPHA, 50);
    SDL_SetAlpha(pion_noir_propose, SDL_SRCALPHA, 50);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(grille[i][j]==BLANC_PROPOSE)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_blanc_propose,NULL,ecran,&position_pion);
            }
            if(grille[i][j]==NOIR_PROPOSE)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_noir_propose,NULL,ecran,&position_pion);
            }
        }
    }
    SDL_Flip(ecran);
    SDL_FreeSurface(pion_blanc_propose);
    SDL_FreeSurface(pion_noir_propose);
}

void affihcer_gagnant(SDL_Surface *ecran)
{
    SDL_Surface *trophee=NULL;
    SDL_Rect position_trophee;
    trophee=IMG_Load("trophee.png");
    if(nb_poin_blanc(grille)>nb_poin_noir(grille))
    {
        position_trophee.x=0;
        position_trophee.y=200;
        SDL_BlitSurface(trophee,NULL,ecran,&position_trophee);
    }
    else if(nb_poin_blanc(grille)<nb_poin_noir(grille))
    {
        position_trophee.x=1000;
        position_trophee.y=200;
        SDL_BlitSurface(trophee,NULL,ecran,&position_trophee);
    }
    SDL_Flip(ecran);
    SDL_FreeSurface(trophee);
}
void jouer(SDL_Surface *ecran,int reprendre)
{
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
    int quitter=0,coup_a=NOIR,a,b,debut_a=1,difficulte=0;
    SDL_Event clic;

    if(!reprendre)
    {
        initialiser_grille(grille); //remplir le tableau qui représente la grille
    }
    else
    {
        charger(&coup_a,&debut_a,&difficulte);
    }
    afficher_coup_joue_et_resultat(ecran);

    proposer_coup(grille,coup_a); //proposer les coups au noir

    affihcer_coup_propose(ecran);

    nettoyer_grille(grille); //supprimer les coup proposés dans le tableau

    while(!Partie_terminee(grille) && !quitter)
    {
        SDL_WaitEvent(&clic);
        switch(clic.type)
        {
        case SDL_QUIT:
            quitter=1;
            break;
        case SDL_KEYDOWN:
            switch(clic.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                quitter = 1;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch(clic.button.button)
            {
            case SDL_BUTTON_LEFT: // clique gauche par la souris
                a=clic.button.x;
                b=clic.button.y;
                if(a>280 && a<1000)
                {
                    if(coup_valide(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a))
                    {
                        jouez_coup(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a);

                        afficher_coup_joue_et_resultat(ecran);

                        if(coup_a==NOIR)
                        {
                            if(encore_coup(grille,BLANC))
                                coup_a=BLANC;
                            else if(!encore_coup(grille,NOIR))
                                quitter=1;
                            proposer_coup(grille,coup_a);
                        }
                        else if(coup_a==BLANC)
                        {
                            if(encore_coup(grille,NOIR))
                                coup_a=NOIR;
                            else if(!encore_coup(grille,BLANC))
                                quitter=1;
                            proposer_coup(grille,coup_a);
                        }
                        affihcer_coup_propose(ecran);
                        nettoyer_grille(grille); //supprimer les coup proposés dans le tableau
                    }
                }
                break;
            }
        }
    }
    afficher_coup_joue_et_resultat(ecran);

    if(Partie_terminee(grille)) // affihcer qui a gagné
    {
        affihcer_gagnant(ecran);
        quitter=0;
        while(!quitter)
        {
            SDL_WaitEvent(&clic);
            switch(clic.type)
            {
            case SDL_QUIT:
                quitter=1;
                break;
            case SDL_KEYDOWN:
                switch(clic.key.keysym.sym)
                {
                case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                    quitter = 1;
                    break;
                }
                break;
            }
        }

    }
    sauvgarder(HUMAIN,coup_a,debut_a,difficulte); //sauvgarder avant de quitter
}

void jouer_vs_bot(SDL_Surface *ecran,int reprendre)
{
    int difficulte;
    if(!reprendre)
    {
        //Configuration de la difficulté
        SDL_Surface *menu=NULL;
        SDL_Rect position_menu;
        SDL_Event clic_menu;
        int continuer=1;

        menu=IMG_Load("Vs_BOT.jpg");
        position_menu.x=100;
        position_menu.y=0;
        SDL_BlitSurface(menu,NULL,ecran,&position_menu);
        SDL_Flip(ecran);
        while(continuer)
        {
            SDL_WaitEvent(&clic_menu);
            switch(clic_menu.type)
            {
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYDOWN:
                switch(clic_menu.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(clic_menu.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(clic_menu.button.y>400 && clic_menu.button.y<680)
                    {
                        if(clic_menu.button.x>160 && clic_menu.button.x<440)
                        {
                            difficulte=FACILE;
                            continuer=0;
                        }
                        if(clic_menu.button.x>500 && clic_menu.button.x<780)
                        {
                            difficulte=MOYEN;
                            continuer=0;
                        }
                        if(clic_menu.button.x>840 && clic_menu.button.x<1120)
                        {
                            difficulte=DIFFICILE;
                            continuer=0;
                        }
                    }
                }
                break;
            }
        }
        SDL_FreeSurface(menu);
    }
    //début de la partie humain vs bot
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
    srand(time(NULL));
    int debut_a=(rand()%2); //qui va commencer HUMAIN=0 ou BOT=1

    int quitter=0,coup_a=NOIR,a,b;
    SDL_Event clic;

    if(!reprendre)
    {
        initialiser_grille(grille); //remplir le tableau qui représente la grille
        afficher_coup_joue_et_resultat(ecran);
        if(debut_a==HUMAIN) //si l'humain commence le premier , on lui affihce les coup proposés
        {
            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup proposés dans le tableau
        }
        else //sinon le bot joue le premier coup , puis on affihce les coup proposés
        {
            SDL_Delay(500); //attendre 0.5s avant de jouer le le coup
            jouez_coup(grille,bot(grille,NOIR,difficulte).x,bot(grille,NOIR,difficulte).y,coup_a);
            afficher_coup_joue_et_resultat(ecran);

            coup_a=BLANC;

            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup proposés dans le tableau
        }
    }

    if(reprendre)
    {
        charger(&coup_a,&debut_a,&difficulte);
        afficher_coup_joue_et_resultat(ecran);
        if((debut_a==HUMAIN && coup_a==NOIR) || (debut_a==BOT && coup_a==BLANC))
        {
            proposer_coup(grille,coup_a);
            affihcer_coup_propose(ecran);
            nettoyer_grille(grille);
        }
    }


    while(!Partie_terminee(grille) && !quitter)
    {
        if((debut_a==HUMAIN && coup_a==NOIR) || (debut_a==BOT && coup_a==BLANC)) // si le trait à l'humain
        {
            SDL_WaitEvent(&clic);
            switch(clic.type)
            {
            case SDL_QUIT:
                quitter=1;
                break;
            case SDL_KEYDOWN:
                switch(clic.key.keysym.sym)
                {
                case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                    quitter = 1;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(clic.button.button)
                {
                case SDL_BUTTON_LEFT: // clique gauche par la souris
                    a=clic.button.x;
                    b=clic.button.y;
                    if(a>280 && a<1000)
                    {
                        if(coup_valide(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a))
                        {
                            jouez_coup(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a);

                            afficher_coup_joue_et_resultat(ecran);

                            if(coup_a==NOIR)
                            {
                                if(encore_coup(grille,BLANC))
                                    coup_a=BLANC;
                                else if(!encore_coup(grille,NOIR))
                                    quitter=1;
                            }
                            else if(coup_a==BLANC)
                            {
                                if(encore_coup(grille,NOIR))
                                    coup_a=NOIR;
                                else if(!encore_coup(grille,BLANC))
                                    quitter=1;
                            }
                        }
                    }
                    break;
                }
            }
        }
        else
        {
            SDL_Delay(500); //attendre 0.5s avant de jouer le le coup
            jouez_coup(grille,bot(grille,coup_a,difficulte).x,bot(grille,coup_a,difficulte).y,coup_a);
            afficher_coup_joue_et_resultat(ecran);

            if(coup_a==NOIR)
            {
                if(encore_coup(grille,BLANC))
                    coup_a=BLANC;
                else if(!encore_coup(grille,NOIR))
                    quitter=1;
            }
            else if(coup_a==BLANC)
            {
                if(encore_coup(grille,NOIR))
                    coup_a=NOIR;
                else if(!encore_coup(grille,BLANC))
                    quitter=1;
            }

            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup proposés dans le tableau
        }
    }
    afficher_coup_joue_et_resultat(ecran);

    if(Partie_terminee(grille)) // affihcer qui a gagné
    {
        affihcer_gagnant(ecran);
        quitter=0;
        while(!quitter)
        {
            SDL_WaitEvent(&clic);
            switch(clic.type)
            {
            case SDL_QUIT:
                quitter=1;
                break;
            case SDL_KEYDOWN:
                switch(clic.key.keysym.sym)
                {
                case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                    quitter = 1;
                    break;
                }
                break;
            }
        }

    }
    sauvgarder(BOT,coup_a,debut_a,difficulte); //sauvgarder avant de quitter
}
