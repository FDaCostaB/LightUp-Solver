//
// Created by fabie on 04/04/2020.
//

#ifndef INF432_GRID_H
#define INF432_GRID_H

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

typedef struct Grid {
    Box *tab;
    int taille;
} Grid;

typedef struct point {
    int x,y;
} point;

struct CellulePoint{
    point p;
    struct CellulePoint *suivant;
};
typedef struct CellulePoint CellulePoint;

struct SequencePoint{
    CellulePoint *tete;
    unsigned int taille;
};
typedef struct SequencePoint SequencePoint;

void afficher (SequencePoint* seq);

void ajoute_queue(SequencePoint *l, point P);

CellulePoint* nouvelleCellule (void);

void detruireCellule (CellulePoint* cel);

void detruireSequenceCoor (SequencePoint* seq);

SequencePoint* enumSubRow(Grid* grille, point p);
SequencePoint* enumSubLine(Grid* grille, point p);

SequencePoint* enumAdj(int taille, point p);

#endif //INF432_GRID_H
