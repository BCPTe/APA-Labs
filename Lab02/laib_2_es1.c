/*
=============================================================
Name        : laib_2_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_2 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
#define MAX_M 50

typedef struct{
    int extreme[2];     /* left-corner coordinates */
    int dims[2];      /* dims[0]=length ; dims[1]=height */
    int area;
}submatrix;

void verify(FILE *fp, int matrix[MAX_M][MAX_M], int nr, int nc);

int main(){
    int i, j, nr, nc;
    int matrix[MAX_M][MAX_M]={0};
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
        fscanf(fp, "%d %d", &nr, &nc);
        for(i=0 ; i<nr ; i++){
            for(j=0 ; j<nc ; j++){
                fscanf(fp, "%d", &matrix[i][j]);
                printf("%3d", matrix[i][j]);
            }
            printf("\n");
        }
    }

    verify(fp, matrix, nr, nc);
    
    fclose(fp);

    return EXIT_SUCCESS;
}

void verify(FILE *fp, int matrix[MAX_M][MAX_M], int nr, int nc){
    int i, j, t, z, area=0;
    submatrix max_length={0}, max_height={0}, max_area={0};

    for(i=0 ; i<nr ; i++){
        for(j=0 ; j<nc ; j++){
            if(matrix[i][j]){
                for(t=i ; matrix[t][j] && t<nr ; t++)
                    for(z=j ; matrix[t][z] && z<nc ; z++);
                area=(z-j)*(t-i);
                if(z-j>max_length.dims[0]){
                    max_length.dims[0]=z-j; max_length.dims[1]=t-i;
                    max_length.extreme[0]=i; max_length.extreme[1]=j;
                    max_length.area=area;
                }
                if(t-i>max_height.dims[1]){
                    max_height.dims[0]=z-j; max_height.dims[1]=t-i;
                    max_height.extreme[0]=i; max_height.extreme[1]=j;
                    max_height.area=area;
                }
                if(area>max_area.area){
                    max_area.dims[0]=z-j; max_area.dims[1]=t-i;
                    max_area.extreme[0]=i; max_area.extreme[1]=j;
                    max_area.area=area;
                }
            }
        }
    }
    printf("max length: extreme upper <%d,%d>, length=%d, height=%d, area: %d\n", max_length.extreme[0], max_length.extreme[1], max_length.dims[0], max_length.dims[1],  max_length.area);
    printf("max height: extreme upper <%d,%d>, length=%d, height=%d, area: %d\n", max_height.extreme[0], max_height.extreme[1], max_height.dims[0], max_height.dims[1], max_height.area);
    printf("max area: extreme upper <%d,%d>, length=%d, height=%d, area: %d\n", max_area.extreme[0], max_area.extreme[1], max_area.dims[0], max_area.dims[1], max_area.area);
}
