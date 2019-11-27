/*
=============================================================
Name        : laib_7_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_7 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

/*
N.B.:
    QUANDO VIENE STAMPATO IL NUMERO TOTALE DI COLLANE CREATE (riga 45) CI SI RIFERISCE A COLLANE DI LUNGHEZZA VARIABILE TRA 1 E total.tot!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define difstonesnumber 4
int actualmaxvalue=0;
int value=0;
int numZaf=0, numSme=0;

typedef struct{
    int zaffiri, smeraldi, rubini, topazi;
    int max_ripZ, max_ripS, max_ripR, max_ripT;
    int val_z, val_s, val_r, val_t;
    int tot;
}stones;

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int n, int consecutive, int *countersol);

int main(){
    int i, totalstones, countersol=0;
    char value[difstonesnumber+1]="zsrt";
    char *sol, *bestsol;
    stones numberstones;

    printf("Enter number of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.zaffiri, &numberstones.smeraldi, &numberstones.rubini, &numberstones.topazi);
    totalstones=numberstones.tot=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;
    printf("Enter value of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.val_z, &numberstones.val_s, &numberstones.val_r, &numberstones.val_t);
    printf("Enter max ripetitions of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.max_ripZ, &numberstones.max_ripS, &numberstones.max_ripR, &numberstones.max_ripT);

    sol=calloc(totalstones+1, sizeof(char));
    bestsol=calloc(totalstones+1, sizeof(char));
    createnecklace(0, value, sol, bestsol, numberstones, totalstones, 0, &countersol);

    printf("Total necklace created: %d!\n\n", countersol);
    printf("Best sol:\n");
    printf("---------------------------------------\n");
    for(i=0 ; i<strlen(bestsol)-1 ; i++)
        printf("%c-", toupper(bestsol[i]));
    printf("%c\n", toupper(bestsol[i]));
    printf("---------------------------------------\n");
    printf("VALUE: %d!\n", actualmaxvalue);
    printf("------------\n");

    return EXIT_SUCCESS;
}

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int n, int consecutive, int *countersol){
    int i;

    if(pos>=1 && pos<=n){
        for(i=pos-1 ; i<pos ; i++){
            if(sol[i]=='z')
                value+=total.val_z;
            else if(sol[i]=='s')
                value+=total.val_s;
            else if(sol[i]=='r')
                value+=total.val_r;
            else if(sol[i]=='t')
                value+=total.val_t;
        }
        if(value>actualmaxvalue && numZaf<=numSme){
            actualmaxvalue=value;
            strcpy(bestsol, sol);
        }
        (*countersol)++;
    }
    if(total.tot==0)
        return;

    for(i=0 ; i<strlen(val) ; i++){
        if(val[i]=='z' && total.zaffiri>0){
            if(sol[pos-1]!='z')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_ripZ)
                continue;
            total.zaffiri--; total.tot--;
            sol[pos]=val[i];
            numZaf++;
            createnecklace(pos+1, "zr", sol, bestsol, total, n, consecutive, countersol);
            total.zaffiri++; total.tot++;
            numZaf--;
            value-=total.val_z;
            sol[pos]='\0';
        }
        else if(val[i]=='s' && total.smeraldi>0){
            if(sol[pos-1]!='s')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_ripS)
                continue;
            total.smeraldi--; total.tot--;
            sol[pos]=val[i];
            numSme++;
            createnecklace(pos+1, "st", sol, bestsol, total, n, consecutive, countersol);
            total.smeraldi++; total.tot++;
            numSme--;
            value-=total.val_s;
            sol[pos]='\0';
        }
        else if(val[i]=='t' && total.topazi>0){
            if(sol[pos-1]!='t')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_ripT)
                continue;
            total.topazi--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "zr", sol, bestsol, total, n, consecutive, countersol);
            total.topazi++; total.tot++;
            value-=total.val_t;
            sol[pos]='\0';
        }
        else if(val[i]=='r' && total.rubini>0){
            if(sol[pos-1]!='r')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_ripR)
                continue;
            total.rubini--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "st", sol, bestsol, total, n, consecutive, countersol);
            total.rubini++; total.tot++;
            value-=total.val_r;
            sol[pos]='\0';
        }
    }
    return;
}
