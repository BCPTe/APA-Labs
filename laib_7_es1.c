/*
=============================================================
Name        : laib_X_esX.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_X Exercise X - APA 19/20 PoliTO
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
int actualmax=0;

typedef struct{
    int zaffiri, smeraldi, rubini, topazi;
    int tot;
}stones;

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int n, int *countersol);

int main(){
    int i, totalstones, countersol=0;
    char value[difstonesnumber+1]="zsrt";
    char *sol, *bestsol;
    stones numberstones;

    printf("Enter number of sapphires, emeralds, rubies, topaz: ");
    scanf("%d%d%d%d", &numberstones.zaffiri, &numberstones.smeraldi, &numberstones.rubini, &numberstones.topazi);
    totalstones=numberstones.tot=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;

    sol=calloc(totalstones, sizeof(char));
    bestsol=calloc(totalstones, sizeof(char));
    createnecklace(0, value, sol, bestsol, numberstones, totalstones, &countersol);

    printf("Total necklace created: %d!\n\n", countersol);
    printf("Best sol:\n");
    printf("---------------------------------------\n");
    for(i=0 ; i<actualmax-1 ; i++)
        printf("%c-", toupper(bestsol[i]));
    printf("%c\n", toupper(bestsol[i]));
    printf("---------------------------------------\n");
    printf("LENGTH: %d!\n", actualmax);
    printf("------------\n");

    return EXIT_SUCCESS;
}

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int n, int *countersol){
    int i;

    if(pos>=1 && pos<=n){
        if(pos>actualmax){
            actualmax=pos;
            strcpy(bestsol, sol);
        }
        (*countersol)++;
    }
    if(total.tot==0){
        return;
    }
    for(i=0 ; i<strlen(val) ; i++){
        if(val[i]=='z' && total.zaffiri>0){
            total.zaffiri--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "zr", sol, bestsol, total, n, countersol);
            total.zaffiri++; total.tot++;
            sol[pos]='\0';
        }
        else if(val[i]=='s' && total.smeraldi>0){
            total.smeraldi--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "st", sol, bestsol, total, n, countersol);
            total.smeraldi++; total.tot++;
            sol[pos]='\0';
        }
        else if(val[i]=='t' && total.topazi>0){
            total.topazi--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "zr", sol, bestsol, total, n, countersol);
            total.topazi++; total.tot++;
            sol[pos]='\0';
        }
        else if(val[i]=='r' && total.rubini>0){
            total.rubini--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "st", sol, bestsol, total, n, countersol);
            total.rubini++; total.tot++;
            sol[pos]='\0';
        }
    }
    return;
}
