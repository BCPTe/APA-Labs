/*
=============================================================
Name        : laib_3_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_3 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define MAX_M 50

typedef enum{FALSE, TRUE}boolean;

typedef struct{
    int extreme[2];     /* left-corner coordinates */
    int dims[2];      /* dims[0]=length ; dims[1]=height */
}submatrix;

void leggiMatrice(FILE *fp, int matrix[MAX_M][MAX_M], int *nr, int *nc);
int riconosciRegione(FILE *fp, int matrix[MAX_M][MAX_M], submatrix *ver, int r, int c, int *nr, int *nc);

int main(){
    int i, j, r, c, nr=0, nc=0;
    int matrix[MAX_M][MAX_M]={0};
    char filename[MAX+1];
    FILE *fp;
    submatrix ver={0};

    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    else
        leggiMatrice(fp, matrix, &nr, &nc);

    for(i=0 ; i<nr ; i++){
        for(j=0 ; j<nc ; j++)
            printf("%3d", matrix[i][j]);
        printf("\n");
    }

    /* enter coordinates to be checked */
    printf("Enter coordinates (care: <1,1> --> <0,0>): ");
    scanf("%d %d", &r, &c);
    if(riconosciRegione(fp, matrix, &ver, r, c, &nr, &nc))
        printf("\nupper left extreme <%d,%d>, length=%d, height=%d\n", r, c, ver.dims[0], ver.dims[1]);
    else
        printf("\n<%d,%d> is not an upper left extreme!\n", r, c);

    fclose(fp);

    return EXIT_SUCCESS;
}

void leggiMatrice(FILE *fp, int matrix[MAX_M][MAX_M], int *nr, int *nc){
    int i=0, j=0;
    char charline;

    /* WARNING: last line of the file must not contain '\n' // if u have '\n' then change line 80 to --> *nr=i <-- */
    while(fscanf(fp, "%d", &matrix[i][j])!=EOF){
        fscanf(fp, "%c", &charline);
        j++;
        if(charline=='\n'){
            i++;
            *nc=j;
            j=0;
        }
    }
    *nr=i+1;
}

int riconosciRegione(FILE *fp, int matrix[MAX_M][MAX_M], submatrix *ver, int r, int c, int *nr, int *nc){
    int i, j;

    if(matrix[r][c]){
        for(i=r ; matrix[i][c] && i>=0 ; i--)
            for(j=c ; matrix[i][j] && j>=0 ; j--);
        ver->extreme[0]=i+1;
        ver->extreme[1]=j+1;
        if(ver->extreme[0]==r && ver->extreme[1]==c){
            for(i=r ; matrix[i][c] && i<*nr ; i++)
                for(j=c ; matrix[i][j] && j<*nc ; j++);
            ver->dims[0]=j-c;
            ver->dims[1]=i-r;
            return TRUE;
        }
    }

    return FALSE;
}

