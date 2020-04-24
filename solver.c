//
// Created by fabie on 14/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
    int *occ = (int *)malloc(sizeof(int) * size);
    int *sos = (int *)malloc(sizeof(int) * size);
    e->occurence = occ;
    e->sumSize = sos;
    for(int i = 0; i<size;i++){
        e->occurence[i] = 0;
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

bool belongClause(Clause *c,variable x){
    CellLiteral *curr = c->tete;
    while(curr!=NULL){
        if(curr->x.x == x ) return true;
        curr = curr->suivant;
    }
    return false;
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

enumCNF *countCNF(CNF *cnf,Clause *clause,int maxSize){
    enumCNF *res = initEnumCNF(cnf->nbVar);
    CellClause *currClause;
    if(cnf==NULL) return NULL;
    currClause = cnf->tete;
    CellLiteral *currLit;
    int occInClause;
    while(currClause != NULL){
        currLit = clause->tete;
        while(currLit != NULL){
            if( belongClause(currClause->c,(variable)currLit->x.x ) && ( maxSize < 0 || currClause->c->taille < maxSize) ){
                res->occurence[currLit->x.x-1] ++;
                res->sumSize[currLit->x.x-1] += currClause->c->taille;
                res->totalSum += currClause->c->taille;
            }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
    currLit = clause->tete;
    while(currLit != NULL){
        occInClause = countClause(clause,currLit->x.x);
        printf("I");
        res->totalSum -= res->occurence[currLit->x.x-1]*(occInClause-1);
        res->sumSize[currLit->x.x-1] = res->sumSize[currLit->x.x-1]/occInClause;
        res->occurence[currLit->x.x-1] = res->occurence[currLit->x.x-1] /occInClause;
        currLit = currLit->suivant;
    }
    printf("\n");
    return res;
}


//JW
variable chooseVariableJW(CNF *tosolve, Clause *clause){
    enumCNF *enumeration = countCNF(tosolve, clause,-1);
    float actualProp = 0;
    float pick = (float) enumeration->totalSum/(float)(rand()%enumeration->totalSum);
    afficherClause(clause);
    printf("Pick : %f\n",pick);
    dispEnumCNF(enumeration);
    for(int i = 0; i < enumeration->size; i++){
        actualProp += (float) enumeration->sumSize[i];
        if (actualProp !=0 && pick > (float)enumeration->totalSum / actualProp){
            printf("Chosen : %d\n",i+1);
            return (variable) i+1;
        }
    }
    printf("Error no variable choose in JW heuristics\n");
    exit(1);
}

variable chooseVariableMOMS(CNF *tosolve, Clause *clause){
    enumCNF *enumeration = countCNF(tosolve, clause,2);
    afficherClause(clause);
    dispEnumCNF(enumeration);
    int max = 0;
    variable moms = 0;
    for(int i=0; i<enumeration->size; i++){
        if(enumeration->occurence[i] > max) {
            moms = i;
            max = enumeration->occurence[i];
        }
    }
    printf("Chosen : %d\n",moms+1);
    return moms+1;
}

variable chooseVariableScore(CNF *tosolve, Clause *clause){
    int *score = (int *)malloc(sizeof(int) * tosolve->nbVar);
    for(int i=0;i<tosolve->nbVar;i++){
        score[i]=0;
    }
    CellClause *currClause;
    currClause = tosolve->tete;
    CellLiteral *currLit;
    int occInClause;
    while(currClause != NULL){
        currLit = clause->tete;
        while(currLit != NULL){
            if(belongClause(currClause->c,(variable)currLit->x.x )){
                switch( signInClause(currClause->c,(variable)currLit->x.x )){
                    case PLUS:
                        score[currLit->x.x-1] += (int)currClause->c->taille;
                        break;
                    case MINUS:
                        score[currLit->x.x-1] -= (int)currClause->c->taille;
                        break;
                }
            }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
    currLit = clause->tete;
    while(currLit != NULL){
        occInClause = countClause(clause,currLit->x.x);
        printf("I");
        score[currLit->x.x-1] = score[currLit->x.x-1]/occInClause;
        currLit = currLit->suivant;
    }
    printf("\n");
    afficherClause(clause);
    int max = score[0];
    variable chosen = 0;
    printf("- %d -\n",score[0]);
    for(int i=1;i<tosolve->nbVar;i++){
        printf("- %d -\n",score[i]);
        if ( (max <= 0 && score[i] < max) || (max>=0 && score[i] > max)){
            max =score[i];
            chosen = i;
        }
    }
    printf("Chosen : %d\n", chosen+1);
    return (variable) chosen+1;
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
        printf(" { %d : occurence : %d ,sum of size of clause : %d } \n", i+1, countCNF->occurence[i], countCNF->sumSize[i]);
    }
    printf("Total sum : %d\n",countCNF->totalSum);
}

Assignation *WalkSat(CNF *toSolve){
    int i = 0, N = 10000;
    double q, P = 0.5;
    Clause *unsatisfied;
    variable toFlip;
    Assignation *v = newRandomAssignation(toSolve->nbVar);
    while(!isModelCNF(toSolve,v) && i < N){
        q = (float)rand()/(float)(RAND_MAX);
        unsatisfied = unsatisfiedClause(toSolve,v);
        printf("%d\n",i);
        if (q < P){
            toFlip = drawVariable(unsatisfied);
        }else{
            toFlip = chooseVariableScore(toSolve, unsatisfied);
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