/*
=============================================================
Name        : laib_3_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_3 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

int checkBigEndian();
void stampaCodifica(void *p, int size, int bigEndian);

int main(){
    int bigEndian;
    float af;
    double ad;
    long double ald;

    bigEndian=checkBigEndian();

    printf("Enter a float, a double and a long double: ");
    scanf("%f %lf %Lf", &af, &ad, &ald);

    printf("\nTYPE\t\tBIT\tBYTE\n");
    printf("float\t\t%d\t%d\n", sizeof(af)*8, sizeof(af));
    printf("double\t\t%d\t%d\n", sizeof(ad)*8, sizeof(ad));
    printf("long double\t%d\t%d\n", sizeof(ald)*8, sizeof(ald));
    stampaCodifica((void *)&af, sizeof(af), bigEndian);
    stampaCodifica((void *)&ad, sizeof(ad), bigEndian);
    stampaCodifica((void *)&ald, sizeof(ald), bigEndian);

    return EXIT_SUCCESS;
}

int checkBigEndian(){
    int value=1;

    unsigned char *c=(unsigned char *)&value;
    if(c[0]==0) return 1;      //bigEndian
    else return 0;     //littleEndian
}

void stampaCodifica(void *p, int size, int bigEndian){
    int i, t=0, exp=0, step, start, end;
    unsigned char *pointer=(unsigned char *)p;

    if(size==16) size=10;

    switch(size){
        case 4:
            exp=8;
            break;
        case 8:
            exp=11;
            break;
        case 10:
            exp=15;
            break;
    }

    if(bigEndian){
        step=1;
        end=size;
        start=1;
    }
    else{
        step=-1;
        end=-1;
        start=size-1;
    }
    /* da completare */
}
