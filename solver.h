//
// Created by fabie on 14/04/2020.
//

#include "logic.h"

#ifndef INF432_SOLVER_H
#define INF432_SOLVER_H

typedef struct assignation {
    Literal *tab;
    int size;
} Assignation;

typedef struct enumCNF {
    int *valueComputed;
    float *sumSize;
    int size;
    int totalSum;
} enumCNF;

Assignation *newRandomAssignation(int size);

void flipInAssignation(int val,Assignation *v);

enumCNF *initEnumCNF(int size);

void dispAssignation(Assignation *model);

int countClause(Clause *c,variable x);

bool belongClause(Clause *c,variable x);

variable drawVariable(Clause *c);

Clause *unsatisfiedClause(CNF *toSolve, Assignation *v);

bool isModelCNF(CNF *toSolve,Assignation *v);

variable chooseVariableMOMS(CNF *tosolve, Clause *clause, enumCNF *enumeration);

variable chooseVariableJW(CNF *tosolve, Clause *clause, enumCNF *enumeration);

variable chooseVariableScore(CNF *tosolve, Clause *clause, enumCNF * enumeration);

enumCNF *countCNF(CNF *cnf,int maxSize);

void dispEnumCNF(enumCNF *countCNF);

Assignation *WalkSat(CNF *toSolve);

#endif //INF432_SOLVER_H
