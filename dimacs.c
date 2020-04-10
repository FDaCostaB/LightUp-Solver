//
// Created by fabie on 07/04/2020.
//

#include <stdlib.h>
#include <string.h>
#include "dimacs.h"
#include "generation.h"

void commentPartInspection(FILE *f)
{
    /* lecture des �ventuelles lignes commen�ant par # */
    bool isComment = true;
    while (isComment)    {
        /* tester d'abord la fin de fichier */
        if (feof(f))
        {
            printf("ERROR : Unexpected end of file\n");
            exit(1);
        }

        /* lire un caractere et tester par rapport � '#' */
        char c;
        fscanf(f, "%c", &c);
        if (c=='c')
        {
            /* lire le reste de la ligne */
            while(c!='\n'){
                fscanf(f, "%c", &c);
                if (feof(f)){
                    printf("ERROR : Unexpected end of file\n");
                    exit(1);
                }
            }
        }
        else
        {
            /* reculer d'un caract�re dans f */
            fseek(f, -1, SEEK_CUR);
            isComment = false;
        }
    }
}

CNF *readDimacs(FILE *f){
    int cardVar=0 , cardClause=0;
    char scanned = 0;
    Literal l ;
    Clause *curr = newClause();
    int litteralVal=0;

    /* comment line(s) */
    commentPartInspection(f);

    /* problem line */
    char *line = (char *) malloc(sizeof(char)*7);
    fgets(line, 7, f);
    if(strcmp(line, "p cnf ")!=0){
        printf("ERROR : Unexpected character in file\n");
        exit(1);
    }
    if(fscanf(f, "%u", &cardVar) != 1){
        printf("ERROR : Unexpected character in file (number of variables missing) \n");
        exit(1);
    }
    if(fscanf(f, "%u", &cardClause) != 1){
        printf("ERROR : Unexpected character in file (number of clauses missing) \n");
        exit(1);
    }
    free(line);

    printf("Number of variables : %d\n",cardVar);
    printf("Number of clauses : %d\n",cardClause);

    /* cnf lecture */
    CNF * res = newCNF();
    res->nbVar = cardVar;
    /*Each loop read a litteral */
    while(feof(f) == 0){
        litteralVal = 0;
        l.sign = PLUS;
        l.x = 0;
        while( (scanned < '0' || scanned >'9') && scanned != '-' && feof(f) == 0){
            fscanf(f,"%c",&scanned);
        }
        if(scanned == '0'){
            addToCNF(res,curr);
            curr = newClause();
            fscanf(f,"%c",&scanned);
        }else {
            if(scanned == '-'){
                l.sign = MINUS;
                fscanf(f,"%c",&scanned);
                if(scanned<'1' || scanned>'9'){
                    printf("ERROR : Unexpected character in file (Not a number or 0 after -) \n");
                    exit(1);
                }
            }

            while( (scanned >= '0' && scanned<='9') && feof(f) == 0){
                litteralVal = 10 * litteralVal + (scanned-'0');
                fscanf(f,"%c",&scanned);
                //printf("%c\n",scanned);
            }

            if(feof(f) == 0){
                l.x = litteralVal;
                addToClause(curr,l,false);
            } else {
                addToCNF(res,curr);
            }

        }
        //fscanf(f,"%c",&scanned);
        //printf("%c",scanned);

    }

    return res;

}

Clause *readMinisatOut(char *fileName){
    char scanned = 0;
    Literal l ;

    FILE *f = fopen(fileName, "r");
    if (f == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }

    /* problem line */
    char *line = (char *) malloc(sizeof(char)*7);
    fgets(line, 6, f);
    if(strcmp(line, "UNSAT")==0){
        printf("No solution was found by minisat\n");
        exit(1);
    }
    free(line);

    /* Clause utilisé comme liste chainée comme stockage simple et efficace */
    Clause * res = newClause();
    int litteralVal;
    /*Each loop read a litteral */
    while(feof(f) == 0){
        litteralVal = 0;
        l.sign = PLUS;
        l.x = 0;
        while( (scanned < '0' || scanned >'9') && scanned != '-' && feof(f) == 0){
            fscanf(f,"%c",&scanned);
        }
        if(scanned == '0'){
            return res;
        }else {
            if(scanned == '-'){
                l.sign = MINUS;
                fscanf(f,"%c",&scanned);
                if(scanned<'1' || scanned>'9'){
                    printf("ERROR : Unexpected character in file (Not a number or 0 after -) \n");
                    exit(1);
                }
            }

            while( scanned >= '0' && scanned<='9'&& feof(f) == 0){
                litteralVal = 10 * litteralVal + (scanned-'0');
                fscanf(f,"%c",&scanned);
            }
            l.x = litteralVal;
            addToClause(res,l,false);
        }

    }

    return res;
}

void dispMinisatOutput(Clause *solution, Grid *grid){
    CellLiteral *curr = solution->tete;
    while(curr != NULL) {
        if(curr->x.sign==PLUS) {
            if(grid->tab[(curr->x.x) - 1] !=LIBRE) {
                printf("ERROR : LAMP ON NON-EMPTY BOX\n");
                exit(1);
            }
            grid->tab[(curr->x.x) - 1] = LAMPE;
        }
        curr = curr->suivant;
    }

    dispGrid(grid);
}

void writeDimacs(char *fileName,CNF *toWrite){
    FILE *f = fopen(fileName, "w");
    if (f == NULL){
        printf("ERROR : Impossible file opening \n");
        exit(1);
    }
    CellClause *currClause = toWrite->tete;
    CellLiteral *currLitt;
    fprintf(f,"p cnf %d %d\n", toWrite->nbVar, toWrite->taille);
    while(currClause != NULL){
        currLitt = currClause->c->tete;
        while(currLitt != NULL){
            switch (currLitt->x.sign){
                case PLUS:
                    fprintf(f,"%d ",(currLitt->x.x)+1);
                    break;
                case MINUS:
                    fprintf(f,"-%d ",(currLitt->x.x)+1);
                    break;
            }
            currLitt = currLitt->suivant;
        }
        fprintf(f,"0 \n");
        currClause = currClause->suivant;
    }
    fclose(f);
}