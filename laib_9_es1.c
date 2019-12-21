/*
=============================================================
Name        : laib_9_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_9 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "att.txt"

typedef struct{
    int t_start;
    int t_end;
    int diff;
}att;

int fill(att **vect);
void solve(att *vect, int n);
int check(att v1, att v2);
void dispSol(att *vect, int *P, int i);

int main(){
    int count;
    att *vector;

    count=fill(&vector);

    solve(vector, count);

    return EXIT_SUCCESS;
}

int fill(att **vect){
    int total;
    FILE *fp;

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    fscanf(fp, "%d", &total);
    *vect=malloc(total*sizeof(att));

    for(int i=0 ; i<total ; i++){                                        /* filling att vector */
        fscanf(fp, "%d%d", &(*vect)[i].t_start, &(*vect)[i].t_end);
        (*vect)[i].diff=(*vect)[i].t_end-(*vect)[i].t_start;
    }

    return total;
}

void solve(att *vect, int n){               /* similar to LIS - LONGEST INCREASING SUBSEQUENCE */
    int i, j, max, last=1, bestR=0;
    int L[n], P[n];

    L[0]=vect[0].diff; P[0]=-1;

    for(i=1 ; i<n ; i++){
        L[i]=vect[i].diff; P[i]=-1; max=0;
        for(j=0 ; j<i ; j++){
            if(check(vect[j], vect[i]) && L[j]>max){
                max=L[j];
                L[i]=L[j]+vect[i].diff;
                P[i]=j;
            }
        }
        if(bestR<L[i]){
            bestR=L[i];
            last=i;
        }
    }
    dispSol(vect, P, last);
}

int check(att v1, att v2){              /* compatibility check function */
    return v1.t_end<=v2.t_start;
}

void dispSol(att *vect, int *P, int i){             /* recursive display solution function */
    if(P[i]==-1){
        printf("(%d,%d)", vect[i].t_start, vect[i].t_end);
        return;
    }
    dispSol(vect, P, P[i]);
    printf("(%d,%d)", vect[i].t_start, vect[i].t_end);
}
