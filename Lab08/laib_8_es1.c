/*
=============================================================
Name        : laib_8_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_8 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "att.txt"
#define DBG 0

int actualmax=0;
int maxleng=0;

typedef struct{
    int t_start;
    int t_end;
    int diff;
}att;

int fill(att **vect);
void attSel(int N, att *v);
void attSel_R(int pos, att *val, att *sol, att *bestsol, int n, int k, int start);
int check(att *sol, int k);

int main(){
    int count;
    att *vector;

    count=fill(&vector);

    #if DBG
    for(int i=0 ; i<count ; i++)
        printf("%d %d %d\n", vector[i].t_start, vector[i].t_end, vector[i].diff);
    #endif // DBG

    attSel(count, vector);

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

void attSel(int N, att *v){             /* wrapper ricorsione */
    int i, count=0;
    att *sol=calloc(N, sizeof(att));
    att *bestsol=calloc(N, sizeof(att));

    for(i=N ; i>=0 && !count ; i--){
        attSel_R(0, v, sol, bestsol, N, i, 0);
    }
    printf("Best sol:\n");                  /* stampo la migliore (la prima delle migliori) soluzione risultante */
    for(i=0 ; i<maxleng ; i++)
        printf("(%d,%d)", bestsol[i].t_start, bestsol[i].t_end);
}

void attSel_R(int pos, att *val, att *sol, att *bestsol, int n, int k, int start){      /* genero powerset con modello combinazioni semplici */
    int i;

    if(pos>=k){
        if(check(sol, pos)){
            for(int j=0 ; j<pos ; j++)
                bestsol[j]=sol[j];
            maxleng=pos;
        }
        return;
    }
    for(i=start ; i<n ; i++){
        sol[pos]=val[i];
        attSel_R(pos+1, val, sol, bestsol, n, k, i+1);
    }

    return;
}

int check(att *sol, int k){
    int i, j, max=0;

    for(i=0 ; i<k ; i++){           /* verifico compatibilita' */
        for(j=i+1 ; j<k ; j++){
            if(sol[i].t_start<sol[j].t_end && sol[j].t_start<sol[i].t_end)
                return 0;
        }
    }

    for(i=0 ; i<k ; i++)        /* calcolo differenza */
        max+=sol[i].diff;
    if(max>actualmax){
        actualmax=max;
        return 1;
    }

    return 0;
}
