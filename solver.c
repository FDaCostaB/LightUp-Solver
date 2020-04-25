//
// Created by fabie on 14/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "solver.h"
#include "logic.h"

Assignation *newRandomAssignation(int size) {
    int sign;
    Assignation *v = (Assignation *)malloc(sizeof(Assignation));
    Literal *tab = (Literal *)malloc(sizeof(Literal) * size);
    v->tab = tab;
    v->size = size;
    for(int i =1; i<=size;i++){
        sign = rand() % 2;
        switch (sign){
            case 0:
                v->tab[i-1] = (Literal) {i,MINUS};
                break;
            case 1:
                v->tab[i-1] = (Literal) {i,PLUS};
                break;
        }
    }
    return v;
}

enumCNF *initEnumCNF(int size){
    enumCNF *e = (enumCNF *)malloc(sizeof(enumCNF));
    int *val = (int *)malloc(sizeof(int) * size);
    float *sos = (float *)malloc(sizeof(float) * size);
    e->valueComputed = val;
    e->sumSize = sos;
    for(int i = 0; i<size;i++){
        e->valueComputed[i] = 0;
        e->sumSize[i] = 0;
    }
    e->size = size;
    e->totalSum = 0;
    return e;
}

bool isModelClause(Clause *toSatisfy,Assignation *v){
    CellLiteral *curr = toSatisfy->tete;
    bool clauseEvaluation = false;
    while(curr!=NULL && !clauseEvaluation){
        clauseEvaluation = (curr->x.sign == v->tab[curr->x.x -1].sign);
        curr = curr->suivant;
    }
    return clauseEvaluation;
}

bool isModelCNF(CNF *toSolve,Assignation *v){
    CellClause *curr = toSolve->tete;
    bool clauseEvaluation = true;
    while(curr!=NULL && clauseEvaluation){
        clauseEvaluation = isModelClause(curr->c,v);
        curr = curr ->suivant;
    }
    return clauseEvaluation;
}

Clause *unsatisfiedClause(CNF *toSolve, Assignation *v){
    CellClause *curr = toSolve->tete;
    while(curr!=NULL && isModelClause(curr->c,v)){
        curr = curr ->suivant;
    }
    if (curr==NULL) return NULL;
    return curr->c;
}

variable drawVariable(Clause *c){
    CellLiteral *curr = c->tete;
    int val = rand() % (c->taille);
    while(curr!=NULL && val>0) {
        curr = curr->suivant;
        val--;
    }
    //if (curr==NULL) NE DEVRAIT JAMAIS ARRIVER
    return curr->x.x;
}

Sign signInClause(Clause *c,variable x){
    CellLiteral *curr = c->tete;
    while(curr!=NULL){
        if(curr->x.x == x ) return curr->x.sign;
        curr = curr->suivant;
    }
    printf("SignInClause : Error variable not found in clause");
    exit(1);
}

int countClause(Clause *c,variable x){
    CellLiteral *curr = c->tete;
    int count = 0;
    while(curr!=NULL){
        if(curr->x.x == x ) count++;
        curr = curr->suivant;
    }
    return count;
}

enumCNF *countCNF(CNF *cnf,int maxSize){ //valueComputed = occurence
    enumCNF *res = initEnumCNF(cnf->nbVar);
    CellClause *currClause;
    if(cnf==NULL) return NULL;
    currClause = cnf->tete;
    CellLiteral *currLit;
    int occInClause;
    int toSub;
    while(currClause != NULL) {
        currLit = currClause->c->tete;
        while(currLit != NULL) {
            if (maxSize < 0 || currClause->c->taille <= maxSize) {
                occInClause = countClause(currClause->c,currLit->x.x);
                res->valueComputed[currLit->x.x - 1] ++;
                res->sumSize[currLit->x.x - 1] += currClause->c->taille /occInClause ;
                res->totalSum += currClause->c->taille;
            }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
    printf("\n");
    return res;
}

enumCNF *scoreLitCNF(CNF *cnf){ // ValueComputed = score
    enumCNF *res = initEnumCNF(cnf->nbVar);
    CellClause *currClause;
    currClause = cnf->tete;
    CellLiteral *currLit;
    while(currClause != NULL){
        currLit = currClause->c->tete;
        while (currLit != NULL) {
            switch( signInClause(currClause->c,(variable)currLit->x.x )){
                case PLUS:
                    res->valueComputed[currLit->x.x-1] += currClause->c->taille;
                    break;
                case MINUS:
                    res->valueComputed[currLit->x.x-1] -= currClause->c->taille ;
                    break;
                }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
    return res;
}


//JW
variable chooseVariableJW(CNF *tosolve, Clause *clause, enumCNF *enumeration){ //valueComputed = occurence
    float actualProp = 0;
    CellLiteral *currLit = clause->tete;
    int totalClauseSum = 0;
    while(currLit != NULL){
        totalClauseSum += enumeration->sumSize[currLit->x.x-1];
        currLit = currLit->suivant;
    }
    printf("Sum : %d\n",totalClauseSum);
    float pick = (float) totalClauseSum / (float) (rand()%totalClauseSum);
    afficherClause(clause);
    printf("Pick : %f\n",pick);
    dispEnumCNF(enumeration);
    currLit = clause->tete;
    while(currLit != NULL){
        actualProp += (float) enumeration->sumSize[currLit->x.x-1];
        printf("actualProp : %d / %.1f\n",totalClauseSum,actualProp);
        if (actualProp !=0 && pick > (float) totalClauseSum / actualProp){
            printf("Chosen : %d\n",currLit->x.x);
            return (variable) currLit->x.x;
        }
        currLit = currLit->suivant;
    }
    printf("Error no variable choose in JW heuristics\n");
    exit(1);
}

variable chooseVariableMOMS(CNF *tosolve, Clause *clause, enumCNF *enumeration){ //valueComputed = occurence
    afficherClause(clause);
    dispEnumCNF(enumeration);
    CellLiteral *currLit = clause->tete;
    int max = 0;
    variable moms = 0;
    currLit = clause->tete;
    while(currLit != NULL){
        if(enumeration->valueComputed[currLit->x.x - 1] > max) {
            moms = currLit->x.x;
            max = enumeration->valueComputed[currLit->x.x - 1];
        }
        currLit = currLit->suivant;
    }
    printf("Chosen : %d\n",moms);
    return moms;
}

variable chooseVariableScore(CNF *tosolve, Clause *clause, enumCNF * enumeration){ // ValueComputed = score
    afficherClause(clause);
    dispEnumCNF(enumeration);
    float max = enumeration->valueComputed[clause->tete->x.x-1];
    variable chosen = clause->tete->x.x;
    CellLiteral *currLit = clause->tete->suivant;
    while(currLit != NULL){
        if ( (max <= 0 && (int)enumeration->valueComputed[currLit->x.x - 1] < (int)max) || (max>=0 && (int)enumeration->valueComputed[currLit->x.x - 1] > (int)max)){
            max = enumeration->valueComputed[currLit->x.x - 1];
            chosen = currLit->x.x;
        }
        currLit = currLit->suivant;
    }
    printf("Chosen : %d\n", chosen);
    return (variable) chosen;
}

void flipInAssignation(int val,Assignation *v){
    switch (v->tab[val-1].sign){
        case PLUS:
            v->tab[val-1].sign=MINUS;
            break;
        case MINUS:
            v->tab[val-1].sign=PLUS;
            break;
    }
}

void dispAssignation(Assignation *model){
    printf("\n");
    for(int i=0; i<model->size;i++){
        afficherLit(model->tab[i]);
    }
    printf("\n");
}

void dispEnumCNF(enumCNF *countCNF){
    printf("\n");
    for(int i=0; i<countCNF->size;i++){
        printf(" { %d : valueComputed : %d ,sum of size of clause : %.1f } \n", i+1, countCNF->valueComputed[i], countCNF->sumSize[i]);
    }
    printf("Total sum : %.d\n",countCNF->totalSum);
}

Assignation *WalkSat(CNF *toSolve){
    int i = 0, N = 10000;
    double q, P = 0.1;
    Clause *unsatisfied;
    variable toFlip;
    Assignation *v = newRandomAssignation(toSolve->nbVar);
    enumCNF *enumeration = countCNF(toSolve,-1); // JW => maxSize = -1 // MOMS => maxSize = 2
    //enumCNF *enumeration = scoreLitCNF(toSolve);
    afficherCNF(toSolve);
    while(!isModelCNF(toSolve,v) && i < N){
        q = (float)rand()/(float)(RAND_MAX);
        unsatisfied = unsatisfiedClause(toSolve,v);
        printf("%d\n",i);
        if (q < P){
            toFlip = drawVariable(unsatisfied);
        }else{
            toFlip = chooseVariableJW(toSolve, unsatisfied, enumeration);
        }
        flipInAssignation(toFlip,v);
        i++;
    }
    if(isModelCNF(toSolve,v)){
        return v;
    }else{
        return NULL;
    }
}