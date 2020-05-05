//
// Created by fabie on 14/04/2020.
//

#include "logic.h"

#ifndef INF432_SOLVER_H
#define INF432_SOLVER_H

/* assignation as list of literal where
 * the sign correspond to the value (true or false) associated
 * to the variable linked with.
 */
typedef struct assignation {
    Literal *tab;
    unsigned int size;
} Assignation;

/* A data structure where all data needed to compute a variable
 * to flip according to a heuristics The goal is to compute it
 * only one time to be less complex.
 */
typedef struct enumCNF {
    int *valueComputed;
    float *sumSize;
    unsigned int size;
    int totalSum;
} enumCNF;

/* Generate a random assignation.
 * Condition of use : Empty
 * Result: An assignation where the value assignated to each variable is random.
*/
Assignation *newRandomAssignation(unsigned int size);

/* Flip the value of a literal in the assignation v.
 * Condition of use : v is a non null pointer (ERROR not handled)
 * Result: Assignation v where the value assignated to val is changed.
*/
void flipInAssignation(int val,Assignation *v);

/* Allocate, initialize an enumCNF struct.
 * Condition of use : Empty
 * Result: enumCnf value filled with default value (zero) and his size
*/
enumCNF *initEnumCNF(unsigned int size);

/* Disp the assignation on the console to help debug.
 * Condition of use : model is a non null pointer (ERROR not handled)
 * Result: void
*/
void dispAssignation(Assignation *model);

/* Write the assignation in the file named file name to write a model once found.
 * Condition of use : model is a non null pointer and file can be open (ERROR handled)
 * Result: File with assignation writen in it.
 */
void writeAssignation(char *fileName, Assignation *model);

/* Count the number of occurence(s) of the variable in clause.
 * Condition of use : model is a non null pointer and file exist (ERROR handled)
 * Result: Number of occurences of x in c.
 */
int countClause(Clause *c,variable x);

/* Pick a random variable in clause c.
 * Condition of use : c is a non null pointer (ERROR not handled)
 * Result: Random variable.
 */
variable drawVariable(Clause *c);

/* Return the first unsatisfied clause found in the CNF,
 * or a null pointer if it doesn't exist.
 * Condition of use : toSolve and v are non null pointer (ERROR not handled)
 * Result: Unsatisfied clause
 */
Clause *unsatisfiedClause(CNF *toSolve, Assignation *v);

/* Return true if assignation model the CNF toSolve.
 * Condition of use : toSolve and v are non null pointer (ERROR not handled)
 * Result: File with assignation writen in it.
 */
bool isModelCNF(CNF *toSolve,Assignation *v);

/* Choose a variable according to MOMS heuristics.
 * Condition of use : clause and enumeration are non null pointer (ERROR not handled)
 * Result: A variable to flip
 */
variable chooseVariableMOMS(Clause *clause, enumCNF *enumeration);

/* Choose a variable according to JW heuristics.
 * Condition of use : clause and enumeration are non null pointer (ERROR not handled)
 * Result: A variable to flip
 */
variable chooseVariableJW(Clause *clause, enumCNF *enumeration);

/* Choose a variable according to a score computed heuristics.
 * Condition of use : clause and enumeration are non null pointer (ERROR not handled)
 * Result: A variable to flip
 */
variable chooseVariableScore(Clause *clause, enumCNF * enumeration);

/* Choose a variable according to a least modified variable heuristics.
 * Condition of use : clause is a non null pointer (ERROR not handled)
 * Result: A variable to flip
 */
variable chooseVariableModif(Clause *clause, unsigned int * modif);

/* Attribute a score and the sum of clause size where the variable appear
 * for each variable. The goal is to compute it only one time to be less complex.
 * Condition of use : cnf is a non null pointer (ERROR not handled)
 * Result: A data structure where all data needed to compute a variable to flip according to a heuristics
 */
enumCNF *countCNF(CNF *cnf,int maxSize);

/* Disp the data structure on the console to help debug.
 * Condition of use : countCNF is a non null pointer (ERROR not handled)
 * Result: void
 */
void dispEnumCNF(enumCNF *countCNF);

/* Free the assignation to avoid memory leak.
 * Condition of use : v is a non null pointer (ERROR not handled)
 * Result: void
 */
void freeAssignation(Assignation *v);

/* Free the enumCNF to avoid memory leak.
 * Condition of use : enumeration is a non null pointer (ERROR not handled)
 * Result: void
 */
void freeEnumCNF(enumCNF *enumeration);

/* Try to find a model for the CNF toSolve according to a heuristics(mode)
 * Condition of use : toSolve is a non null pointer (ERROR handled)
 * Result: A model of the CNF if one is found.
 */
Assignation *WalkSat(CNF *toSolve, unsigned int mode);

#endif //INF432_SOLVER_H
