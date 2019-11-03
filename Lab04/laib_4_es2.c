/*
=============================================================
Name        : laib_4_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_4 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int majority(int *vect, int n);
int majorityR(int *vect, int l, int r);

int main(){
    int i, n;
    int vect[MAX];

    printf("Enter the number of elements (max. 20): ");
    scanf("%d", &n);
    printf("Enter the elements of the vector detached by space: ");
    for(i=0 ; i<n ; i++)
        scanf("%d", vect+i);

    printf("Majority element (-1 if doesn't exist): %d\n", majority(vect, n));

    return EXIT_SUCCESS;
}

int majority(int *vect, int n){
    return majorityR(vect, 0, n-1);
}

int majorityR(int *vect, int l, int r){
    int i, half=(l+r)/2, sx, dx, majsx=0, majdx=0;

    if(l==r) return vect[l];
    if(r-l==1){
        if(vect[l]==vect[r]) return vect[l];
        return -1;
    }
    sx=majorityR(vect, l, half);
    dx=majorityR(vect, half+1, r);
    for(i=l ; i<=r ; i++){
        if(vect[i]==sx) majsx++;
        if(vect[i]==dx) majdx++;
    }
    if(majsx>(r-l+1)/2) return sx;
    if(majdx>(r-l+1)/2) return dx;
    return -1;
}
