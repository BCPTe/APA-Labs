/*
=============================================================
Name        : laib_10_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_10 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define diffstonesnumber 4

typedef struct{
    int Z, R, S, T;
    int tot;
}gems;

/* PROTOTYPES */
int ****allocM(gems gemme);
void freeM(int ****matrix, gems gemme);
int calcMAX(int x, int y);
int solve(int ****Mz, int ****Mr, int ****Ms, int ****Mt, gems gemme);
int fZ(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t);
int fR(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t);
int fS(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t);
int fT(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t);
/* ---------- */

int main(){
    int ****Mz;
    int ****Mr;
    int ****Ms;
    int ****Mt;
    gems gemme;

    printf("Enter number of Z, R, S, T: ");
    scanf("%d%d%d%d", &gemme.Z, &gemme.R, &gemme.S, &gemme.T);
    gemme.tot=gemme.Z+gemme.R+gemme.S+gemme.T;

    Mz=allocM(gemme);
    Mr=allocM(gemme);
    Ms=allocM(gemme);
    Mt=allocM(gemme);

    printf("Collana di lunghezza massima: %d!\n", solve(Mz, Mr, Ms, Mt, gemme));

    freeM(Mz, gemme);
    freeM(Mr, gemme);
    freeM(Ms, gemme);
    freeM(Mt, gemme);

    return EXIT_SUCCESS;
}

int calcMAX(int x, int y){
    return (x>=y ? x : y);
}

int solve(int ****Mz, int ****Mr, int ****Ms, int ****Mt, gems gemme){
    int maxZ=fZ(Mz, Mr, Ms, Mt, gemme.Z, gemme.R, gemme.S, gemme.T);
    int maxR=fR(Mz, Mr, Ms, Mt, gemme.Z, gemme.R, gemme.S, gemme.T);
    int maxS=fS(Mz, Mr, Ms, Mt, gemme.Z, gemme.R, gemme.S, gemme.T);
    int maxT=fT(Mz, Mr, Ms, Mt, gemme.Z, gemme.R, gemme.S, gemme.T);

    return calcMAX(calcMAX(maxZ, maxR), calcMAX(maxS, maxT));
}

int fZ(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t){
    if(z==0) return 0;
    if(Mz[z][r][s][t]!=-1) return Mz[z][r][s][t];
    Mz[z][r][s][t]=1+calcMAX(fZ(Mz, Mr, Ms, Mt, z-1, r, s, t), fR(Mz, Mr, Ms, Mt, z-1, r, s, t));
    return Mz[z][r][s][t];
}

int fR(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t){
    if(r==0) return 0;
    if(Mr[z][r][s][t]!=-1) return Mr[z][r][s][t];
    Mr[z][r][s][t]=1+calcMAX(fS(Mz, Mr, Ms, Mt, z, r-1, s, t), fT(Mz, Mr, Ms, Mt, z, r-1, s, t));
    return Mr[z][r][s][t];
}

int fS(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t){
    if(s==0) return 0;
    if(Ms[z][r][s][t]!=-1) return Ms[z][r][s][t];
    Ms[z][r][s][t]=1+calcMAX(fS(Mz, Mr, Ms, Mt, z, r, s-1, t), fT(Mz, Mr, Ms, Mt, z, r, s-1, t));
    return Ms[z][r][s][t];
}

int fT(int ****Mz, int ****Mr, int ****Ms, int ****Mt, int z, int r, int s, int t){
    if(t==0) return 0;
    if(Mt[z][r][s][t]!=-1) return Mt[z][r][s][t];
    Mt[z][r][s][t]=1+calcMAX(fZ(Mz, Mr, Ms, Mt, z, r, s, t-1), fR(Mz, Mr, Ms, Mt, z, r, s, t-1));
    return Mt[z][r][s][t];
}

int ****allocM(gems gemme){
    int ****matrix;
    int h, i, j, k;

    matrix=malloc((gemme.Z+1)*sizeof(int ***));
    for(i=0 ; i<gemme.Z+1 ; i++){
        matrix[i]=malloc((gemme.R+1)*sizeof(int **));
        for(j=0 ; j<gemme.R+1 ; j++){
            matrix[i][j]=malloc((gemme.S+1)*sizeof(int *));
            for(k=0 ; k<gemme.S+1 ; k++){
                matrix[i][j][k]=malloc((gemme.T+1)*sizeof(int));
                for(h=0 ; h<gemme.T+1 ; h++)
                    matrix[i][j][k][h]=-1;
            }
        }
    }

    return matrix;
}

void freeM(int ****matrix, gems gemme){
    int i, j, k;

    for(i=0 ; i<gemme.Z ; i++){
        for(j=0 ; j<gemme.R ; j++){
            for(k=0 ; k<gemme.S ; k++){
                free(matrix[i][j][k]);
            }
            free(matrix[i][j]);
        }
        free(matrix[i]);
    }
    free(matrix);

    return;
}
