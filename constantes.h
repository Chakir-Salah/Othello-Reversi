/*
    Nom du fichier : constantes.h
    Auteur         : Chakir Salah Eddine
    Date           : 25/05/2021
    Role           : contient les constantes et les variables utilisées

*/


#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

    #define LARGEUR_FENETRE 1280
    #define HAUTEUR_FENETRE 720
    #define TAILLE_BLOC 90
    #define POSITION_GRILLE_X 280
    #define POSITION_GRILLE_Y 0
    #define FICHIER "sauvgarde.othello" //le fichier qui contient la dernière partie joué
    struct coup{
        int x;
        int y;
    };
    typedef struct coup coup;
    enum{a,b,c,d,e,f,g,h};
    enum{VIDE,NOIR,BLANC,NOIR_PROPOSE,BLANC_PROPOSE};
    enum{HUMAIN,BOT};
    enum{FACILE,MOYEN,DIFFICILE};

#endif // CONSTANTES_H_INCLUDED
