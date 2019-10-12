/*
=============================================================
Name        : laib_1_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_1 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20
#define MAX_LINE 100

void rotation(int matrix[MAX+10][MAX+10], int nr, int nc, char selector[41], int index, char direction[41], int position);

int main(){
    int i, j, nr, nc, index, position;
    int matrix[MAX+10][MAX+10];
    char filename[MAX+1], line[MAX_LINE+1], selector[41], direction[41];
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", filename);
    fflush(stdin);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    else{
        fscanf(fp, "%d\n%d", &nr, &nc);
        for(i=0 ; i<nr ; i++)
            for(j=0 ; j<nc ; j++)
                fscanf(fp, "%d", &matrix[i][j]);
    }

    do{
        do{
            printf("Enter command: ");
            gets(line);
            sscanf(line, "%s %d %s %d", selector, &index, direction, &position);
            if((index<=0 || index>nr || index>nc) && strcmp(selector, "fine")!=0)
                printf("Wrong index!\n");
            if(position>=nc && strcmp(selector, "riga")==0)
                position-=nc;
            else if(position>=nr && strcmp(selector, "colonna")==0)
                position-=nr;
        }while((index<=0 || index>nr || index>nc) && strcmp(selector, "fine")!=0);
        if(strcmp(selector, "riga")==0 || strcmp(selector, "colonna")==0)
            rotation(matrix, nr, nc, selector, index-1, direction, position);
    }while(strcmp(selector, "fine")!=0);

    return EXIT_SUCCESS;
}

void rotation(int matrix[MAX+10][MAX+10], int nr, int nc, char selector[41], int index, char direction[41], int position){
    int i, j, temp=0;

    if(strcmp(selector, "riga")==0){
        if(strcmp(direction, "destra")==0){
            /* right-shift */
            for(j=0 ; j<position ; j++){
                temp=matrix[index][nc-1];
                for(i=nc-1 ; i>0 ; i--)
                    matrix[index][i]=matrix[index][i-1];
                matrix[index][0]=temp;
            }
        }
        else if(strcmp(direction, "sinistra")==0){
            /* left-shift */
            for(j=0 ; j<position ; j++){
                temp=matrix[index][0];
                for(i=0 ; i<nc-1 ; i++)
                    matrix[index][i]=matrix[index][i+1];
                matrix[index][nc-1]=temp;
            }
        }
        else{
            printf("Impossible direction!\n");
            return;
        }
    }
    else if(strcmp(selector, "colonna")==0){
        if(strcmp(direction, "su")==0){
            /* up-shift */
            for(j=0 ; j<position ; j++){
                temp=matrix[0][index];
                for(i=0 ; i<nr-1 ; i++)
                    matrix[i][index]=matrix[i+1][index];
                matrix[nr-1][index]=temp;
            }
        }
        else if(strcmp(direction, "giu")==0){
            /* down-shift */
            for(j=0 ; j<position ; j++){
                temp=matrix[nr-1][index];
                for(i=nr-1 ; i>0 ; i--)
                    matrix[i][index]=matrix[i-1][index];
                matrix[0][index]=temp;
            }
        }
    }

    /* print shifted matrix */
    printf("Shifted matrix:\n\n");
    for(i=0 ; i<nr ; i++){
        for(j=0 ; j<nc ; j++)
            printf("%3d ", matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}
