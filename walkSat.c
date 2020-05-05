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
    Assignation *model = NULL;
    unsigned int mode = 0;
    // ouverture du fichier nom_f en lecture

    if(argc!=4){
        printf("Usage commande : ./main mode file.cnf file.res\n");
        return 1;
    }

    srand(time(NULL));

    mode = (unsigned int) atoi(argv[1]);
    res = readDimacs(argv[2]);
    model = WalkSat(res,mode);

    writeAssignation(argv[3],model);
    detruireCNF(res);
    if(model!=NULL) freeAssignation(model);
}