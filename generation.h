//
// Created by fabie on 03/03/2020.
//

#ifndef INF432_GENERATION_H
#define INF432_GENERATION_H


#include <stdbool.h>
#define TAILLE 7

typedef enum { INCONNU, LIBRE, MURV, MUR0, MUR1, MUR2, MUR3, MUR4, LAMPE, VIDE } Case;

typedef struct{
    Case tab[TAILLE * TAILLE];
} Grille;

int nbCasesLibresAdj(Grille *grille,int i);

Case placerMur(Grille *grille,int i);

void placerLampe(Case actuel,int i, Grille *grille);

Grille *genere_grille(int pourcentMur);

bool lampe_possible(int i,Grille *grille);

void afficher_grille(Grille *grille);

#endif //INF432_GENERATION_H
