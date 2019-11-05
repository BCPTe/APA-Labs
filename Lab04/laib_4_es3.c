/*
=============================================================
Name        : laib_4_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_4 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50
#define no_occ "NONE"

char *cercaRegexp(char *src, char *regexp);

int main(){
    char src[MAX+1], regexp[MAX+1];

    printf("Enter a string (max. 50 ch): ");
    scanf("%s", src);
    printf("Enter regexp: ");
    scanf("%s", regexp);

    printf("Occurence: %s\n", cercaRegexp(src, regexp));

    return EXIT_SUCCESS;
}

char *cercaRegexp(char *src, char *regexp){
    int i=0, j=0, k=0, found=0, flag=0;
    char *ptr=NULL;
    char line[MAX+1]={0};

    for(i=0 ; i<strlen(regexp) ; i++)
        line[i]=regexp[i];
    i=0;

    while(line[i]!='\0'){
        flag=0;
        if(line[i]=='.'){
            line[i]=src[i];
            if(strncmp(src, line, i+1)==0) found=1;
        }
        else if(line[i]=='['){
            j=i+1;
            while(line[j]!=']'){
                if(!flag)
                    line[i]=line[j];
                if(strncmp(src, line, i+1)==0) flag=1;
                j++;
            }
            if(flag){
                for(k=i+1 ; k<strlen(line) ; k++)
                    line[k]=line[++j];
            }
            i++;
        }
        else if(line[i]=='\\'){
            line[i]=src[i];
            if(line[i+1]=='a')
                line[i]=tolower(line[i]);
            else if(line[i+1]=='A')
                line[i]=toupper(line[i]);
            for(j=i+1 ; j<strlen(line) ; j++)
                line[j]=line[j+1];
            if(strncmp(src, line, i+1)==0) found=1;
        }
        i++;
    }

    if(found){
        ptr=strstr(src, line);
    }
    if(ptr!=NULL) return src;
    return no_occ;
}
