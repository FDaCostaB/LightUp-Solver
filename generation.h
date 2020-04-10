//
// Created by fabie on 03/03/2020.
//

#ifndef INF432_GENERATION_H
#define INF432_GENERATION_H

#include <stdbool.h>
#include "grid.h"


int nbCasesLibresAdj(Grid *grille, int i);

Box placerMur(Grid *grille, int i);

void placerLampe(Box actuel, int i, Grid *grille);

Grid *genere_grille(int pourcentMur, int taille);

void clearGrid(Grid *grid);

bool lampe_possible(int i, Grid *grille);

void dispGrid(Grid *grid);

void writeGrid(char *fileName,Grid *grid);

Grid *readGrid(char *fileName);

bool isWall(Grid *grille, int index);

Grid *newGrid(int size);

#endif // INF432_GENERATION_H
