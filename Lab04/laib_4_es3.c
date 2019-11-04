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
    int i=0, j=0, pos=0;
    char *ptr;
    char line[MAX+1]={0};

    while(regexp[i]!='\0'){
        if(regexp[i]=='.'){
            if(i>0)
                strncpy(line, regexp, i);
            line[i]=src[i];
            strcat(line, regexp+i+1);
            ptr=strstr(src, line);
            if(ptr!=NULL) return ptr;
        }
        else if(regexp[i]=='['){
            j=i+1;
            if(i>0)
                strncpy(line, regexp, i);
            while(regexp[j]!=']'){
                line[i]=regexp[j];
                while(regexp[pos++]!=']');
                strcpy(line+i+1, regexp+pos);
                ptr=strstr(src, line);
                if(ptr!=NULL) return ptr;
                j++;
                pos=0;
            }
            i++;
        }
        else if(regexp[i]=='\\'){
            if(i>0)
                strncpy(line, regexp, i);
            line[i]=src[i];
            if(regexp[i+1]=='a')
                line[i]=tolower(line[i]);
            else if(regexp[i+1]=='A')
                line[i]=toupper(line[i]);
            strcat(line, regexp+i+2);
            ptr=strstr(src, line);
            if(ptr!=NULL) return ptr;
        }
        i++;
    }

    return no_occ;
}
