//
// Created by fabie on 07/04/2020.
//
#include "logic.h"
#include <stdio.h>

#ifndef INF432_DIMACS_H
#define INF432_DIMACS_H

/* Parse DIMACS formated file in fileName
 * Condition of use : fileName can be open and follow the DIMACS format (ERROR handled)
 * Result: CNF representing the problem in the DIMACS file
 */
CNF *readDimacs(char *fileName);

/* Parse minisat output read in fileName
 * Condition of use : fileName can be open and follow the minisat output format (ERROR handled)
 * Result: Clause representing the model found or NULL if no model was found(WalkSat)/exist(minisat).
 */
Clause *readMinisatOut(char *fileName);

/* Disp the correction of grid given by the sat solver use
 * Condition of use : solution and grid are non null pointer (ERROR not handled)
 * Result: Void
 */
void dispMinisatOutput(Clause *solution, Grid *grid);

/* Write a DIMACS format file the CNF toWrite in fileName file.
 * Condition of use : fileName can be open (handled) and toWrite is a non null pointer (not handled)
 * Result: File with the problem written in following DIMACS format.
 */
void writeDimacs(char *fileName,CNF *toWrite, unsigned int toAdd);

/* Return true if x belong to c fals otherwise
 * Condition of use : c is a non null pointer (ERROR not handled)
 * Result: Return true if x belong to c fals otherwise
 */
bool inClause(Clause *c,Literal l);

/* Transform a clause to a 3SAT problem (CNF with only clause(s) of size 3)
 * Condition of use : c is a non null pointer (ERROR not handled)
 * Result: CNF with only clause(s) of size 3 with the same satisfiability condition of c
 */
CNF * SATto3SAT(Clause *c, unsigned int *tailleCNF );

#endif //INF432_DIMACS_H
