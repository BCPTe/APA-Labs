/*
=============================================================
Name        : laib_1_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_1 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

void whoisleader(int matrix[MAX][MAX], int rows, int columns);

int main(){
    int i, j, rows, columns;
    int matrix[MAX][MAX]={0};
    char filename[MAX+1];
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    else{
        fscanf(fp, "%d %d\n", &rows, &columns);
        for(i=0 ; i<rows ; i++){
            for(j=0 ; j<columns ; j++)
                fscanf(fp, "%d", &matrix[i][j]);
        }
    }

    printf("\n");
    whoisleader(matrix, rows, columns);

    return EXIT_SUCCESS;
}

void whoisleader(int matrix[MAX][MAX], int rows, int columns){
    int i, j, leader=0, max=-1;
    int tot[MAX]={0};

    for(j=0 ; j<columns ; j++){
        tot[0]+=matrix[0][j];
        if(tot[0]>max)
            max=tot[0];
        for(i=1 ; i<rows ; i++){
            tot[i]+=matrix[i][j];
            if(tot[i]>max){
                max=tot[i];
                leader=i;
            }
        }
        /* print leader at day X */
        printf("Leader at day #%d is team #%d!\n", j+1, leader+1);
    }
}
