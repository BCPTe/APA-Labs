/*
=============================================================
Name        : laib_6_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_6 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef enum{FALSE, TRUE}boolean;

typedef struct{
    int u, v;
}vertex_arc;

int powersetcreator(int pos, int *val, int *powset, int dx_ext, int count, vertex_arc *arcs, int n_arcs);
int checkfunction(int *powset, int *val, int dx_ext, vertex_arc *arcs, int n_arcs);

int main(){
    int i, dx_ext, n_arcs, v_cov;
    int *val, *powset;
    char filename[MAX+1];
    vertex_arc *arcs;
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    fscanf(fp, "%d%d\n", &dx_ext, &n_arcs);
    arcs=malloc(n_arcs*sizeof(vertex_arc));
    val=malloc(dx_ext*sizeof(int));
    powset=calloc(dx_ext, sizeof(int));

    for(i=0 ; i<n_arcs ; i++)
        fscanf(fp, "%d%d", &arcs[i].u, &arcs[i].v);
    for(i=0 ; i<dx_ext ; i++)
        val[i]=i;

    fclose(fp);

    v_cov=powersetcreator(0, val, powset, dx_ext, 0, arcs, n_arcs);
    printf("Found %d vertex cover!\n", v_cov);

    free(arcs);
    free(val);
    free(powset);

    return EXIT_SUCCESS;
}

int powersetcreator(int pos, int *val, int *powset, int dx_ext, int count, vertex_arc *arcs, int n_arcs){
    int i;

    if(pos>=dx_ext){
        if(checkfunction(powset, val, dx_ext, arcs, n_arcs)){
            printf("( ");
            for(i=0 ; i<pos ; i++)
                if(powset[i]!=0)
                    printf("%d ", val[i]);
            printf(")\n");
            return count+1;
        }
        return count;
    }

    powset[pos]=0;
    count=powersetcreator(pos+1, val, powset, dx_ext, count, arcs, n_arcs);
    powset[pos]=1;
    count=powersetcreator(pos+1, val, powset, dx_ext, count, arcs, n_arcs);

    return count;
}

int checkfunction(int *powset, int *val, int dx_ext, vertex_arc *arcs, int n_arcs){
    int i, j, counter=0;
    int *flag=calloc(dx_ext, sizeof(int));

    for(j=0 ; j<dx_ext ; j++){
        if(powset[j]!=0){
            for(i=0 ; i<n_arcs ; i++)
                if(flag[i]==0 && (arcs[i].u==val[j] || arcs[i].v==val[j])){
                    counter++;
                    flag[i]=1;
                }
        }
    }
    free(flag);

    if(counter>=n_arcs) return TRUE;
    return FALSE;
}
