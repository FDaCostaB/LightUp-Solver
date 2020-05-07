//
// Created by fabie on 10/04/2020.
//

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "grid.h"
#include "generation.h"

int main(int argc, char *argv[]) {
     int pourcentMur, taille;
    srand(time(NULL));
    Grid *res = NULL;

    if(argc!=4){
        printf("Usage commande : ./main pourcentMur taille res.grid\n");
        return 1;
    }
    pourcentMur=atoi(argv[1]);
    taille=atoi(argv[2]);
    res = genere_grille(pourcentMur,taille);
    clearGrid(res);
    writeGrid(argv[3],res);
    detruireGrid(res);
    return 0;
}