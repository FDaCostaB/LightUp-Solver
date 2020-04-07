#include "generation.h"
#include "grid.h"
#include "logic.h"
#include "dimacs.h"
#include <stdio.h>
#include <stdlib.h>

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

/*int main(int argc, char *argv[]) {
    Clause *clause = newClause();
    Literal a = (Literal) { 0 , PLUS};
    Literal b = (Literal) { 1 , PLUS};
    Literal c = (Literal) { 2 , PLUS};
    Literal d = (Literal) { 3 , MINUS};
    Literal e = (Literal) { 4 , PLUS};
    Literal f = (Literal) { 5 , PLUS};
    Literal g = (Literal) { 6 , PLUS};

    addToClause(clause,a,false);
    addToClause(clause,b,false);
    addToClause(clause,c,false);
    addToClause(clause,d,false);
    addToClause(clause,e,false);
    addToClause(clause,f,false);
    addToClause(clause,g,false);

    afficherClause(clause);

    CNF *res1 = KChosenInClause(4,clause);
    afficherCNF(res1);
    detruireCNF(res1);

    CNF *res2 = KneglectedInClause(4,clause);
    afficherCNF(res2);
    detruireCNF(res2);

    detruireClause(clause);

    return 0;
}*/


int main(int argc, char *argv[]) {
    // ouverture du fichier nom_f en lecture
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "w");
    CNF *res;
    if (f1 == NULL || f2 == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }
    res = readDimacs(f1);
    writeDimacs(f2,res);

    fclose(f1);
    fclose(f2);
    detruireCNF(res);
}
