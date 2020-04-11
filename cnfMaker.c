//
// Created by fabie on 09/04/2020.
//

#include "generation.h"
#include "grid.h"
#include "logic.h"
#include "dimacs.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if(argc!=3){
        printf("Usage commande : ./main grille fichier.cnf\n");
        return 1;
    }
    CNF *res = newCNF();
    CNF *temp;

    Grid *grid = readGrid(argv[1]);
    dispGrid(grid);

    res->nbVar = (grid->taille) * (grid ->taille);

    for(int i = 0; i < (grid->taille * grid->taille); i++){
         temp = cnfOfBox(grid,i);
         //afficherCNF(temp);
         concatCNF(res,temp);
    }

    writeDimacs(argv[2], res,1);
    //afficherCNF(res);

    free(grid->tab);
    free(grid);
    detruireCNF(res);
}