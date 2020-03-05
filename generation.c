//
// Created by fabie on 03/03/2020.
//

#include "generation.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int nbCasesLibresAdj(Grille *grille, int i) {
  int n = 0;
  if (i - TAILLE >= 0 && (grille->tab[i - TAILLE] == LIBRE ||
                          grille->tab[i - TAILLE] == INCONNU)) {
    n++;
  }
  if ((i - 1) % TAILLE < (i % TAILLE) &&
      (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU)) {
    n++;
  }
  if ((i + 1) % TAILLE > (i % TAILLE) &&
      (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU)) {
    n++;
  }
  if (i + TAILLE < TAILLE * TAILLE && (grille->tab[i + TAILLE] == LIBRE ||
                                       grille->tab[i + TAILLE] == INCONNU)) {
    n++;
  }
  return n;
}

int nbLampesPossibles(Grille *grille, int i) {
  int n = 0;
  if (i - TAILLE >= 0 && lampe_possible(i - TAILLE, grille)) {
    n++;
  }
  if ((i - 1) % TAILLE < (i % TAILLE) && lampe_possible(i - 1, grille)) {
    n++;
  }
  if ((i + 1) % TAILLE > (i % TAILLE) && lampe_possible(i + 1, grille)) {
    n++;
  }
  if (i + TAILLE < TAILLE * TAILLE && lampe_possible(i + TAILLE, grille)) {
    n++;
  }
  return n;
}

int nbLampesPossiblesEtLibres(Grille *grille, int i) {
  int n = 0;
  if (i - TAILLE >= 0 &&
      (grille->tab[i - TAILLE] == LIBRE ||
       grille->tab[i - TAILLE] == INCONNU) &&
      lampe_possible(i - TAILLE, grille)) {
    n++;
  }
  if ((i - 1) % TAILLE < (i % TAILLE) && (i - 1) > 0 &&
      (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU) &&
      lampe_possible(i - 1, grille)) {
    n++;
  }
  if ((i + 1) % TAILLE > (i % TAILLE) && (i + 1) < TAILLE * TAILLE &&
      (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU) &&
      lampe_possible(i + 1, grille)) {
    n++;
  }
  if (i + TAILLE < TAILLE * TAILLE &&
      (grille->tab[i + TAILLE] == LIBRE ||
       grille->tab[i + TAILLE] == INCONNU) &&
      lampe_possible(i + TAILLE, grille)) {
    n++;
  }
  return n;
}

Case placerMur(Grille *grille, int i) {
  int chiffreMur = rand();
  if (nbCasesLibresAdj(grille, i) == 4) {
    grille->tab[i] = MUR0;
  } else if (nbLampesPossiblesEtLibres(grille, i) == 4) {
    chiffreMur = chiffreMur % (7);
    switch (chiffreMur) {
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
      grille->tab[i] = MURV;
      break;
    }
  } else if (nbLampesPossiblesEtLibres(grille, i) == 3) {
    chiffreMur = chiffreMur % (6);
    switch (chiffreMur) {
    case 0:
      if (nbCasesLibresAdj(grille, i) == 4)
        grille->tab[i] = MUR0;
      else
        grille->tab[i] = MURV;
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
    default:
      grille->tab[i] = MURV;
      break;
    }
  } else if (nbLampesPossiblesEtLibres(grille, i) == 2) {
    chiffreMur = chiffreMur % (5);
    switch (chiffreMur) {
    case 0:
      if (nbCasesLibresAdj(grille, i) == 4)
        grille->tab[i] = MUR0;
      else
        grille->tab[i] = MURV;
      break;
    case 1:
      grille->tab[i] = MUR1;
      break;
    case 2:
      grille->tab[i] = MUR2;
      break;
    default:
      grille->tab[i] = MURV;
      break;
    }
  } else if (nbLampesPossiblesEtLibres(grille, i) == 1) {
    chiffreMur = chiffreMur % (4);
    switch (chiffreMur) {
    case 0:
      if (nbCasesLibresAdj(grille, i) == 4)
        grille->tab[i] = MUR0;
      else
        grille->tab[i] = MURV;
      break;
    case 1:
      grille->tab[i] = MUR1;
      break;
    default:
      grille->tab[i] = MURV;
      break;
    }
  } else {
    grille->tab[i] = MURV;
  }
  return grille->tab[i];
}

void ajouterLampe(Grille *grille, int casePossible[TAILLE], int longueur,
                  int aPlacer) {
  if (aPlacer > longueur) {
    printf("ERREUR GRILLE IMPOSSIBLE\n");
    return;
  }

  if (longueur != 0) {
    printf("Case choisie(s) : ");
    for (int i = 0; i < aPlacer; i++) {
      int x = rand() % longueur;
      while (grille->tab[casePossible[x]] == LAMPE) {
        x = (x + 1) % longueur;
      }
      grille->tab[casePossible[x]] = LAMPE;
      printf("( %d , %d ) -  ", casePossible[x] % TAILLE,
             casePossible[x] / TAILLE);
    }
    for (int j = 0; j < longueur; j++) {
      if (grille->tab[casePossible[j]] != LAMPE)
        grille->tab[casePossible[j]] = VIDE;
    }
  }
}

void placerLampe(Case actuel, int i, Grille *grille) {
  int casePossible[TAILLE];
  int longueur = 0;

  if (actuel == MURV)
    return;
  if (actuel == MUR0) {
    if (i - TAILLE >= 0)
      grille->tab[i - TAILLE] = VIDE;
    if ((i - 1) % TAILLE < (i % TAILLE))
      grille->tab[i - 1] = VIDE;
    if ((i + 1) % TAILLE > (i % TAILLE))
      grille->tab[i + 1] = VIDE;
    if (i + TAILLE < TAILLE * TAILLE)
      grille->tab[i + TAILLE] = VIDE;
  } else {
    if (i - TAILLE >= 0) {
      if (lampe_possible(i - TAILLE, grille) && i - TAILLE >= 0) {
        casePossible[longueur] = i - TAILLE;
        longueur++;
      } else {
        if (grille->tab[i - TAILLE] == LIBRE ||
            grille->tab[i - TAILLE] == INCONNU)
          grille->tab[i - TAILLE] = VIDE;
      }
    }
    if ((i - 1) % TAILLE < (i % TAILLE)) {
      if (lampe_possible(i - 1, grille) && i - 1 >= 0) {
        casePossible[longueur] = i - 1;
        longueur++;
      } else {
        if (grille->tab[i - 1] == LIBRE || grille->tab[i - 1] == INCONNU)
          grille->tab[i - 1] = VIDE;
      }
    }
    if ((i + 1) % TAILLE > (i % TAILLE)) {
      if (lampe_possible(i + 1, grille) && i + 1 < TAILLE * TAILLE) {
        casePossible[longueur] = i + 1;
        longueur++;
      } else {
        if (grille->tab[i + 1] == LIBRE || grille->tab[i + 1] == INCONNU)
          grille->tab[i + 1] = VIDE;
      }
    }

    if (i + TAILLE < TAILLE * TAILLE) {
      if (lampe_possible(i + TAILLE, grille) && i + TAILLE < TAILLE * TAILLE) {
        casePossible[longueur] = i + TAILLE;
        longueur++;
      } else {
        if (grille->tab[i + TAILLE] == LIBRE ||
            grille->tab[i + TAILLE] == INCONNU)
          grille->tab[i + TAILLE] = VIDE;
      }
    }
    if (actuel == MUR1)
      ajouterLampe(grille, casePossible, longueur, 1);
    if (actuel == MUR2)
      ajouterLampe(grille, casePossible, longueur, 2);
    if (actuel == MUR3)
      ajouterLampe(grille, casePossible, longueur, 3);
    if (actuel == MUR4)
      ajouterLampe(grille, casePossible, longueur, 4);
  }
  switch (grille->tab[i]) {
  case MURV:
    printf("MURV en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  case MUR0:
    printf("MUR0 en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  case MUR1:
    printf("MUR1 en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  case MUR2:
    printf("MUR2 en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  case MUR3:
    printf("MUR3 en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  case MUR4:
    printf("MUR4 en %d , %d. Case possible : ", i % TAILLE, i / TAILLE);
    break;
  }
  for (int i = 0; i < longueur; i++) {
    printf(" ( %d , %d ) ", casePossible[i] % TAILLE, casePossible[i] / TAILLE);
  }
  printf("\n");
  /*longueur = 0;
  for(int j = TAILLE * ligne;i<j; j++){
      if(lampe_possible(j,grille)){
          casePossible[longueur] = j;
          longueur ++;
      }
  }
      if(longueur != 0) grille->tab[rand() % longueur] = LAMPE;
      ajouterLampe(grille,casePossible,longueur,1)
      */
}

Grille *newGrid(int size) {
  Grille *g = (Grille *)malloc(sizeof(Grille));
  Case *tab = (Case *)malloc(sizeof(Case) * size);
  g->tab = tab;
  g->taille = size;
  return g;
}

Grille *genere_grille(int pourcentMur) {
  int x = 0;
  Grille *res = newGrid(7);
  int i = 0;
  Case actuel;

  while (i < TAILLE * TAILLE) {
    x = rand() % (100);
    while (i < TAILLE * TAILLE && res->tab[i] != INCONNU) {
      i++;
    }
    if (x < pourcentMur) {
      actuel = placerMur(res, i);
      placerLampe(actuel, i, res);
    } else {
      res->tab[i] = LIBRE;
    }
    i++;
  }
  return res;
}

bool lampe_possible(int i, Grille *grille) {
  int ligne = i / TAILLE;
  int colonne = i % TAILLE;
  bool lignePossible = true;
  bool colonnePossible = true;

  if (grille->tab[i] != LIBRE && grille->tab[i] != INCONNU)
    return false;

  for (int j = 0; j < TAILLE; j++) {
    if (grille->tab[ligne * TAILLE + j] == LAMPE && ligne * TAILLE + j <= i)
      lignePossible = false;
    if ((grille->tab[ligne * TAILLE + j] == MURV ||
         grille->tab[ligne * TAILLE + j] == MUR0 ||
         grille->tab[ligne * TAILLE + j] == MUR1 ||
         grille->tab[ligne * TAILLE + j] == MUR2 ||
         grille->tab[ligne * TAILLE + j] == MUR3 ||
         grille->tab[ligne * TAILLE + j] == MUR4) &&
        ligne * TAILLE + j < i)
      lignePossible = true;
    if (grille->tab[ligne * TAILLE + j] == LAMPE && ligne * TAILLE + j > i)
      return false;
    if ((grille->tab[ligne * TAILLE + j] == MURV ||
         grille->tab[ligne * TAILLE + j] == MUR0 ||
         grille->tab[ligne * TAILLE + j] == MUR1 ||
         grille->tab[ligne * TAILLE + j] == MUR2 ||
         grille->tab[ligne * TAILLE + j] == MUR3 ||
         grille->tab[ligne * TAILLE + j] == MUR4) &&
        ligne * TAILLE + j > i)
      break;

    if (grille->tab[colonne + j * TAILLE] == LAMPE && colonne + j * TAILLE < i)
      colonnePossible = false;
    if ((grille->tab[colonne + j * TAILLE] == MURV ||
         grille->tab[colonne + j * TAILLE] == MUR0 ||
         grille->tab[colonne + j * TAILLE] == MUR1 ||
         grille->tab[colonne + j * TAILLE] == MUR2 ||
         grille->tab[colonne + j * TAILLE] == MUR3 ||
         grille->tab[colonne + j * TAILLE] == MUR4) &&
        colonne + j * TAILLE < i)
      colonnePossible = true;
    if (grille->tab[colonne + j * TAILLE] == LAMPE && colonne + j * TAILLE > i)
      return false;
    if ((grille->tab[colonne + j * TAILLE] == MURV ||
         grille->tab[colonne + j * TAILLE] == MUR0 ||
         grille->tab[colonne + j * TAILLE] == MUR1 ||
         grille->tab[colonne + j * TAILLE] == MUR2 ||
         grille->tab[colonne + j * TAILLE] == MUR3 ||
         grille->tab[colonne + j * TAILLE] == MUR4) &&
        colonne + j * TAILLE > i)
      break;
  }
  return (colonnePossible && lignePossible);
}

void afficher_grille(Grille *grille) {
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      switch (grille->tab[j + TAILLE * i]) {
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

Grille *readGrid(char *fileName) {
  FILE *f;
  int i, j;
  char *s = NULL;
  char *g = NULL;
  size_t size = sizeof(int);
  f = fopen(fileName, "r");

  getline(&s, &size, f);
  int sizeOfGrid = atoi(s);

  Grille *grid = newGrid(sizeOfGrid);

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
        printf("j:::%d:::%d:::%c\n", j, i, g[j]);
        grid->tab[j + sizeOfGrid * i] = INCONNU;
        break;
      }
      printf("%c", g[j]);
    }
  }

  for (i = 0; i < sizeOfGrid; ++i) {
    for (j = 0; j < sizeOfGrid; ++j) {
      printf("%d", grid->tab[j + sizeOfGrid * i]);
    }
  }
  printf("\n\n");

  return grid;
}