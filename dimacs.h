//
// Created by fabie on 07/04/2020.
//
#include "logic.h"
#include <stdio.h>

#ifndef INF432_DIMACS_H
#define INF432_DIMACS_H

CNF *readDimacs(FILE *f);

Clause *readMinisatOut(char *fileName);

void dispMinisatOutput(Clause *solution, Grid *grid);

void writeDimacs(char *fileName,CNF *toWrite);

CNF * SATto3SAT(Clause *c, int *tailleCNF );

#endif //INF432_DIMACS_H
