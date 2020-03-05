#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "generation.h"

int main() {
    Grille *res;
    srand(time(NULL));
    res = genere_grille(40);
    afficher_grille(res);
    return 0;
}
