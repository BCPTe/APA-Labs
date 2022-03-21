/*
=============================================================
Name        : laib_10_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_10 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "elementi.txt"

#define MAX 100
#define MAXELEM 5
#define MAXDIAG 3

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
    int sequence;
    int avanti, indietro;
}limitations;

/* PROTOTYPES */
element_s *readfile(int *totItems);
void inizializer(int matrix[MAXDIAG][MAXELEM]);
void MergeSort(element_s *list, int N);
void MergeSortR(element_s *list, element_s *B, int l, int r);
void Merge(element_s *list, element_s *B, int l, int q, int r);
void solveDiag(element_s *list, int *sol, int n, limitations *limits, int actDD, int *actDP, int DD, int DP);
int checksol(element_s *list, int sol[MAXDIAG][MAXELEM]);
/* ---------- */

int main(){
    int i, actDD=0, actDP=0, DD, DP, totItems;
    element_s *lis_elem=readfile(&totItems);
    int sol[MAXDIAG][MAXELEM];
    limitations limits={0};

    inizializer(sol);

    printf("Enter DD and DP: ");
    scanf("%d%d", &DD, &DP);

    MergeSort(lis_elem, totItems);
    for(i=0 ; i<MAXDIAG ; i++)
        solveDiag(lis_elem, sol[i], totItems, &limits, actDD, &actDP, DD, DP);

    if(checksol(lis_elem, sol)){
        printf("VALUE:%.3f!\n", maxvalue);
        for(int i=0 ; i<MAXDIAG ; i++){
            printf("DIAG %d:\n", i+1);
            for(int j=0 ; j<MAXELEM && sol[i][j]!=-1 ; j++)
                printf("%s %u %u %u %u %u %.2f %d\n", lis_elem[sol[i][j]].name, lis_elem[sol[i][j]].type, lis_elem[sol[i][j]].in_direction,
                        lis_elem[sol[i][j]].out_direction, lis_elem[sol[i][j]].p_requisite, lis_elem[sol[i][j]].f_requisite,
                        lis_elem[sol[i][j]].value, lis_elem[sol[i][j]].difficulty);
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}

void inizializer(int matrix[MAXDIAG][MAXELEM]){
    int i, j;

    for(i=0 ; i<MAXDIAG ; i++)
        for(j=0 ; j<MAXELEM ; j++)
            matrix[i][j]=-1;

    return;
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

void MergeSort(element_s *list, int N){
    int l=0, r=N-1;
    element_s *B=malloc(N*sizeof(element_s));
    MergeSortR(list, B, l, r);
}

void MergeSortR(element_s *list, element_s *B, int l, int r){
    int q=(l+r)/2;

    if(r<=l)
        return;

    MergeSortR(list, B, l, q);
    MergeSortR(list, B, q+1, r);
    Merge(list, B, l, q, r);
}

void Merge(element_s *list, element_s *B, int l, int q, int r){
    int i, j, k;
    i=l;
    j=q+1;

    for(k=l ; k<=r ; k++)
        if(i>q)
            B[k]=list[j++];
        else if(j>r)
            B[k]=list[i++];
        else if(list[i].value/list[i].difficulty<=list[j].value/list[j].difficulty)
            B[k]=list[i++];
        else
            B[k]=list[j++];
    for(k=l ; k<=r ; k++)
        list[k]=B[k];

    return;
}

void solveDiag(element_s *list, int *sol, int n, limitations *limits, int actDD, int *actDP, int DD, int DP){
    int i, pos=0;

    for(i=0 ; i<n ; i++){
        if(pos==0 && (list[i].p_requisite!=FIRST || list[i].in_direction!=FRONT_DIR))
            continue;
        if(pos>0 && list[sol[pos-1]].out_direction!=list[i].in_direction)
            continue;
        if(actDD+list[i].difficulty>DD || *actDP+list[i].difficulty>DP)
            continue;
        if((list[i].type==FORWARD && limits->avanti) || (list[i].type==BACK && limits->indietro))
            continue;
        sol[pos++]=i;
        actDD+=list[i].difficulty;
        *actDP+=list[i].difficulty;
        if(list[i].type==FORWARD)
            limits->avanti=1;
        else if(list[i].type==BACK)
            limits->indietro=1;
        if(pos==MAXELEM || list[i].f_requisite==LAST)
            return;
    }

    return;
}

int checksol(element_s *list, int sol[MAXDIAG][MAXELEM]){               /* funzione di check secondo specifiche 1->VALIDA / 0->!VALIDA */
    int i, j, avanti=0, indietro=0, checkAvIn[2]={0}, checkAcrob2=0, bonus=0;
    float value=0.0, valdiag=0.0;

    for(i=0 ; i<MAXDIAG ; i++){
        valdiag=0.0;
        indietro=avanti=0;
        for(j=0 ; j<MAXELEM && sol[i][j]!=-1 ; j++){
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
            if(i==MAXDIAG-1 && list[sol[i][j]].difficulty>=8)
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
