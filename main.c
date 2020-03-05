#include "generation.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  Grille *res = readGrid("grille.txt");
  afficher_grille(res);
  return 0;
}
