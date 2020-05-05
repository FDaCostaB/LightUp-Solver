//
// Created by fabie on 05/04/2020.
//

#include <stdbool.h>
#include "grid.h"

#ifndef INF432_LOGIC_H
#define INF432_LOGIC_H

/* A representation of variable usefull to write a DIMACS file where variable are unsigned int */
typedef unsigned int variable;

/* Sign for variable */
typedef enum {
    PLUS,
    MINUS
} Sign;

/* A variable and his sign */
typedef struct literal{
    variable x;
    Sign sign;
} Literal;

/* A cell containing a literal to create a linked list */
struct CellLiteral{
    Literal x;
    struct CellLiteral *suivant;
};
typedef struct CellLiteral CellLiteral;

/* A linked list of literal */
struct Clause{
    CellLiteral *tete;
    unsigned int taille;
};
typedef struct Clause Clause;

/* A cell containing a pointer of a clause to create a linked list */
struct CellClause{
    Clause *c;
    struct CellClause *suivant;
};
typedef struct CellClause CellClause;

/* A linked list of clause */
struct CNF{
    CellClause *tete;
    unsigned int taille;
    unsigned int nbVar;
};
typedef struct CNF CNF;

/* Disp a literal to help debug
 * Condition of use : Empty
 * Result: Void
 */
void afficherLit (Literal l);

/* Disp a clause to help debug
 * Condition of use : Empty
 * Result: Void
 */
void afficherClause (Clause* seq);

/* Disp a CNF to help debug
 * Condition of use : Empty
 * Result: Void
 */
void afficherCNF (CNF* seq);

/* Add a literal (neglected if neglect is true) to a clause
 * Condition of use : Empty
 * Result: Clause c with the literal x in it.
 */
void addToClause(Clause *C, Literal x, bool neglect);

/* A new cell literal initialized
 * Condition of use : Empty
 * Result: Fresh cell literal.
 */
CellLiteral* newLiterral (void);

/* Free the memory allocated for the cell literal
 * Condition of use : cel is a non null pointer (ERROR not handled)
 * Result: void
 */
void detruireCellLit (CellLiteral* cel);

/* A new clause initialized
 * Condition of use : Empty
 * Result: Fresh clause.
 */
Clause * newClause (void);

/* A new cell clause initialized
 * Condition of use : Empty
 * Result: Fresh cell clause.
 */
CellClause *newCellClause();

/* Free the memory allocated for the clause and the cell literal in it
 * Condition of use : seq is a non null pointer (ERROR not handled)
 * Result: void
 */
void detruireClause (Clause* seq);

/* Copy a clause and return a new pointer to the same clause
 * Condition of use : source is a non null pointer (ERROR not handled)
 * Result: The same clause in another pointer
 */
Clause *CopyClause(Clause *source);

/* Concat c1 and c2
 * Condition of use : Empty
 * Result: The concatenation is in c1 and c2 is freed
 * but what was in is linked with c1
 */
void concatClause(Clause *c1, Clause *c2 );

/* A new CNF initialized
 * Condition of use : Empty
 * Result: Fresh CNF.
 */
CNF *newCNF(void);

/* Add a clause to a CNF
 * Condition of use : Empty
 * Result: Cnf with the clause C at the end.
 */
void addToCNF(CNF *Cnf, Clause *C );

/* Concat cnf1 and cnf2
 * Condition of use : Empty
 * Result: The concatenation is in cnf1 and cnf2 is freed
 * but what was in is linked with cnf1
 */
void concatCNF(CNF *cnf1, CNF *cnf2 );

/* Free the memory allocated for the CNF and what is in it
 * Condition of use : seq is a non null pointer (ERROR not handled)
 * Result: void
 */
void detruireCNF (CNF* seq);

/* A function returning a conjunction of each clause of size K in Clause
 * using recursive code and pointer.
 * Condition of use : Clause c is a non null pointer (ERROR not handled)
 * Result: The list of all clause of size K in Clause c.
 */
CNF* KChosenInClause(int k, Clause *c, bool doNeglect);

/* A function returning the list of all clause with same variable of c
 * with K variable neglected. It use recursive code and pointer.
 * Condition of use : Clause c is a non null pointer (ERROR not handled)
 * Result: The list of all clause with same variable of c with K variable neglected.
 */
CNF* KneglectedInClause(int k, Clause *c);

/* A clause containing all the variable/index of the sub row of box at index i.
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: A clause containing all the variable/index of the sub row of box at index i
 */
Clause* enumSubRow(Grid* grid, int i);

/* A clause containing all the variable/index of the sub line of box at index i.
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: A clause containing all the variable/index of the sub line of box at index i
 */
Clause* enumSubLine(Grid* grid, int i);

/* A clause containing all the variable/index of adjacent box of box at index i.
 * Condition of use : Empty.
 * Result: A clause containing all the variable/index of adjacent box of box at index i.
 */
Clause* enumAdj(int taille, int i);

/* Return the CNF to find a model to solve the grid
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: A CNF who model the grid.
 */
CNF* cnfOfBox(Grid *grid, int i);

#endif //INF432_LOGIC_H
