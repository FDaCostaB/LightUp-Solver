//
// Created by fabie on 03/03/2020.
//

#include "generation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int nbCasesLibresAdj(Grid *grille, int i) {
  int n = 0;
  if (i - grille->taille >= 0 && (grille->tab[i - grille->taille] == LIBRE ||
                                  grille->tab[i - grille->taille] == INCONNU)) {
    n++;
  }
  if ((i - 1) % grille->taille < (i % grille->taille) &&
      (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU)) {
    n++;
  }
  if ((i + 1) % grille->taille > (i % grille->taille) &&
      (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU)) {
    n++;
  }
  if (i + grille->taille < grille->taille * grille->taille &&
      (grille->tab[i + grille->taille] == LIBRE ||
       grille->tab[i + grille->taille] == INCONNU)) {
    n++;
  }
  return n;
}

int nbLampesAdj(Grid *grille, int i) {
    int n = 0;
    if (i - grille->taille >= 0 && (grille->tab[i - grille->taille] == LAMPE) ) {
        n++;
    }
    if ((i - 1) % grille->taille < (i % grille->taille) && (grille->tab[i - 1] == LAMPE)) {
        n++;
    }
    if ((i + 1) % grille->taille > (i % grille->taille) && (grille->tab[i + 1] == LAMPE)) {
        n++;
    }
    if (i + grille->taille < grille->taille * grille->taille && (grille->tab[i + grille->taille] == LAMPE)) {
        n++;
    }
    return n;
}

int nbLampesPossibles(Grid *grille, int i) {
  int n = 0;
  if (i - grille->taille >= 0 && lampe_possible(i - grille->taille, grille)) {
    n++;
  }
  if ((i - 1) % grille->taille < (i % grille->taille) &&
      lampe_possible(i - 1, grille)) {
    n++;
  }
  if ((i + 1) % grille->taille > (i % grille->taille) &&
      lampe_possible(i + 1, grille)) {
    n++;
  }
  if (i + grille->taille < grille->taille * grille->taille &&
      lampe_possible(i + grille->taille, grille)) {
    n++;
  }
  return n;
}

int nbLampesPossiblesEtLibres(Grid *grille, int i) {
  int n = 0;
  if (i - grille->taille >= 0 &&
      (grille->tab[i - grille->taille] == LIBRE ||
       grille->tab[i - grille->taille] == INCONNU) &&
      lampe_possible(i - grille->taille, grille)) {
    n++;
  }
  if ((i - 1) % grille->taille < (i % grille->taille) && (i - 1) > 0 &&
      (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU) &&
      lampe_possible(i - 1, grille)) {
    n++;
  }
  if ((i + 1) % grille->taille > (i % grille->taille) &&
      (i + 1) < grille->taille * grille->taille &&
      (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU) &&
      lampe_possible(i + 1, grille)) {
    n++;
  }
  if (i + grille->taille < grille->taille * grille->taille &&
      (grille->tab[i + grille->taille] == LIBRE ||
       grille->tab[i + grille->taille] == INCONNU) &&
      lampe_possible(i + grille->taille, grille)) {
    n++;
  }
  return n;
}

//Out of the grid we consider that any Case is a wall
bool isWall(Grid *grille,int i){
    return i < 0 || i >= (grille->taille * grille->taille) || grille->tab[ i ] == MURV || grille->tab[ i ] == MUR0 ||
    grille->tab[ i ] == MUR1 || grille->tab[ i ] == MUR2 || grille->tab[ i ] == MUR3 || grille->tab[ i ] == MUR4;
}

bool lampe_possible(int i, Grid *grille) {
    int y = i / grille->taille;
    int x = i % grille->taille;
    bool lignePossible = true;
    bool ligneFinal = false,colonneFinal = false;
    bool colonnePossible = true;

    if (grille->tab[i] != LIBRE && grille->tab[i] != INCONNU ){
        //if(grille->tab[i] != MURV) printf("MURV en %d\n",i);
        return false;
    }
    int j = 0;
    while( (!ligneFinal || !colonneFinal) && j<grille->taille) {
        if (grille->tab[y * grille->taille + j] == LAMPE &&
            y * grille->taille + j < i)
            lignePossible = false;
        if(y * grille->taille + j == i && !lignePossible) {
            //printf("Lampe à gauche\n");
            return false;
        }
        if ((grille->tab[y * grille->taille + j] == MURV ||
             grille->tab[y * grille->taille + j] == MUR0 ||
             grille->tab[y * grille->taille + j] == MUR1 ||
             grille->tab[y * grille->taille + j] == MUR2 ||
             grille->tab[y * grille->taille + j] == MUR3 ||
             grille->tab[y * grille->taille + j] == MUR4) &&
            y * grille->taille + j < i)
            lignePossible = true;
        if (grille->tab[y * grille->taille + j] == LAMPE &&
            y * grille->taille + j > i && !ligneFinal){
            //printf("Lampe à droite\n");
            return false;
        }

        if ( ((grille->tab[y * grille->taille + j] == MURV ||
               grille->tab[y * grille->taille + j] == MUR0 ||
               grille->tab[y * grille->taille + j] == MUR1 ||
               grille->tab[y * grille->taille + j] == MUR2 ||
               grille->tab[y * grille->taille + j] == MUR3 ||
               grille->tab[y * grille->taille + j] == MUR4 ) &&
              y * grille->taille + j > i ) || ligneFinal){
            ligneFinal = true;
            lignePossible = true;
        }

        if (grille->tab[x + j * grille->taille] == LAMPE &&
            x + j * grille->taille < i)
            colonnePossible = false;
        if(x + j * grille->taille == i && !colonnePossible) {
            //printf("Lampe dessus\n");
            return false;
        }
        if ((grille->tab[x + j * grille->taille] == MURV ||
             grille->tab[x + j * grille->taille] == MUR0 ||
             grille->tab[x + j * grille->taille] == MUR1 ||
             grille->tab[x + j * grille->taille] == MUR2 ||
             grille->tab[x + j * grille->taille] == MUR3 ||
             grille->tab[x + j * grille->taille] == MUR4) &&
            x + j * grille->taille < i)
            colonnePossible = true;
        if (grille->tab[x + j * grille->taille] == LAMPE &&
            x + j * grille->taille > i && !colonneFinal){
            //printf("Lampe dessous\n");
            return false;
        }



        if (((grille->tab[x + j * grille->taille] == MURV ||
              grille->tab[x + j * grille->taille] == MUR0 ||
              grille->tab[x + j * grille->taille] == MUR1 ||
              grille->tab[x + j * grille->taille] == MUR2 ||
              grille->tab[x + j * grille->taille] == MUR3 ||
              grille->tab[x + j * grille->taille] == MUR4 ) &&
             x + j * grille->taille > i) || colonneFinal ){
            colonneFinal = true;
            colonnePossible = true;
        }
        j ++;
    }
    return (colonnePossible && lignePossible);
}

Box placerMur(Grid *grille, int i) {
  int chiffreMur = rand();
  int estVide = rand() % 5;
  if(estVide < 1 || nbLampesPossiblesEtLibres(grille, i) == 0) {
      grille->tab[i] = MURV;
      return  MURV;
  }
  if (nbCasesLibresAdj(grille, i) == 4) {
        grille->tab[i] = MUR0;
  } else {
        chiffreMur = chiffreMur % (nbLampesPossiblesEtLibres(grille, i)+1-nbLampesAdj(grille,i));
        switch ( chiffreMur +  nbLampesAdj(grille,i) ) {
            case 0:
                grille->tab[i] = MUR0;
                break;
            case 1:
                grille->tab[i] = MUR1;
                break;
            case 2:
                grille->tab[i] = MUR2;
                break;
            case 3:
                grille->tab[i] = MUR3;
                break;
            case 4:
                grille->tab[i] = MUR4;
                break;
            default:
                printf("ERREUR NUMERO MUR SUPERIEUR A 5\n");
                exit(1);
    }
  }
    return grille->tab[i];
}

void ajouterLampe(Grid *grille, int casePossible[], int longueur, int aPlacer) {
  if (aPlacer > longueur) {
    printf("ERREUR GRILLE IMPOSSIBLE\n");
    exit(2);
  }

  if (longueur != 0) {
    //printf("Case choisie(s) : ");
    for (int i = 0; i < aPlacer; i++) {
      int x = rand() % longueur;
      while (grille->tab[casePossible[x]] == LAMPE) {
        x = (x + 1) % longueur;
      }
      grille->tab[casePossible[x]] = LAMPE;
      //printf(" ( %d , %d ) -  ", casePossible[x] % grille->taille,casePossible[x] / grille->taille);
    }
    for (int j = 0; j < longueur; j++) {
      if (grille->tab[casePossible[j]] != LAMPE)
        grille->tab[casePossible[j]] = VIDE;
    }
  }
}

void placerLampe(Box actuel, int i, Grid *grille) {
  int casePossible[5];
  int longueur = 0;

  if (actuel == MURV)
    return;
  if (actuel == MUR0) {
    if (i - grille->taille >= 0)
      grille->tab[i - grille->taille] = VIDE;
    if ((i - 1) % grille->taille < (i % grille->taille))
      grille->tab[i - 1] = VIDE;
    if ((i + 1) % grille->taille > (i % grille->taille))
      grille->tab[i + 1] = VIDE;
    if (i + grille->taille < grille->taille * grille->taille)
      grille->tab[i + grille->taille] = VIDE;
  } else {
    if (i - grille->taille >= 0) {
      if (lampe_possible(i - grille->taille, grille) &&
          i - grille->taille >= 0) {
        casePossible[longueur] = i - grille->taille;
        longueur++;
      } else {
        if (grille->tab[i - grille->taille] == LIBRE ||
            grille->tab[i - grille->taille] == INCONNU)
          grille->tab[i - grille->taille] = VIDE;
      }
    }
    if ((i - 1) % grille->taille < (i % grille->taille)) {
      if (lampe_possible(i - 1, grille) && i - 1 >= 0) {
        casePossible[longueur] = i - 1;
        longueur++;
      } else {
        if (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU)
          grille->tab[i - 1] = VIDE;
      }
    }
    if ((i + 1) % grille->taille > (i % grille->taille)) {
      if (lampe_possible(i + 1, grille) &&
          i + 1 < grille->taille * grille->taille) {
        casePossible[longueur] = i + 1;
        longueur++;
      } else {
        if (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU)
          grille->tab[i + 1] = VIDE;
      }
    }

    if (i + grille->taille < grille->taille * grille->taille) {
      if (lampe_possible(i + grille->taille, grille) &&
          i + grille->taille < grille->taille * grille->taille) {
        casePossible[longueur] = i + grille->taille;
        longueur++;
      } else {
        if (grille->tab[i + grille->taille] == LIBRE ||
            grille->tab[i + grille->taille] == INCONNU)
          grille->tab[i + grille->taille] = VIDE;
      }
    }
    if (actuel == MUR1)
      ajouterLampe(grille, casePossible, longueur, 1-nbLampesAdj(grille,i));
    if (actuel == MUR2)
      ajouterLampe(grille, casePossible, longueur, 2-nbLampesAdj(grille,i));
    if (actuel == MUR3)
      ajouterLampe(grille, casePossible, longueur, 3-nbLampesAdj(grille,i));
    if (actuel == MUR4)
      ajouterLampe(grille, casePossible, longueur, 4-nbLampesAdj(grille,i));
  }
  /*switch (grille->tab[i]) {
  case MURV:
    printf("MURV en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
  case MUR0:
    printf("MUR0 en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
  case MUR1:
    printf("MUR1 en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
  case MUR2:
    printf("MUR2 en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
  case MUR3:
    printf("MUR3 en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
  case MUR4:
    printf("MUR4 en %d , %d. Case possible : ", i % grille->taille,
           i / grille->taille);
    break;
      default:
          perror("Mur manquant");
          break;
  }
  for (int i = 0; i < longueur; i++) {
    printf(" ( %d , %d ) ", casePossible[i] % grille->taille,
           casePossible[i] / grille->taille);
  }
  printf("\n");*/
/////TODO COMPLETE LIGNE
}

Grid *newGrid(int size) {
  Grid *g = (Grid *)malloc(sizeof(Grid));
  Box *tab = (Box *)malloc(sizeof(Box) * size * size);
  g->tab = tab;
  g->taille = size;
  for(int i =0; i<size*size;i++){
      g->tab[i]=INCONNU;
  }
  return g;
}

Grid *genere_grille(int pourcentMur, int taille) {
  int x = 0;
  Grid *res = newGrid(taille);
  int i = 0;
  Box actuel;

  while (i < res->taille * res->taille) {
    x = rand() % (100);
    while (i < res->taille * res->taille && res->tab[i] != INCONNU) {
      i++;
    }
    if (x < pourcentMur) {
      actuel = placerMur(res, i);
      //EMPECHER UN "INTERVALLE" AVEC TOUTE LES CASES VIDES
      placerLampe(actuel, i, res);
    } else {
      res->tab[i] = LIBRE;
    }
    i++;
  }
  return res;
}

void clearGrid(Grid *grid){
    for (int i = 0; i < grid->taille; i++) {
        for (int j = 0; j < grid->taille; j++) {
            if(grid->tab[j + grid->taille * i] == LAMPE || grid->tab[j + grid->taille * i] == VIDE){
                grid->tab[j + grid->taille * i] = LIBRE;
            }
        }
    }
}


void dispGrid(Grid *grid) {
  for (int i = 0; i < grid->taille; i++) {
    for (int j = 0; j < grid->taille; j++) {
      switch (grid->tab[j + grid->taille * i]) {
      case MURV:
        printf("#");
        break;
      case MUR0:
        printf("0");
        break;
      case MUR1:
        printf("1");
        break;
      case MUR2:
        printf("2");
        break;
      case MUR3:
        printf("3");
        break;
      case MUR4:
        printf("4");
        break;
      case VIDE:
        printf(".");
        break;
      case LIBRE:
        printf("_");
        break;
      case LAMPE:
        printf("O");
        break;
      case INCONNU:
        printf("?");
        break;
      }
    }
    printf("\n");
  }
}

void writeGrid(char *fileName,Grid *grid) {
    FILE *f = fopen(fileName, "w");
    if (f == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }
    fprintf(f,"%d\n",grid->taille);
    for (int i = 0; i < grid->taille; i++) {
        for (int j = 0; j < grid->taille; j++) {
            switch (grid->tab[j + grid->taille * i]) {
                case MURV:
                    fprintf(f,"#");
                    break;
                case MUR0:
                    fprintf(f,"0");
                    break;
                case MUR1:
                    fprintf(f,"1");
                    break;
                case MUR2:
                    fprintf(f,"2");
                    break;
                case MUR3:
                    fprintf(f,"3");
                    break;
                case MUR4:
                    fprintf(f,"4");
                    break;
                case VIDE:
                    fprintf(f,".");
                    break;
                case LIBRE:
                    fprintf(f,"_");
                    break;
                case LAMPE:
                    fprintf(f,"O");
                    break;
                case INCONNU:
                    fprintf(f,"?");
                    break;
            }
        }
        fprintf(f,"\n");
    }
}

Grid *readGrid(char *fileName) {
    FILE *f;
    int i, j, sizeOfGrid;
    f = fopen(fileName, "r");

    fscanf(f,"%d\n", &sizeOfGrid);
    char *g = (char *) malloc(sizeof(char)*(sizeOfGrid+1));
    size_t size = sizeof(char) * (sizeOfGrid+1);

    Grid *grid = newGrid(sizeOfGrid);

    for (i = 0; i < sizeOfGrid; ++i) {
        getline(&g, &size, f);
        for (j = 0; j < sizeOfGrid; ++j) {
            switch (g[j]) {
                case '#':
                    grid->tab[j + sizeOfGrid * i] = MURV;
                    break;
                case '0':
                    grid->tab[j + sizeOfGrid * i] = MUR0;
                    break;
                case '1':
                    grid->tab[j + sizeOfGrid * i] = MUR1;
                    break;
                case '2':
                    grid->tab[j + sizeOfGrid * i] = MUR2;
                    break;
                case '3':
                    grid->tab[j + sizeOfGrid * i] = MUR3;
                    break;
                case '4':
                    grid->tab[j + sizeOfGrid * i] = MUR4;
                    break;
                case '.':
                    grid->tab[j + sizeOfGrid * i] = VIDE;
                    break;
                case '_':
                    grid->tab[j + sizeOfGrid * i] = LIBRE;
                    break;
                case 'O':
                    grid->tab[j + sizeOfGrid * i] = LAMPE;
                    break;
                default:
                    grid->tab[j + sizeOfGrid * i] = INCONNU;
                    break;
            }
        }
    }

    free(g);
    fclose(f);
    return grid;
}