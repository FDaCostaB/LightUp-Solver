//
// Created by fabie on 11/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "logic.h"
#include "dimacs.h"

int main(int argc, char *argv[]) {
    if(argc!=){
        printf("Usage commande : ./main source.cnf res.cnf\n");
        return 1;
    }

    FILE *f1 = fopen(argv[1], "r");
    CNF *res;
    if (f1 == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }
    res = readDimacs(f1);
    while(){

    }
    writeDimacs(argv[2],res3sat);

    fclose(f1);
    detruireCNF(res);
}