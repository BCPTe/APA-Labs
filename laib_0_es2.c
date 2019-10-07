/*
=============================================================
Name        : laib_0_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_0 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 20

int count(char line[N], int length);

int main(void){
    int i, length, totsubs=0;
    char filename[N+1], line[N];
    FILE *fp;

    /* ask user to enter filename */
    printf("Enter filename: ");
    scanf("%s", filename);

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    /* ask user to enter length substrings */
    printf("Insert length substrings: ");
    scanf("%d", &length);

    fscanf(fp, "%*d\n");
    while(fscanf(fp, "%s\n", line)!=EOF){
        for(i=0 ; line[i]!='\0' ; i++)
            line[i]=tolower(line[i]);
            /* cause in c 'A' != 'a' */
        totsubs+=count(line, length);
    }
    printf("Number of substrings: %d", totsubs);

    return EXIT_SUCCESS;
}

int count(char line[N], int length){
    int cnt=0, totsubs=0;
    int i, j;

    for(i=0 ; i<strlen(line)-length+1 ; i++){
        for(j=i ; j<i+length ; j++){
            if(line[j]=='a' || line[j]=='e' || line[j]=='i' || line[j]=='o' || line[j]=='u')
            cnt++;
        }
        if(cnt==2)
            totsubs++;
            /* if vowels are exactly 2, add 1 to the substring counter */
        cnt=0;
    }
    return totsubs;
}
