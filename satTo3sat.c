//
// Created by fabie on 11/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "logic.h"
#include "dimacs.h"

int main(int argc, char *argv[]) {
    if(argc!=3){
        printf("Usage commande : ./main source.cnf res.cnf\n");
        return 1;
    }

    CNF *toReduct,*temp;
    CNF *res=newCNF();

    toReduct = readDimacs(argv[1]);
    res->nbVar = toReduct->nbVar;
    CellClause *curr = toReduct->tete;
    while(curr!=NULL){
        temp = SATto3SAT(curr->c,&(res->nbVar));
        concatCNF(res,temp);
        curr = curr->suivant;
    }
    writeDimacs(argv[2],res,0);

    detruireCNF(res);
    return 0;
}