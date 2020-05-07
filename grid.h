//
// Created by fabie on 04/04/2020.
//

#ifndef INF432_GRID_H
#define INF432_GRID_H

/* A representation of box */
typedef enum {
    INCONNU,
    LIBRE,
    MURV,
    MUR0,
    MUR1,
    MUR2,
    MUR3,
    MUR4,
    LAMPE,
    VIDE
} Box;

/* A representation of grid as one dimensions table */
typedef struct Grid {
    Box *tab;
    int taille;
} Grid;

/* A representation of coordinate in 2 dimensions  */
typedef struct point {
    int x,y;
} point;

/* A cell containig a point to create a linked list */
struct CellulePoint{
    point p;
    struct CellulePoint *suivant;
};
typedef struct CellulePoint CellulePoint;

/* A linked list of point */
struct SequencePoint{
    CellulePoint *tete;
    unsigned int taille;
};
typedef struct SequencePoint SequencePoint;

/* Disp a list of point to help debug
 * Condition of use : Empty
 * Result: Void
 */
void afficher (SequencePoint* seq);

/* Add a point at the end of the linked list
 * Condition of use : Empty
 * Result: Sequence l include P at the end
 */
void ajoute_queue(SequencePoint *l, point P);

/* New CellulePoint initialize with default value
 * Condition of use : Empty
 * Result: Fresh CellulePoint
 */
CellulePoint* nouvelleCellule (void);

/* Free cel
 * Condition of use : cel is a non null pointer (ERROR not handled)
 * Result: Void
 */
void detruireCellule (CellulePoint* cel);

/* Free grille and his components
 * Condition of use : cel is a non null pointer (ERROR not handled)
 * Result: Void
 */
void detruireGrid (Grid *grille);

/* New SequencePoint initialize with default value
 * Condition of use : Empty
 * Result: Fresh SequencePoint
 */
SequencePoint * nouvelleSequencePoint (void);

/* Free seq
 * Condition of use : seq is a non null pointer (ERROR not handled)
 * Result: Void
 */
void detruireSequencePoint (SequencePoint* seq);

// We use clause instead this type is obsolete now
/*SequencePoint* enumSubRow(Grid* grille, point p);
SequencePoint* enumSubLine(Grid* grille, point p);
SequencePoint* enumAdj(int taille, point p);*/

#endif //INF432_GRID_H
