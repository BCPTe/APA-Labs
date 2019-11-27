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
      'int consecutive' permette di evitare la consecuzione di più pietre secondo le specifiche dell'utente all'avvio del programma!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define difstonesnumber 4
int actualmaxvalue=0;
int value=0;
int numZaf=0, numSme=0;

typedef struct{
    int zaffiri, smeraldi, rubini, topazi;
    int max_rip;
    int val_z, val_s, val_r, val_t;
    int tot;
}stones;

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int consecutive);

int main(){
    int i;
    char value[difstonesnumber+1]="ZRST";
    char *sol, *bestsol;
    stones numberstones;

    printf("Enter number of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.zaffiri, &numberstones.smeraldi, &numberstones.rubini, &numberstones.topazi);
    numberstones.tot=numberstones.zaffiri+numberstones.smeraldi+numberstones.rubini+numberstones.topazi;
    printf("Enter value of ZAFFIRI, SMERALDI, RUBINI, TOPAZI: ");
    scanf("%d%d%d%d", &numberstones.val_z, &numberstones.val_s, &numberstones.val_r, &numberstones.val_t);
    printf("Enter max ripetitions: ");
    scanf("%d", &numberstones.max_rip);

    sol=calloc(numberstones.tot+1, sizeof(char));
    bestsol=calloc(numberstones.tot+1, sizeof(char));
    createnecklace(0, value, sol, bestsol, numberstones, 0);

    printf("\nTotal stones used: %d!\n", strlen(bestsol));
    printf("Best sol:\n");
    printf("---------------------------------------\n");
    for(i=0 ; i<strlen(bestsol)-1 ; i++)
        printf("%c-", bestsol[i]);
    printf("%c\n", bestsol[i]);
    printf("---------------------------------------\n");
    printf("VALUE: %d!\n", actualmaxvalue);
    printf("------------\n");

    return EXIT_SUCCESS;
}

void createnecklace(int pos, char *val, char *sol, char *bestsol, stones total, int consecutive){
    int i;

    if(pos>=1){
        for(i=pos-1 ; i<pos ; i++){         /* calcolo l'attuale valore della soluzione */
            if(sol[i]=='Z')
                value+=total.val_z;
            else if(sol[i]=='S')
                value+=total.val_s;
            else if(sol[i]=='R')
                value+=total.val_r;
            else if(sol[i]=='T')
                value+=total.val_t;
        }
        if(value>actualmaxvalue && numZaf<=numSme){     /* verifico che il valore sia > di quello attuale e che numZaf<numSme come da specifica*/
            actualmaxvalue=value;
            strcpy(bestsol, sol);
        }
    }
    if(total.tot==0)
        return;

    for(i=0 ; i<strlen(val) ; i++){                 /* INIZIO ALGORITMO RICORSIVO */
        if(val[i]=='Z' && total.zaffiri>0){
            if(sol[pos-1]!='Z')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_rip)
                continue;
            total.zaffiri--; total.tot--;
            sol[pos]=val[i];
            numZaf++;
            createnecklace(pos+1, "ZR", sol, bestsol, total, consecutive);
            total.zaffiri++; total.tot++;               /* BACKTRACK */
            numZaf--;
            value-=total.val_z;
            sol[pos]='\0';
        }
        else if(val[i]=='S' && total.smeraldi>0){
            if(sol[pos-1]!='S')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_rip)
                continue;
            total.smeraldi--; total.tot--;
            sol[pos]=val[i];
            numSme++;
            createnecklace(pos+1, "ST", sol, bestsol, total, consecutive);
            total.smeraldi++; total.tot++;              /* BACKTRACK */
            numSme--;
            value-=total.val_s;
            sol[pos]='\0';
        }
        else if(val[i]=='T' && total.topazi>0){
            if(sol[pos-1]!='T')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_rip)
                continue;
            total.topazi--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "ZR", sol, bestsol, total, consecutive);
            total.topazi++; total.tot++;                /* BACKTRACK */
            value-=total.val_t;
            sol[pos]='\0';
        }
        else if(val[i]=='R' && total.rubini>0){
            if(sol[pos-1]!='R')
                consecutive=0;
            consecutive++;
            if(consecutive>total.max_rip)
                continue;
            total.rubini--; total.tot--;
            sol[pos]=val[i];
            createnecklace(pos+1, "ST", sol, bestsol, total, consecutive);
            total.rubini++; total.tot++;                /* BACKTRACK */
            value-=total.val_r;
            sol[pos]='\0';
        }
    }
    return;
}
