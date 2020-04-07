//
// Created by fabie on 05/04/2020.
//

#include "logic.h"
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

void KchosenInClauseRec(int k, int taille, int startIndex, CellLiteral *act, Clause *inConstruction,CNF *res){
    if (taille<k) return;
    if(k==1){
        while(act != NULL){
            Clause *toAddCNF = CopyClause(inConstruction);
            addToClause(toAddCNF,act->x,false);
            //afficherClause(toAddCNF);
            addToCNF(res,toAddCNF);
            act = act->suivant;
        }
        detruireClause(inConstruction);
    }else {
        Clause *Save = CopyClause(inConstruction);
        for(int n=startIndex; n <= taille - k; n++){
            addToClause(Save,act->x,false);
            //afficherClause(Save);
            KchosenInClauseRec(k-1,taille,n+1,act->suivant, Save, res);
            Save = CopyClause(inConstruction);
            act = act->suivant;
        }
        detruireClause(Save);
        detruireClause(inConstruction);
    }
}

CNF* KChosenInClause(int k, Clause *c){
    CNF *res = newCNF();
    res->nbVar = c->taille;
    Clause *start = newClause();
    KchosenInClauseRec(k,c->taille,0,c->tete,start,res);
    //detruireClause(start);
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
        detruireClause(inConstruction);
    }else {
        Clause *Save = CopyClause(inConstruction);
        for(int n=startIndex; n <= taille - k; n++){
            addToClause(Save,act->x,true);
            KneglectedInClauseRec(k-1,taille,n+1,act->suivant, Save, res);
            addToClause(inConstruction,act->x,false);
            Save = CopyClause(inConstruction);
            act = act->suivant;
        }
        detruireClause(Save);
        detruireClause(inConstruction);
    }
}

CNF* KneglectedInClause(int k, Clause *c){
    CNF *res = newCNF();
    res->nbVar = c->taille;
    Clause *start = newClause();
    KneglectedInClauseRec(k,c->taille,0,c->tete,start,res);
    return res;
}