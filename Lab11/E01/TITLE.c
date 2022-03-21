#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TITLE.h"
#include "QLIST.h"

struct title_s{
    char code[MAXC+1];
    QLIST dailyQTS;
};

TITLE TITLEread(FILE *fp){
    TITLE tmp=malloc(sizeof *tmp);

    fscanf(fp, "%s", tmp->code);
    tmp->dailyQTS=QLISTinit(fp);

    return tmp;
}

int TITLEcmp(TITLE t1, TITLE t2){
    return strcmp(t1->code, t2->code);
}

int TITLEcmp2(TITLE t1, char *toSearch){
    return strcmp(t1->code, toSearch);
}

void TITLEprint(TITLE x, int strategy){
    printf("%s\n", x->code);
    QLISTvisit(x->dailyQTS, strategy);

    return;
}

QLIST TITLEgetQTS(TITLE titolo){
    return titolo->dailyQTS;
}

float TITLEgetMAX(TITLE titolo){
    return QLISTgetMAX(titolo->dailyQTS);
}

float TITLEgetMIN(TITLE titolo){
    return QLISTgetMIN(titolo->dailyQTS);
}

int TITLEgetMAXheight(TITLE titolo){
    return QLISTgetMAXheight(titolo->dailyQTS);
}

int TITLEgetMINheight(TITLE titolo){
    return QLISTgetMINheight(titolo->dailyQTS);
}
