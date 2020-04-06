#include "generation.h"
#include "grid.h"
#include "logic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*int main(int argc, char *argv[]) {
    bool Lpossible;
    int x, y;

    if(argc!=4)printf("Usage commande : ./main x y fichier");
    x=atoi(argv[1]);
    y=atoi(argv[2]);
    srand(time(NULL));

    Grid *res = readGrid(argv[3]);
    Lpossible = lampe_possible(x + res->taille * y,res);
    printf("Lampe possible : %d \n",(int)Lpossible);
    afficher_grille(res);
    return 0;
}*/

/*int main(int argc, char *argv[]) {
     int pourcentMur, taille;
    srand(time(NULL));
    Grid *res = NULL;

    if(argc!=3){
        printf("Usage commande : ./main pourcentMur taille\n");
        return 1;
    }
    pourcentMur=atoi(argv[1]);
    taille=atoi(argv[2]);
    res = genere_grille(pourcentMur,taille);
    afficher_grille(res);
    return 0;
}*/

/*int main(int argc, char *argv[]) {
    SequencePoint *seq;
    int x,y,taille;

    if(argc!=4){
        printf("Usage commande : ./main taille x y\n");
        return 1;
    }
    taille = atoi(argv[1]);
    x=atoi(argv[2]);
    y=atoi(argv[3]);
    point p = (point) { x,y };
    seq = enumSubLine(taille,p);
    afficher(seq);
    free(seq);
    seq = enumSubRow(taille,p);
    afficher(seq);
    free(seq);
    seq = enumAdj(taille,p);
    afficher(seq);
    free(seq);
    return 0;
}*/

int main(int argc, char *argv[]) {
    Clause *clause = newClause();
    Literal a = (Literal) { 0 , PLUS};
    Literal b = (Literal) { 1 , PLUS};
    Literal c = (Literal) { 2 , PLUS};
    Literal d = (Literal) { 3 , PLUS};
    Literal e = (Literal) { 4 , PLUS};
    Literal f = (Literal) { 5 , PLUS};
    Literal g = (Literal) { 6 , PLUS};

    addToClause(clause,a);
    addToClause(clause,b);
    addToClause(clause,c);
    addToClause(clause,d);
    addToClause(clause,e);
    addToClause(clause,f);
    addToClause(clause,g);

    afficherClause(clause);

    CNF *res = KChosenInClause(2,clause);
    afficherCNF(res);
    detruireClause(clause);
    detruireCNF(res);
    return 0;
}