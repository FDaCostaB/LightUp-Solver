//
// Created by fabie on 07/04/2020.
//
#include "logic.h"
#include <stdio.h>

#ifndef INF432_DIMACS_H
#define INF432_DIMACS_H

CNF *readDimacs(char *fileName);

Clause *readMinisatOut(char *fileName);

void dispMinisatOutput(Clause *solution, Grid *grid);

void writeDimacs(char *fileName,CNF *toWrite, unsigned int toAdd);

bool inClause(Clause *c,Literal l);

CNF * SATto3SAT(Clause *c, unsigned int *tailleCNF );

#endif //INF432_DIMACS_H
