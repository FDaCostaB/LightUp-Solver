//
// Created by fabie on 14/04/2020.
//

#include "logic.h"

#ifndef INF432_SOLVER_H
#define INF432_SOLVER_H

typedef struct assignation {
    Literal *tab;
    unsigned int size;
} Assignation;

typedef struct enumCNF {
    int *valueComputed;
    float *sumSize;
    unsigned int size;
    int totalSum;
} enumCNF;

Assignation *newRandomAssignation(unsigned int size);

void flipInAssignation(int val,Assignation *v);

enumCNF *initEnumCNF(unsigned int size);

void dispAssignation(Assignation *model);

void writeAssignation(char *fileName, Assignation *model);

int countClause(Clause *c,variable x);

bool belongClause(Clause *c,variable x);

variable drawVariable(Clause *c);

Clause *unsatisfiedClause(CNF *toSolve, Assignation *v);

bool isModelCNF(CNF *toSolve,Assignation *v);

variable chooseVariableMOMS(Clause *clause, enumCNF *enumeration);

variable chooseVariableJW(Clause *clause, enumCNF *enumeration);

variable chooseVariableScore(Clause *clause, enumCNF * enumeration);

variable chooseVariableModif(Clause *clause, unsigned int * modif);

enumCNF *countCNF(CNF *cnf,int maxSize);

void dispEnumCNF(enumCNF *countCNF);

void freeAssignation(Assignation *v);

void freeEnumCNF(enumCNF *enumeration);

Assignation *WalkSat(CNF *toSolve);

#endif //INF432_SOLVER_H
