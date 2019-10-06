/*
=============================================================
Name        : laib_0_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_0 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define N 10

void readv(int vect[N]);
void print_subv(int vect[N]);

int main(void){
    int vect[N];

	readv(vect);
	print_subv(vect);

	return EXIT_SUCCESS;
}

void readv(int vect[N]){
	int i;

    fprintf(stdout, "Enter the elements of the vector detached by space: ");
	for(i=0 ; i<N ; i++)
		scanf("%d", &vect[i]);
}

void print_subv(int vect[N]){
    int i, j, cnt=0, max=0;

    for(i=0 ; i<N ; i++){
        if(vect[i]!=0){
            cnt++;
            if(cnt>max)
                max=cnt;
        }
        else
            cnt=0;
    }

    for(i=0 ; i<N ; i++){
        for(j=i ; vect[j]!=0 && j<N ; j++);
        if(j-i==max){
            printf("{ ");
            for( ; i<j ; i++)
                printf("%d ", vect[i]);
            printf("} ");
        }
    }
}
