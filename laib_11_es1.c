/*
=============================================================
Name        : laib_11_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_11 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "TLIST.h"
#include "QLIST.h"
#include "TITLE.h"
#include "TIME.h"

#define filename "F3.txt"

int main(){
    int cmd, soglia;
    char code[MAXC+1];
    TIME data;
    TITLE titSearch;
    FILE *fp;
    TLIST titoli;

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    titoli=TLISTload(fp);

    do{
        printf("------------------------------------------------------\n");
        printf("\tMENU':\n");
        printf("1) STAMPA BST (check funzioni)\n");
        printf("2) RICERCA TITOLO CON CODICE\n");
        printf("3) RICERCA QUOTAZIONE DI UN TITOLO IN DETERMINATA DATA\n");
        printf("4) RICERCA MAX-MIN TRA DUE DATE\n");
        printf("5) RICERCA MAX-MIN ASSOLUTI\n");
        printf("6) BILANCIAMENTO ALBERO CON SOGLIA\n");
        printf("0) ESCI\n\n");

        printf("Enter command: ");
        scanf("%d", &cmd);

        switch(cmd){
            case 1:
                printf("-----------------\n");
                printf("STAMPA PREORDER:\n");
                printf("-----------------\n");
                TLISTprint(titoli, PREORDER);
                printf("-----------------\n");
                printf("STAMPA INORDER:\n");
                printf("-----------------\n");
                TLISTprint(titoli, INORDER);
                printf("-----------------\n");
                printf("STAMPA POSTORDER:\n");
                printf("-----------------\n");
                TLISTprint(titoli, POSTORDER);
                break;
            case 2:
                printf("Enter code to search: ");
                scanf("%s", code);
                titSearch=TLISTsearch(titoli, code);
                printf("\n------------------------------\n");
                if(titSearch!=NULL)
                    TITLEprint(titSearch, INORDER);
                else printf("TITLE NOT FOUND!\n");
                printf("------------------------------\n\n");
                break;
            case 3:
                printf("Enter code to search: ");
                scanf("%s", code);
                titSearch=TLISTsearch(titoli, code);
                if(titSearch==NULL){
                    printf("TITLE NOT FOUND\n");
                    break;
                }
                printf("Enter date: ");
                data=TIMEdataread(stdin);
                printf("\n------------------------------\n");
                QLISTsearch(TITLEgetQTS(titSearch), data);
                printf("------------------------------\n\n");
                break;
            case 4:
                break;
            case 5:
                printf("Enter code to search: ");
                scanf("%s", code);
                titSearch=TLISTsearch(titoli, code);
                if(titSearch==NULL){
                    printf("TITLE NOT FOUND\n");
                    break;
                }
                printf("--------------------------\n");
                printf("MAX: %.2f -- MIN: %.2f\n", TITLEgetMAX(titSearch), TITLEgetMIN(titSearch));
                printf("--------------------------\n\n");
                break;
            case 6:
                printf("Enter code to search: ");
                scanf("%s", code);
                titSearch=TLISTsearch(titoli, code);
                if(titSearch==NULL){
                    printf("TITLE NOT FOUND\n");
                    break;
                }
                printf("Cammino piu' lungo: %d\n", TITLEgetMAXheight(titSearch));
                printf("Cammino piu' corto: %d\n", TITLEgetMINheight(titSearch));
                printf("Enter SOGLIA: ");
                scanf("%d", &soglia);
                break;
            case 0:
                printf("Closing in progress...\n\n");
                break;
            default:
                printf("Invalid command!\n");
        }
    }while(cmd!=0);

    return EXIT_SUCCESS;
}
