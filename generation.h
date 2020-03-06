//
// Created by fabie on 03/03/2020.
//

#ifndef INF432_GENERATION_H
#define INF432_GENERATION_H

#include <stdbool.h>

typedef enum {
  INCONNU,
  LIBRE,
  MURV,
  MUR0,
  MUR1,
  MUR2,
  MUR3,
  MUR4,
  LAMPE,
  VIDE
} Case;

typedef struct {
  Case *tab;
  int taille;
} Grille;

int nbCasesLibresAdj(Grille *grille, int i);

Case placerMur(Grille *grille, int i);

void placerLampe(Case actuel, int i, Grille *grille);

Grille *genere_grille(int pourcentMur);

bool lampe_possible(int i, Grille *grille);

void afficher_grille(Grille *grille);

Grille *readGrid(char *fileName);

#endif // INF432_GENERATION_H
