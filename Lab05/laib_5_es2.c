/*
=============================================================
Name        : laib_5_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_5 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "mat.txt"

int **malloc2dR(int nr, int nc);
//void malloc2dP(int ***matrix, int nr, int nc);
void free2d(int **matrix, int nr);
void separa(int **matrix, int **black, int **white, int nr, int nc);

int main(){
    int nr, nc, i, j;
    int *black, *white;
    int **matrix;
    FILE *fp;

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    fscanf(fp, "%d %d", &nr, &nc);

    matrix=malloc2dR(nr, nc);
    //malloc2dP(&matrix, nr, nc);

    /* load file matrix */
    for(i=0 ; i<nr ; i++)
        for(j=0 ; j<nc ; j++)
            fscanf(fp, "%d", &matrix[i][j]);

    separa(matrix, &black, &white, nr, nc);

    if((nr*nc)%2){                          /* number of cells is odd */
        printf("black cells:\n");
        for(i=0 ; i<nr*nc/2+1 ; i++)
            printf("%d ", black[i]);
        printf("\nwhite cells:\n");
        for(i=0 ; i<nr*nc/2 ; i++)
            printf("%d ", white[i]);
    }
    else{                                   /* number of cells is even */
        printf("black cells:\n");
        for(i=0 ; i<nr*nc/2 ; i++)
            printf("%d ", black[i]);
        printf("\nwhite cells:\n");
        for(i=0 ; i<nr*nc/2 ; i++)
            printf("%d ", white[i]);
    }

    free(black);
    free(white);
    free2d(matrix, nr);

    return EXIT_SUCCESS;
}

int **malloc2dR(int nr, int nc){
    int i;
    int **matrix;

    matrix=calloc(nr, sizeof(int *));
    for(i=0 ; i<nr ; i++)
        matrix[i]=calloc(nc, sizeof(int));
    return matrix;
}

/*
void malloc2dP(int ***matrix, int nr, int nc){
    int i;
    *matrix=calloc(nr, sizeof(int *));
    for(i=0 ; i<nr ; i++)
        (*matrix)[i]=calloc(nc, sizeof(int));
}
*/

void free2d(int **matrix, int nr){
    int i;

    for(i=0 ; i<nr ; i++)
        free(matrix[i]);
    free(matrix);
}

void separa(int **matrix, int **black, int **white, int nr, int nc){
    int i, j, indw=0, indb=0;

    if((nr*nc)%2){
        *black=calloc(nr*nc/2+1, sizeof(int));
        *white=calloc(nr*nc/2, sizeof(int));

        for(i=0 ; i<nr ; i++)
            for(j=0 ; j<nc ; j++)
                if((i+j)%2) (*white)[indw++]=matrix[i][j];             /* if i+j is odd --> white cell */
                else (*black)[indb++]=matrix[i][j];            /* if i+j is even --> black cell */
    }
    else{
        *black=calloc(nr*nc/2, sizeof(int));
        *white=calloc(nr*nc/2, sizeof(int));

        for(i=0 ; i<nr ; i++)
            for(j=0 ; j<nc ; j++)
                if((i+j)%2) (*white)[indw++]=matrix[i][j];             /* if i+j is odd --> white cell */
                else (*black)[indb++]=matrix[i][j];            /* if i+j is even --> black cell */
    }
}
