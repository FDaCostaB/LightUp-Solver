//
// Created by fabie on 04/04/2020.
//

#include "grid.h"
#include "generation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void ajoute_queue(SequencePoint *S, point p) {
    CellulePoint *curr;
    CellulePoint *new;
    new = (CellulePoint *) malloc(sizeof(CellulePoint));
    new->p = p;
    new->suivant=NULL;
    if (S->tete==NULL) {
        S->tete=new;
        S->taille=1;
    }
    else {
        curr = S->tete;
        while (curr->suivant!=NULL) {
            curr = curr->suivant;

        }
        curr->suivant = new;
        S->taille=S->taille +1;
    }
    return;
}

void afficher (SequencePoint* seq){
    CellulePoint *curr;
    if(seq==NULL) return;
    curr = seq->tete;
    printf("[ ");
    while(curr != NULL){
        if(curr->suivant != NULL)printf("(%d, %d) ,", curr->p.x, curr->p.y);
        else printf("(%d, %d)", curr->p.x, curr->p.y);
        curr = curr->suivant;
    }
    printf(" ]\n");

}

CellulePoint* nouvelleCellule (void){
    CellulePoint *cel =(CellulePoint*)malloc(sizeof(CellulePoint));
    cel->suivant = NULL;
    return cel;
}


void detruireCellule (CellulePoint* cel){
    free(cel);
}

void detruireGrid (Grid *grille){
    free(grille->tab);
    free(grille);
}
SequencePoint * nouvelleSequencePoint (void){
    SequencePoint * seq = (SequencePoint*)malloc(sizeof(SequencePoint));
    seq->taille=0;
    seq->tete=NULL;
    return seq;
}

void detruireSequencePoint(SequencePoint* seq){
    CellulePoint *curr = seq->tete;
    CellulePoint *aSuppr;
    while(curr != NULL){
        aSuppr = curr;
        curr = curr->suivant;
        detruireCellule(aSuppr);
    }
    seq->tete=NULL;
    seq->taille=0;
    free(seq);
}

//Refactor in logic package to return a clause
/*SequencePoint* enumSubRow(Grid* grid, point p){
    SequencePoint *res=nouvelleSequencePoint();
    point compt;
    bool stopAbove = false, stopBellow = false;
    if (p.x >= grid->taille || p.y >= grid->taille || p.x < 0 || p.y < 0) return res;
    for(int j = 0;j<grid->taille || (stopAbove && stopBellow);j++){
        if(isWall(grid, p.x + (p.y-j) * grid->taille)){
            stopAbove = true;
        }
        if(isWall(grid, p.x + (p.y+j) * grid->taille)){
            stopBellow = true;
        }
        if(!stopAbove){
            compt = (point) {p.x, p.y - j};
            ajoute_queue(res,compt);
        }
        if(!stopBellow){
            compt = (point) {p.x, p.y + j};
            ajoute_queue(res,compt);
        }
    }
    return  res;
}

SequencePoint* enumSubLine(Grid* grid, point p) {
    SequencePoint *res=nouvelleSequencePoint();
    point compt;
    bool stopLeft = false,stopRight = false;

    if (p.x >= grid->taille || p.y >= grid->taille || p.x < 0 || p.y < 0) return res;
    for(int j = 0; j<grid->taille || (stopLeft && stopRight); j++){
        if(isWall(grid, (p.x-j) + p.y * grid->taille)){
            stopLeft = true;
        }
        if(isWall(grid, (p.x+j) + p.y * grid->taille)){
            stopRight = true;
        }
        if(!stopLeft){
            compt = (point) {p.x-j, p.y};
            ajoute_queue(res,compt);
        }
        if(!stopRight){
            compt = (point) {p.x+j, p.y};
            ajoute_queue(res,compt);
        }
    }
    return  res;
}

SequencePoint* enumAdj(int taille, point p){
    SequencePoint *res=nouvelleSequencePoint();
    point compt;
    if (p.x >= taille || p.y >= taille || p.x < 0 || p.y < 0) return res;
    if ( (p.y - 1) >= 0){
        compt = (point) {p.x, p.y-1};
        ajoute_queue(res,compt);
    }
    if ((p.x  - 1) >=0 ){
        compt = (point) {p.x -1, p.y};
        ajoute_queue(res,compt);
    }
    if ((p.x + 1)  < taille){
        compt = (point) {p.x +1, p.y};
        ajoute_queue(res,compt);
    }
    if ((p.y + 1) < taille ){
        compt = (point) {p.x, p.y+1};
        ajoute_queue(res,compt);
    }
    return  res;
}*/