/*
=============================================================
Name        : laib_0_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_0 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define maxN 30

void rotation(int vect[maxN], int N, int P, int dir);

int main(){
    int i, N, P, dir;
    int vect[maxN]={0};

    do{
        printf("Enter the number of elements (max. 30): ");
        scanf("%d", &N);
        if(N>maxN)
            printf("Error: max number of elements is 30!\n");
    }while(N>maxN);

    printf("Enter the elements of the vector detached by space: ");
    for(i=0 ; i<N ; i++)
        scanf("%d", &vect[i]);
    fflush(stdin);

    do{
        do{
            printf("Enter the number of positions to shift (0 to exit): ");
            scanf("%d", &P);
            if(P>N)
                printf("Error: number of positions bigger than number of elements!\n");
        }while(P>N);

        if(P!=0){
            printf("Enter the direction (-1 for a right-shift / 1 for a left-shift): ");
            scanf("%d", &dir);

            rotation(vect, N, P, dir);

            printf("Vector shifted:\n");
            for(i=0 ; i<N ; i++)
                printf("%d ", vect[i]);
            printf("\n");
        }
    }while(P!=0);

    return EXIT_SUCCESS;
}

void rotation(int vect[maxN], int N, int P, int dir){
    int i, j, temp=0;

    if(dir==1){
        /* left-shift */
        for(j=0 ; j<P ; j++){
            temp=vect[0];
            for(i=0 ; i<N-1 ; i++)
                vect[i]=vect[i+1];
            vect[N-1]=temp;
        }
    }
    else if(dir==-1){
        /* right-shift */
        for(j=0 ; j<P ; j++){
            temp=vect[N-1];
            for(i=N-1 ; i>0 ; i--)
                vect[i]=vect[i-1];
            vect[0]=temp;
        }
    }
}
