/*
=============================================================
Name        : laib_4_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_4 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b);

int main(){
    int a, b;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    printf("GCD: %d\n", gcd(a, b));

    return EXIT_SUCCESS;
}

int gcd(int a, int b){
    int tmp;

    /* swap a and b */
    if(b>a){
        tmp=a;
        a=b;
        b=tmp;
    }

    if(a==b) return a;          /* termination condition */

    if(!(a%2) && !(b%2)) return 2*gcd(a/2, b/2);        /* a even - b even */
    else if(a%2 && !(b%2)) return gcd(a, b/2);          /* a odd - b even */
    else if(a%2 && b%2) return gcd((a-b)/2, b);         /* a odd - b odd */
    else return gcd(a/2, b);                            /* a even - b odd */
}
