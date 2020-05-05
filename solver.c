//
// Created by fabie on 14/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "solver.h"
#include "logic.h"

Assignation *newRandomAssignation(unsigned int size) {
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
            default:
                break;
        }
    }
    return v;
}

enumCNF *initEnumCNF(unsigned int size){
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
    currClause = cnf->tete;
    CellLiteral *currLit;
    int occInClause;
    while(currClause != NULL) {
        currLit = currClause->c->tete;
        while(currLit != NULL) {
            if (maxSize < 0 || currClause->c->taille <= maxSize) {
                occInClause = countClause(currClause->c,currLit->x.x);
                res->valueComputed[currLit->x.x - 1] ++;
                res->sumSize[currLit->x.x - 1] += (float)currClause->c->taille / (float) occInClause ;
                res->totalSum += (int) currClause->c->taille;
            }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
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
                    res->valueComputed[currLit->x.x-1] ++;
                    break;
                case MINUS:
                    res->valueComputed[currLit->x.x-1] -- ;
                    break;
                }
            currLit = currLit->suivant;
        }
        currClause = currClause->suivant;
    }
    return res;
}

variable chooseVariableJW(Clause *clause, enumCNF *enumeration){ //valueComputed = occurence
    float actualProp = 0;
    CellLiteral *currLit = clause->tete;
    float clauseInverseSum = 0;
    int sum = 0;
    while(currLit != NULL){
        sum += (int) enumeration->sumSize[currLit->x.x-1];
        currLit = currLit->suivant;
    }
    currLit = clause->tete;
    while(currLit != NULL){
        clauseInverseSum += (float) sum/enumeration->sumSize[currLit->x.x-1];
        currLit = currLit->suivant;
    }
    float pick = (( (float)rand()/(float)RAND_MAX ) * (float)(clauseInverseSum));
    //afficherClause(clause);
    //printf("Pick : %f \n", pick);
    //printf("Sum : %d Sum of inverse : %.1f\n",sum,clauseInverseSum);
    currLit = clause->tete;
    while(currLit != NULL){
        actualProp += (float) sum / enumeration->sumSize[currLit->x.x-1];
        //printf("actualProp : %.1f\n", actualProp);
        if (actualProp !=0 && pick <= (float) actualProp){
            //printf("Chosen : %d\n",currLit->x.x);
            return (variable) currLit->x.x;
        }
        currLit = currLit->suivant;
    }
    printf("ERROR : No variable choose in JW heuristics\n");
    exit(1);
}

variable chooseVariableMOMS(Clause *clause, enumCNF *enumeration){ //valueComputed = occurence
    CellLiteral *currLit;
    variable moms = 0;
    currLit = clause->tete;
    int max = enumeration->valueComputed[currLit->x.x - 1];
    moms = currLit->x.x;
    while(currLit != NULL){
        if(enumeration->valueComputed[currLit->x.x - 1] > max) {
            //printf(" %d : %d > %d :%d \n",currLit->x.x, enumeration->valueComputed[currLit->x.x - 1], moms, max);
            moms = currLit->x.x;
            max = enumeration->valueComputed[currLit->x.x - 1];
        }
        currLit = currLit->suivant;
    }
    return moms;
}

variable chooseVariableScore(Clause *clause, enumCNF * enumeration){ // ValueComputed = score
    int max = enumeration->valueComputed[clause->tete->x.x-1];
    variable chosen = clause->tete->x.x;
    CellLiteral *currLit = clause->tete->suivant;
    while(currLit != NULL){
        if ( (max <= 0 && enumeration->valueComputed[currLit->x.x - 1] < max) || (max <= 0 && enumeration->valueComputed[currLit->x.x - 1] > -1 * max) ||
        (max>=0 && enumeration->valueComputed[currLit->x.x - 1] > max) || (max>=0 && enumeration->valueComputed[currLit->x.x - 1] < -1 * max) ){
            max = enumeration->valueComputed[currLit->x.x - 1];
            chosen = currLit->x.x;
        }
        currLit = currLit->suivant;
    }
    return (variable) chosen;
}

variable chooseVariableModif(Clause *clause, unsigned int* modif){ // ValueComputed = score
    unsigned int min = modif[clause->tete->x.x-1];
    variable chosen = clause->tete->x.x;
    CellLiteral *currLit = clause->tete->suivant;
    while(currLit != NULL){
        if ( modif[currLit->x.x - 1] < min ){
            min = modif[currLit->x.x - 1];
            chosen = currLit->x.x;
        }
        currLit = currLit->suivant;
    }
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
    for(int i=0; i<model->size;i++){
        afficherLit(model->tab[i]);
    }
    printf("\n");
}

void writeAssignation(char *fileName, Assignation *model){
    FILE *f = fopen(fileName, "w");
    if (f == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }
    if(model == NULL){
        fprintf(f,"undef\n");
    } else {
        fprintf(f,"SAT\n");
        for(int i=0; i<model->size;i++){
            switch (model->tab[i].sign){
                case PLUS:
                    fprintf(f,"%d ",model->tab[i].x);
                    break;
                case MINUS:
                    fprintf(f,"-%d ",model->tab[i].x);
                    break;
            }
        }
        fprintf(f,"0\n");
    }
    fclose(f);
}

void dispEnumCNF(enumCNF *countCNF){
    printf("\n");
    for(int i=0; i<countCNF->size;i++){
        printf(" { %d : valueComputed : %d ,size of clause : %.1f } \n", i+1, countCNF->valueComputed[i], countCNF->sumSize[i]);
    }
    printf("Total sum : %.d\n",countCNF->totalSum);
}

void freeEnumCNF(enumCNF *enumeration){
    free(enumeration->valueComputed);
    free(enumeration->sumSize);
    free(enumeration);
}

void freeAssignation(Assignation *v){
    free(v->tab);
    free(v);
}

Assignation *WalkSat(CNF *toSolve, unsigned int mode){
    if(toSolve == NULL) {
        printf("WalkSat : Nothing to solve\n");
        exit(1);
    }

    int i = 0, N = 100000;
    double q, P = 0.1;

    Clause *unsatisfied;
    variable toFlip;
    Assignation *v = newRandomAssignation(toSolve->nbVar);
    enumCNF *enumeration;
    unsigned int *modifiedVar = NULL;
    switch ( mode ) {
        case 1 : //JW
            enumeration = countCNF(toSolve,-1);
            break;
        case 2 : //MOMS
            enumeration = countCNF(toSolve,2);
            break;
        case 3 : //score
            enumeration = scoreLitCNF(toSolve);
            break;
        case 4 : //LeastModified
            modifiedVar = (unsigned int *) malloc(toSolve->nbVar*sizeof(unsigned int) );
            for(int i =0; i<toSolve->nbVar; i++){
                modifiedVar[i]=0;
            }
            break;
        default:
            printf("WalkSat : No mode specified\n");
            exit(1);
    }
    //dispEnumCNF(enumeration);
    //afficherCNF(toSolve);
    while(!isModelCNF(toSolve,v) && i < N){
        q = (float)rand()/(float)(RAND_MAX);
        unsatisfied = unsatisfiedClause(toSolve,v);
        if (q <= P){
            toFlip = drawVariable(unsatisfied);
        }else{
            switch ( mode ) {
                case 1 : //JW
                    toFlip = chooseVariableJW(unsatisfied, enumeration);
                    break;
                case 2 : //MOMS
                    toFlip = chooseVariableMOMS(unsatisfied, enumeration);
                    break;
                case 3 : //score
                    toFlip = chooseVariableScore(unsatisfied, enumeration);
                    break;
                case 4 : //LeastModified
                    toFlip = chooseVariableModif(unsatisfied, modifiedVar);
                    break;
                default:
                    break;
            }
        }
        flipInAssignation(toFlip,v);
        if (mode == 4) modifiedVar[toFlip-1] ++;
        i++;
    }

    if( (int) mode>=1 && (int) mode<=3 ) freeEnumCNF(enumeration);
    else if (mode == 4) free(modifiedVar);

    if(isModelCNF(toSolve,v)){
        return v;
    }else{
        freeAssignation(v);
        return NULL;
    }
}