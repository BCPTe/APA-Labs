/*
=============================================================
Name        : laib_2_es4.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_2 Exercise 4 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 30
#define MAX_F 15

void SelectionSort(int vect[MAX], int length);
void InsertionSort(int vect[MAX], int length);
void ShellSort(int vect[MAX], int length);

int main(){
    int i, j, tot_vect, length;
    int vect[MAX];
    char filename[MAX_F+1];
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    fscanf(fp, "%d\n", &tot_vect);
    for(i=0 ; i<tot_vect ; i++){
        fscanf(fp, "%d", &length);
        for(j=0 ; j<length ; j++)
            fscanf(fp, "%d", &vect[j]);
        printf("SELECTION SORT\n");
        SelectionSort(vect, length);
        printf("INSERTION SORT\n");
        InsertionSort(vect, length);
        printf("SHELL SORT\n");
        ShellSort(vect, length);
    }

    return EXIT_SUCCESS;
}

void SelectionSort(int vect[MAX], int length){
    int i, j, r=length-1, min, tmp, tot=0, cnt_ex=0;
    int cnt_int[MAX]={0};
    int tmp_vect[MAX]={0};

    for(i=0 ; i<length ; i++)
        tmp_vect[i]=vect[i];

    /* selection sort algorithm */
    for(i=0 ; i<r ; i++){
        tot++;
        min=i;
        for(j=i+1 ; j<=r ; j++){
            tot++;
            cnt_int[i]++;
            if(tmp_vect[j]<tmp_vect[min])
                min=j;
        }
        if(min!=i){
            cnt_ex++;
            tmp=tmp_vect[i];
            tmp_vect[i]=tmp_vect[min];
            tmp_vect[min]=tmp;
        }
    }

    printf("Vector in order: ");
    for(i=0 ; i<length ; i++)
        printf("%d ", tmp_vect[i]);
    printf("\n");
    for(i=0 ; i<r ; i++)
        printf("i=%d\t-->\titerations of internal cycle: %d\n", i, cnt_int[i]);
    printf("iterations of external cycle: %d\n", i);
    printf("exchanges: %d\n", cnt_ex);
    printf("total iterations: %d\n\n", tot);
}

void InsertionSort(int vect[MAX], int length){
    int i, j, r=length-1, x, tot=0, cnt_ex=0;
    int cnt_int[MAX]={0};
    int tmp_vect[MAX]={0};

    for(i=0 ; i<length ; i++)
        tmp_vect[i]=vect[i];

    /* insertion sort algorithm */
    for(i=0 ; i<=r ; i++){
        tot++;
        x=tmp_vect[i];
        j=i-1;
        while(j>=0 && x<tmp_vect[j]){
            tot++;
            cnt_ex++;
            cnt_int[i]++;
            tmp_vect[j+1]=tmp_vect[j];
            j--;
        }
        tmp_vect[j+1]=x;
    }

    printf("Vector in order: ");
    for(i=0 ; i<length ; i++)
        printf("%d ", tmp_vect[i]);
    printf("\n");
    for(i=0 ; i<=r ; i++)
        printf("i=%d\t-->\titerations of internal cycle: %d\n", i, cnt_int[i]);
    printf("iterations of external cycle: %d\n", i);
    printf("exchanges: %d\n", cnt_ex);
    printf("total iterations: %d\n\n", tot);
}

void ShellSort(int vect[MAX], int length){
    int i, j, r=length-1, h=1, tmp, tot=0, cnt_ex=0;
    int tmp_vect[MAX]={0};

    for(i=0 ; i<length ; i++)
        tmp_vect[i]=vect[i];

    /* shell sort algorithm */
    while(h<length/3)
        h=3*h+1;
    while(h>=1){
        tot++;
        for(i=h ; i<=r ; i++){
            tot++;
            j=i;
            tmp=tmp_vect[i];
            while(j>=h && tmp<tmp_vect[j-h]){
                tot++;
                cnt_ex++;
                tmp_vect[j]=tmp_vect[j-h];
                j-=h;
            }
            tmp_vect[j]=tmp;
        }
        h=h/3;
    }

    printf("Vector in order: ");
    for(i=0 ; i<length ; i++)
        printf("%d ", tmp_vect[i]);
    printf("\n");
    printf("exchanges: %d\n", cnt_ex);
    printf("total iterations: %d\n\n", tot);
}
