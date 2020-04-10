//
// Created by fabie on 05/04/2020.
//

#include <stdbool.h>
#include "grid.h"

#ifndef INF432_LOGIC_H
#define INF432_LOGIC_H

typedef unsigned int variable;

typedef enum {
    PLUS,
    MINUS
} Sign;

typedef struct literal{
    variable x;
    Sign sign;
} Literal;

struct CellLiteral{
    Literal x;
    struct CellLiteral *suivant;
};
typedef struct CellLiteral CellLiteral;

struct Clause{
    CellLiteral *tete;
    unsigned int taille;
};
typedef struct Clause Clause;

struct CellClause{
    Clause *c;
    struct CellClause *suivant;
};
typedef struct CellClause CellClause;

struct CNF{
    CellClause *tete;
    unsigned int taille;
    unsigned int nbVar;
};
typedef struct CNF CNF;

void afficherLit (Literal l);

void afficherClause (Clause* seq);

void afficherCNF (CNF* seq);

void addToClause(Clause *C, Literal x, bool neglect);

CellLiteral* newLiterral (void);

void detruireCellLit (CellLiteral* cel);

Clause * newClause (void);

CellClause *newCellClause();

void detruireClause (Clause* seq);

Clause *CopyClause(Clause *source);

void concatClause(Clause *c1, Clause *c2 );

CNF *newCNF(void);

void addToCNF(CNF *Cnf, Clause *C );

void concatCNF(CNF *cnf1, CNF *cnf2 );

void detruireCNF (CNF* seq);

CNF* KChosenInClause(int k, Clause *c, bool doNeglect);

CNF* KneglectedInClause(int k, Clause *c);

Clause* enumSubRow(Grid* grid, int i);

Clause* enumSubLine(Grid* grid, int i);

Clause* enumAdj(int taille, int i);

CNF* cnfOfBox(Grid *grid, int i);

#endif //INF432_LOGIC_H
