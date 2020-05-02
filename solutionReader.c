//
// Created by fabie on 10/04/2020.
//

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
    Clause *res ;

    if(argc!=3){
        printf("Usage commande : ./main grid.txt output.sat\n");
        return 1;
    }

    Grid *grid = readGrid(argv[1]);
    printf("--Solution of the grid --\n\n");

    res = readMinisatOut(argv[2]);
    if(res == NULL){
        free(grid->tab);
        free(grid);
    } else {
        dispMinisatOutput(res,grid);
        detruireClause(res);
        free(grid->tab);
        free(grid);
    }
}