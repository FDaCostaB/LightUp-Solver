//
// Created by fabie on 05/04/2020.
//

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
};
typedef struct CNF CNF;

void afficherLit (Literal l);

void afficherClause (Clause* seq);

void afficherCNF (CNF* seq);

void addToClause(Clause *l, Literal x);

CellLiteral* newLiterral (void);

void detruireCellLit (CellLiteral* cel);

Clause * newClause (void);

CellClause *newCellClause();

void detruireClause (Clause* seq);

Clause *CopyClause(Clause *source);

CNF *newCNF(void);

void addToCNF(CNF *Cnf, Clause *C );

void detruireCNF (CNF* seq);

CNF* KChosenInClause(int k, Clause *c);

void KchosenInClauseRec(int k, int taille, int startIndex, CellLiteral *act, Clause *inConstruction,CNF *res);

#endif //INF432_LOGIC_H
