/*
=============================================================
Name        : laib_0_es4.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_0 Exercise 4 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int printsubm(int size, int nr, int nc, int matrix[MAX][MAX], int max_sum, int maxsum_matrix[][MAX]);

int main(){
    int i, j, size, size_save, min, nr, nc, max_sum=0;
    int matrix[MAX][MAX], maxsum_matrix[MAX][MAX]={0};
    char filename[MAX+1];
    FILE *fp;

    /* ask user to enter filename */
    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    else{
        fscanf(fp, "%d %d", &nr, &nc);
        min=nr;
        if(nc<min)
            min=nc;
        for(i=0 ; i<nr ; i++){
            for(j=0 ; j<nc ; j++){
                fscanf(fp, "%d", &matrix[i][j]);
            }
        }
    }

    do{
        do{
            printf("Enter the size of the square sub-matrix: ");
            scanf("%d", &size);
            if(size>min)
                printf("Error: size must not exceed min(nr,nc)!\n");
        }while(size>min);

        if(size>0 && size<=min){
                for(i=0 ; i<MAX ; i++)
                    for(j=0 ; j<MAX ; j++)
                        maxsum_matrix[i][j]=0;
            max_sum=printsubm(size, nr, nc, matrix, max_sum, maxsum_matrix);
            size_save=size;
        }

    }while(size>0 && size<=min);

    /* print submatrix with max sum */
    printf("\nMaxsum_matrix (%d):\n\n", max_sum);
    for(i=0 ; i<size_save ; i++){
        for(j=0 ; j<size_save ; j++)
            printf("%3d", maxsum_matrix[i][j]);
        printf("\n");
    }
    printf("\n");
    system("pause");

    return EXIT_SUCCESS;
}

int printsubm(int size, int nr, int nc, int matrix[MAX][MAX], int max_sum, int maxsum_matrix[][MAX]){
    int i, j, t, z, sum=0;

    max_sum=0;
    for(i=0 ; i<nr-size+1 ; i++){
        for(j=0 ; j<nc-size+1 ; j++){
            sum=0;
            for(t=i ; t<size+i ; t++){
                for(z=j ; z<size+j ; z++){
                    sum+=matrix[t][z];
                    /* print submatrix */
                    printf("%3d", matrix[t][z]);
                }
                printf("\n");
            }
            /* print sum of each submatrix */
            printf("---------------\nSum: %d\n---------------\n", sum);
            if(sum>max_sum){
                max_sum=sum;
                for(t=i ; t<size+i ; t++)
                    for(z=j ; z<size+j ; z++)
                        maxsum_matrix[t-i][z-j]=matrix[t][z];
            }
        }
    }
    return max_sum;
}
