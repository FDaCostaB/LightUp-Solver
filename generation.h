//
// Created by fabie on 03/03/2020.
//

#ifndef INF432_GENERATION_H
#define INF432_GENERATION_H

#include <stdbool.h>
#include "grid.h"

/* Return the number of free box adjacent to box at index i
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: Number of free box adjacent to box at index i
 */
int nbCasesLibresAdj(Grid *grille, int i);

/* Give a type of wall that don't make the grid unsolvable if place at index i
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: A variant of wall
 */
Box placerMur(Grid *grille, int i);

/* Dispose lights around a wall to avoid unsolvable grid due to lights
 * in a same sub row/line place in the end of generation
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: Void
 */
void placerLampe(Box actuel, int i, Grid *grille);

/* Generate a grid of size "taille" and with a density near "pourcentMur" (can be unsolvable)
 * Condition of use : Empty
 * Result: A grid
 */
Grid *genere_grille(int pourcentMur, int taille);

/* Delete all box who are not a variant of walls or an empty box
 * Condition of use : Empty
 * Result: Void
 */
void clearGrid(Grid *grid);

/* Check if a light can be in box at index i
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: true if a light can be in box at index i
 */
bool lampe_possible(int i, Grid *grille);

/* Disp the grid to help debug
 * Condition of use : Empty
 * Result: Void
 */
void dispGrid(Grid *grid);

/* Write the grid in the file called fileName
 * Condition of use : Empty
 * Result: Void
 */
void writeGrid(char *fileName,Grid *grid);

/* Parse a grid in the file called fileName
 * Condition of use : fileName can be open.
 * Result: The grid in fileName
 */
Grid *readGrid(char *fileName);

/* Check if there is a wall in the box at index i
 * Condition of use : grid is a non null pointer (ERROR not handled)
 * Result: true if there is a wall in the box at index i
 */
bool isWall(Grid *grille, int index);

/* Initialize a grid with default value
 * Condition of use : Empty
 * Result: A grid with default value
 */
Grid *newGrid(int size);

#endif // INF432_GENERATION_H
