//
// Created by fabie on 07/04/2020.
//
#include "logic.h"
#include <stdio.h>

#ifndef INF432_DIMACS_H
#define INF432_DIMACS_H

CNF *readDimacs(FILE *f);

void writeDimacs(FILE *f,CNF *toWrite);

#endif //INF432_DIMACS_H
