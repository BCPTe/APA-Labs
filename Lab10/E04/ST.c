#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

typedef struct{
    char *label;
    char *net;
}Item;

struct symboltable{
    Item *a;
    int maxN;
    int size;
};

ST STinit(int maxN){
    ST st=malloc(sizeof *st);

    st->a=malloc(maxN*sizeof(Item));
    for(int i=0 ; i<maxN ; i++){
        st->a[i].label=malloc((MAXC+1)*sizeof(char));
        st->a[i].label[0]='\0';
        st->a[i].net=malloc((MAXC+1)*sizeof(char));
        st->a[i].net[0]='\0';
    }
    st->maxN=maxN;
    st->size=0;

    return st;
}

void STfree(ST st){
    for(int i=0 ; i<st->maxN ; i++){
        free(st->a[i].label);
        free(st->a[i].net);
    }
    free(st->a);
    free(st);

    return;
}

int STcount(ST st){
    return st->size;
}

void STinsert(ST st, char *label, char *net){
    if(st->size==st->maxN){
        st->maxN*=2;
        st->a=realloc(st->a, st->maxN*sizeof(Item));
        for(int i=st->size ; i<st->maxN ; i++){
            st->a[i].label=malloc((MAXC+1)*sizeof(char));
            st->a[i].label[0]='\0';
            st->a[i].net=malloc((MAXC+1)*sizeof(char));
            st->a[i].net[0]='\0';
        }
    }
    strncpy(st->a[st->size].label, label, MAXC);
    strncpy(st->a[st->size].net, net, MAXC);
    st->size++;

    return;
}

int STsearch(ST st, char *toSearch){
    for(int i=0 ; i<st->size ; i++)
        if(strcmp(toSearch, st->a[i].label)==0)
            return i;

    return -1;
}

char *STsearchByIndex(ST st, int index){
    return st->a[index].label;
}
