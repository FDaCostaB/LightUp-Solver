//
// Created by fabie on 23/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "solver.h"
#include "dimacs.h"

int main(int argc,char *argv[]){
    CNF *res;
    Assignation *model;
    // ouverture du fichier nom_f en lecture
    if(argc!=2){
        printf("Usage commande : ./main fichier.sat\n");
        return 1;
    }
    srand(time(NULL));

    res = readDimacs(argv[1]);
    model = WalkSat(res);

    if(model == NULL) printf("No model found");
    else dispAssignation(model);
    detruireCNF(res);
}
