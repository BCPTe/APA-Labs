/*
=============================================================
Name        : laib_10_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_10 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "elementi.txt"
#define DBG 1

#define MAX 100
#define MAXRIGHE 3
#define MAXCOLONNE 5

float maxvalue=0;

typedef enum{TRANSITION, BACK, FORWARD}typology;
typedef enum{BACK_DIR, FRONT_DIR}dir;
typedef enum{FIRST, N_FIRST}prec_req;
typedef enum{N_LAST, LAST}final_req;

typedef struct{
    char name[MAX+1];
    typology type;
    dir in_direction, out_direction;
    prec_req p_requisite;
    final_req f_requisite;
    float value;
    int difficulty;
}element_s;

typedef struct{
    int DD, DP;
}limitations;

/* PROTOTYPES */
element_s *readfile(int *totItems);
void inizializer(int matrix[MAXRIGHE][MAXCOLONNE]);
void solve(element_s *list, int bestsol[MAXRIGHE][MAXCOLONNE], int totItems, limitations limits);
void solveR(int index_riga, int index_colonna, element_s *list, int sol[MAXRIGHE][MAXCOLONNE], int bestsol[MAXRIGHE][MAXCOLONNE], int n, limitations limits, int actDD, int actDP);
int checksol(element_s *list, int sol[MAXRIGHE][MAXCOLONNE]);
/* ---------- */

int main(){
    int totItems;
    int bestsol[MAXRIGHE][MAXCOLONNE];
    element_s *lis_elem=readfile(&totItems);
    limitations limits;
    inizializer(bestsol);

    printf("Enter DD and DP: ");
    scanf("%d%d", &limits.DD, &limits.DP);

    solve(lis_elem, bestsol, totItems, limits);
    printf("VALUE:%.3f!\n", maxvalue);
    for(int i=0 ; i<MAXRIGHE ; i++){
        printf("DIAG %d:\n", i+1);
        for(int j=0 ; j<MAXCOLONNE && bestsol[i][j]!=-1 ; j++)
            printf("%s %u %u %u %u %u %.2f %d\n", lis_elem[bestsol[i][j]].name, lis_elem[bestsol[i][j]].type, lis_elem[bestsol[i][j]].in_direction,
                    lis_elem[bestsol[i][j]].out_direction, lis_elem[bestsol[i][j]].p_requisite, lis_elem[bestsol[i][j]].f_requisite,
                    lis_elem[bestsol[i][j]].value, lis_elem[bestsol[i][j]].difficulty);
        printf("\n");
    }

    return EXIT_SUCCESS;
}

element_s *readfile(int *totItems){     /* leggo gli elementi */
    int i;
    element_s *tmp;
    FILE *fp=fopen(filename, "r");

    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    fscanf(fp, "%d", totItems);
    tmp=malloc((*totItems)*sizeof(element_s));
    for(i=0 ; i<(*totItems) ; i++)
        fscanf(fp, "%s %u%u%u%u%u %f %d\n", tmp[i].name, &tmp[i].type, &tmp[i].in_direction, &tmp[i].out_direction,
               &tmp[i].p_requisite, &tmp[i].f_requisite, &tmp[i].value, &tmp[i].difficulty);

    return tmp;
}

void inizializer(int matrix[MAXRIGHE][MAXCOLONNE]){     /* inizializza le matrici a -1 */
    int i, j;

    for(i=0 ; i<MAXRIGHE ; i++)
        for(j=0 ; j<MAXCOLONNE ; j++)
            matrix[i][j]=-1;

    return;
}

void solve(element_s *list, int bestsol[MAXRIGHE][MAXCOLONNE], int totItems, limitations limits){
    int sol[MAXRIGHE][MAXCOLONNE];
    inizializer(sol);

    solveR(0, 0, list, sol, bestsol, totItems, limits, 0, 0);

    return;
}

void solveR(int index_riga, int index_colonna, element_s *list, int sol[MAXRIGHE][MAXCOLONNE], int bestsol[MAXRIGHE][MAXCOLONNE], int n, limitations limits, int actDD, int actDP){
    int i, j;

    if(index_riga>=MAXRIGHE){               /* terminazione */
        if(checksol(list, sol)){
            for(i=0 ; i<MAXRIGHE ; i++)
                for(j=0 ; j<MAXCOLONNE ; j++)
                    bestsol[i][j]=sol[i][j];            /* copia sol->bestsol se checksol torna 1 */
        }
        return;
    }

    /* START RECURSIVE ALGORITHM */

    for(i=0 ; i<n ; i++){
        if(index_colonna==0 && (list[i].in_direction!=FRONT_DIR || list[i].p_requisite==N_FIRST))
            continue;
        if(index_colonna>0 && list[sol[index_riga][index_colonna-1]].out_direction!=list[i].in_direction)
            continue;
        if(list[i].difficulty+actDD>limits.DD || list[i].difficulty+actDP>limits.DP)
            continue;
        if(index_colonna>0 && list[sol[index_riga][index_colonna-1]].f_requisite==LAST)
            break;
        sol[index_riga][index_colonna]=i;
        solveR(index_riga, index_colonna+1, list, sol, bestsol, n, limits, actDD+list[i].difficulty, actDP+list[i].difficulty);
    }
    if(index_colonna>0){
        sol[index_riga][index_colonna]=-1;
        solveR(index_riga+1, 0, list, sol, bestsol, n, limits, 0, actDP);
    }

    return;
}

int checksol(element_s *list, int sol[MAXRIGHE][MAXCOLONNE]){               /* funzione di check secondo specifiche 1->VALIDA / 0->!VALIDA */
    int i, j, avanti=0, indietro=0, checkAvIn[2]={0}, checkAcrob2=0, bonus=0;
    float value=0.0, valdiag=0.0;

    for(i=0 ; i<MAXRIGHE ; i++){
        valdiag=0.0;
        indietro=avanti=0;
        for(j=0 ; j<MAXCOLONNE && sol[i][j]!=-1 ; j++){
            valdiag+=list[sol[i][j]].value;
            if(list[sol[i][j]].type==BACK){
                indietro=1;
                checkAvIn[0]=1;
            }
            else if(list[sol[i][j]].type==FORWARD){
                avanti=1;
                checkAvIn[1]=1;
            }
            if(j>0 && list[sol[i][j]].type!=TRANSITION)
                if(list[sol[i][j-1]].type!=TRANSITION) checkAcrob2=1;
            if(i==MAXRIGHE-1 && list[sol[i][j]].difficulty>=8)
                bonus=1;
        }
        if(!avanti && !indietro)
            return 0;
        if(bonus)
            valdiag*=1.5;
        value+=valdiag;
    }

    if(!checkAcrob2 || (!checkAvIn[0] && !checkAvIn[1]))
        return 0;

    if(value>maxvalue)
        maxvalue=value;
    else return 0;

    return 1;
}
