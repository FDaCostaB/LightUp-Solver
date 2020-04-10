//
// Created by fabie on 05/04/2020.
//

#include "logic.h"
#include "grid.h"
#include "generation.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void addToClause(Clause *C, Literal x, bool neglect) {
    CellLiteral *curr;
    CellLiteral *new;
    new = newLiterral();
    if (neglect) {
        switch (x.sign){
            case PLUS:
                new->x.sign = MINUS;
                break;
            case MINUS :
                new->x.sign = PLUS;
                break;
        }
    } else{
        new->x.sign = x.sign;
    }
    new->x.x = x.x;
    if (C->tete==NULL) {
        C->tete=new;
        C->taille=1;
    }
    else {
        curr = C->tete;
        while (curr->suivant!=NULL) {
            curr = curr->suivant;

        }
        curr->suivant = new;
        C->taille = C->taille +1;
    }
    return;
}

void afficherLit (Literal l){
    switch (l.sign){
        case PLUS:
            printf(" +%d ",l.x);
            break;
        case MINUS:
            printf(" -%d ",l.x);
            break;
    }
}

void afficherClause (Clause* seq){
    CellLiteral *curr;
    if(seq==NULL) return;
    curr = seq->tete;
    printf("[ ");
    while(curr != NULL){
        if(curr->suivant != NULL){
            afficherLit(curr->x);
            printf(",");
        }
        else afficherLit(curr->x);
        curr = curr->suivant;
    }
    printf(" ]\n");
}

void afficherCNF (CNF* seq){
    CellClause *curr;
    if(seq==NULL) return;
    curr = seq->tete;
    printf("{ ");
    while(curr != NULL){
        afficherClause(curr->c);
        curr = curr->suivant;
    }
    printf(" }\n");
}

CellLiteral* newLiterral (void) {
    CellLiteral *cel =(CellLiteral*)malloc(sizeof(CellLiteral));
    cel->suivant = NULL;
    return cel;
}

void detruireCellLit (CellLiteral* cel){
    free(cel);
}

Clause * newClause (void) {
    Clause * seq = (Clause*)malloc(sizeof(Clause));
    seq->taille=0;
    seq->tete=NULL;
    return seq;
}

CellClause *newCellClause(){
    CellClause * cell = (CellClause*)malloc(sizeof(CellClause));
    cell->suivant = NULL;
    return cell;
}

void detruireClause (Clause* seq) {
    CellLiteral *curr = seq->tete;
    CellLiteral *aSuppr;
    while(curr != NULL){
        aSuppr = curr;
        curr = curr->suivant;
        detruireCellLit(aSuppr);
    }
    seq->tete=NULL;
    seq->taille=0;
    free(seq);
}

void delLastClause(struct Clause* seq){
    CellLiteral *curr = seq->tete;
    CellLiteral *aSuppr;
    while(curr->suivant->suivant != NULL){
        curr = curr->suivant;
    }
    aSuppr = curr->suivant;
    curr->suivant = NULL;
    detruireCellLit(aSuppr);
}

Clause *CopyClause(Clause *source){
    CellLiteral *curr = source->tete;
    Clause *Copy = newClause();
    Copy->taille = source->taille;
    while(curr != NULL){
        addToClause(Copy,curr->x,false);
        curr=curr->suivant;
    }
    return Copy;
}

void concatClause(Clause *c1, Clause *c2 ){
    CellLiteral *curr;
    if (c1->tete==NULL) {
        c1->tete=c2->tete;
        c1->taille=c2->taille;
    }
    else {
        curr = c1->tete;
        while (curr->suivant!=NULL) {
            curr = curr->suivant;
        }
        curr->suivant = c2->tete;
        c1->taille += c2->taille;
    }
    free(c2);
    return;
}

CNF *newCNF(){
    CNF *res = (CNF *) malloc(sizeof(CNF));
    res->taille=0;
    res->nbVar=0;
    res->tete=NULL;
    return res;
}

void addToCNF(CNF *Cnf, Clause *C ){
    CellClause *curr;
    CellClause *new = newCellClause();
    new->c = C;
    if (Cnf->tete==NULL) {
        Cnf->tete=new;
        Cnf->taille=1;
    }
    else {
        curr = Cnf->tete;
        while (curr->suivant!=NULL) {
            curr = curr->suivant;

        }
        curr->suivant = new;
        Cnf->taille = Cnf->taille +1;
    }
    return;
}

void concatCNF(CNF *cnf1, CNF *cnf2 ){
    CellClause *curr;
    if (cnf1->tete==NULL) {
        cnf1->tete=cnf2->tete;
        cnf1->taille=cnf2->taille;
    }
    else {
        curr = cnf1->tete;
        while (curr->suivant!=NULL) {
            curr = curr->suivant;

        }
        curr->suivant = cnf2->tete;
        cnf1->taille += cnf2->taille;
    }
    free(cnf2);
    return;
}

void detruireCNF (CNF* seq) {
    CellClause *curr = seq->tete;
    CellClause *aSuppr;
    while(curr != NULL){
        aSuppr = curr;
        curr = curr->suivant;
        detruireClause(aSuppr->c);
        free(aSuppr);
    }
    free(seq);
}

void KchosenInClauseRec(int k, int taille, int startIndex, CellLiteral *act, Clause *inConstruction,CNF *res, bool doNeglect){
    if (taille<k) return;
    if(k==1){
        while(act != NULL){
            Clause *toAddCNF = CopyClause(inConstruction);
            addToClause(toAddCNF,act->x,doNeglect);
            addToCNF(res,toAddCNF);
            act = act->suivant;
        }
        if(startIndex != 0) detruireClause(inConstruction);
    }else {
        Clause *Save = CopyClause(inConstruction);
        for(int n=startIndex; n <= taille - k; n++){
            addToClause(Save,act->x,doNeglect);
            KchosenInClauseRec(k-1,taille,n+1,act->suivant, Save, res,doNeglect);
            Save = CopyClause(inConstruction);
            act = act->suivant;
        }
        detruireClause(Save);
        if(startIndex != 0) detruireClause(inConstruction);
    }
}

CNF* KChosenInClause(int k, Clause *c, bool doNeglect){
    CNF *res = newCNF();
    res->nbVar = c->taille;
    Clause *start = newClause();
    KchosenInClauseRec(k,c->taille,0,c->tete,start,res, doNeglect);
    detruireClause(start);
    return res;
}

void KneglectedInClauseRec(int k, int taille, int startIndex, CellLiteral *act, Clause *inConstruction,CNF *res){
    if (taille<k) return;
    if(k==1){
        CellLiteral *curr;
        while(act != NULL){
            Clause *toAddCNF = CopyClause(inConstruction);
            addToClause(toAddCNF,act->x,true);
            addToCNF(res,toAddCNF);
            addToClause(inConstruction,act->x,false);
            act = act->suivant;
            curr = act;
            while(curr !=NULL){
                addToClause(toAddCNF,curr->x,false);
                curr = curr->suivant;
            }
        }
        if(startIndex != 0) detruireClause(inConstruction);
    }else {
        Clause *Save = CopyClause(inConstruction);
        for(int n=startIndex; n <= taille - k; n++){
            addToClause(Save,act->x,true);
            KneglectedInClauseRec(k-1,taille,n+1,act->suivant, Save, res);
            //delLastClause(inConstruction);
            addToClause(inConstruction,act->x,false);
            Save = CopyClause(inConstruction);
            act = act->suivant;
        }
        detruireClause(Save);
        if(startIndex != 0)detruireClause(inConstruction);
    }
}

CNF* KneglectedInClause(int k, Clause *c){
    CNF *res = newCNF();
    if(k==0){
        addToCNF(res,c);
        return res;
    }
    res->nbVar = c->taille;
    Clause *start = newClause();
    KneglectedInClauseRec(k,c->taille,0,c->tete,start,res);
    detruireClause(start);
    return res;
}

Clause* enumSubRow(Grid* grid, int i){
    Clause *res=newClause();
    Literal index ; index.sign = PLUS;
    bool stopAbove = false, stopBellow = false;
    point p = (point) { i%grid->taille , i/grid->taille};
    //printf(" (%d, %d)\n",p.x,p.y);
    if (p.x >= grid->taille || p.y >= grid->taille || p.x < 0 || p.y < 0) return res;
    index.x = i;
    addToClause(res,index,false);
    for(int j = 1;j<grid->taille || (!stopAbove && !stopBellow);j++){
        if(isWall(grid, p.x + (p.y-j) * grid->taille) || (p.y - j) < 0){
            stopAbove = true;
        }
        if(isWall(grid, p.x + (p.y+j) * grid->taille) || (p.y + j) < 0){
            stopBellow = true;
        }
        if(!stopAbove){
            index.x = p.x + (p.y - j) * grid->taille;
            addToClause(res,index,false);
        }
        if(!stopBellow){
            index.x = p.x + (p.y + j) * grid->taille;
            addToClause(res,index,false);
        }
    }
    //printf("Fin enumSubRow.\n");
    return  res;
}

Clause* enumSubLine(Grid* grid, int i) {
    Clause *res=newClause();
    Literal index ; index.sign = PLUS;
    bool stopLeft = false,stopRight = false;
    point p = (point) { i%grid->taille , i/grid->taille};
    //printf(" (%d, %d)\n",p.x,p.y);
    if (p.x >= grid->taille || p.y >= grid->taille || p.x < 0 || p.y < 0) return res;
    for(int j = 0; j<grid->taille || (!stopLeft && !stopRight); j++){
        if(isWall(grid, (p.x-j) + p.y * grid->taille) || (p.x - j) < 0 ){
            stopLeft = true;
        }
        if(isWall(grid, (p.x+j) + p.y * grid->taille) || (p.x + j) > (p.x+j)%grid->taille){
            stopRight = true;
        }
        if(j==0){
            index.x = (p.x-j) + p.y * grid->taille;
            addToClause(res,index,false);
        }else{
            if(!stopLeft){
                index.x = (p.x-j) + p.y * grid->taille;
                addToClause(res,index,false);
            }
            if(!stopRight){
                index.x = (p.x+j) + p.y * grid->taille;
                addToClause(res,index,false);
            }
        }
    }
    //printf("Fin enumSubLine.\n");
    return  res;
}

Clause* enumAdj(int taille, int i){
    Clause *res=newClause();
    Literal index ; index.sign = PLUS;
    point p = (point) { i%taille , i/taille};
    if (p.x >= taille || p.y >= taille || p.x < 0 || p.y < 0) return res;
    if ( (p.y - 1) >= 0){
        index.x = p.x + (p.y-1) * taille;
        addToClause(res,index,false);
    }
    if ((p.x  - 1) >=0 ){
        index.x = (p.x-1) + p.y * taille;
        addToClause(res,index,false);
    }
    if ((p.x + 1)  < taille){
        index.x = (p.x+1) + p.y * taille;
        addToClause(res,index,false);
    }
    if ((p.y + 1) < taille ){
        index.x = p.x + (p.y+1) * taille;
        addToClause(res,index,false);
    }
    return  res;
}

//Les cases sont des murs ou des cases libres ( la grille n'est pas résolu )
CNF* cnfOfBox(Grid *grid, int i){
    CNF *res = newCNF();
    Clause * toAdd;
    CNF *concat;
    if( /*i>=0 && i < (grid->taille * grid->taille) && */isWall(grid,i)){
        int numWall=-1;
        toAdd = newClause();
        Literal l = (Literal){ i, MINUS};
        addToClause(toAdd,l,false);
        addToCNF(res, toAdd);
        Clause *adj = enumAdj(grid->taille, i);
        //afficherClause(adj);
        switch (grid->tab[i]) {
            case MUR0 :
                numWall = 0;
                break;
            case MUR1 :
                numWall = 1;
                break;
            case MUR2 :
                numWall = 2;
                break;
            case MUR3 :
                numWall = 3;
                break;
            case MUR4 :
                numWall = 4;
                break;
            default:
                break;
        }
        if(numWall != 0 && numWall - adj->taille !=0 && numWall !=-1){
            for(int i=0;i<=adj->taille;i++){
                if(i!=numWall){
                    concat = KneglectedInClause(i,adj);
                    concatCNF(res,concat);
                }
            }
        }else if (numWall != -1){
            CellLiteral *curr = adj->tete;
            while(curr != NULL){
                toAdd = newClause();
                addToClause(toAdd,curr->x,numWall==0);
                addToCNF(res,toAdd);
                curr = curr->suivant;
            }
        }

    } else {
        Clause *temp;
        toAdd = enumSubRow(grid, i);
        //addToCNF(res,toAdd);
        concat = KChosenInClause(2,toAdd,true);
        concatCNF(res,concat);

        temp = toAdd;

        toAdd = enumSubLine(grid, i);
        //addToCNF(res,toAdd);
        concat = KChosenInClause(2,toAdd,true);
        concatCNF(res,concat);

        //afficherClause(toAdd);
        //afficherClause(temp);
        concatClause(toAdd,temp);
        addToCNF(res,toAdd);
        //afficherClause(toAdd);
    }
    return res;
}