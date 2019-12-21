/*
=============================================================
Name        : laib_9_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_9 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "INVARRAY.h"
#include "PGLIST.h"
#include "PG.h"

#define DBG 0

typedef enum{
    c_addPg=1, c_removePg, c_searchPg, c_searchObj, c_editEquip, c_showStats, c_end=0
}command;

int main(){
    int cmd;            /* si sarebbe potuta usare, con lo stesso fine, il tipo command e creare una funzione che leggesse il comando */
    char code[7], name[MAX+1];
    pg_t *searchedPg;
    inv_t *searchedObj;
    ptr_invArray inventario=invIniz();
    ptr_pgList infolist=listIniz();

    #if DBG
    stampaInv(inventario);
    stampaPg(infolist);
    #endif // DBG

    do{
        printf("\t--------\n");
        printf("\t| MENU |\n");
        printf("\t--------\n");
        printf("---------------------------------------------------------------------\n");
        printf("1) AGGIUNGI PERSONAGGIO\n");
        printf("2) RIMUOVI PERSONAGGIO\n");
        printf("3) CERCA PERSONAGGIO PER CODICE\n");
        printf("4) CERCA OGGETTO PER NOME\n");
        printf("5) AGGIUNGI/RIMUOVI ELEMENTO DALL'EQUIPAGGIAMENTO DI UN PERSONAGGIO\n");
        printf("6) VISUALIZZA STATISTICHE DI TUTTI I PERSONAGGI\n");
        printf("0) ESCI\n");
        printf("---------------------------------------------------------------------\n\n");

        printf("Enter command:");
        scanf("%d", &cmd);
        fflush(stdin);              /* evito loop in caso di immissione letterale */

        switch(cmd){
            case c_addPg: infolist=addPgCMD(stdin, infolist);
                break;
            case c_removePg: infolist=removePgCMD(stdin, infolist);
                break;
            case c_searchPg:
                printf("Enter CODE to search: ");
                scanf("%s", code);
                searchedPg=searchPgCMD(infolist, code);
                if(searchedPg!=NULL){
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    printf("| %-7s  %-15s%-15s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\t|\n", "CODE", "NAME", "CLASS");
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    printPg(stdout, searchedPg);
                    printf("---------------------------------------------------------------------------------------------------------\n\n");
                }
                else{
                    printf("-----------------------------------\n");
                    printf("NO CHARACTER WITH CODE '%s'!\n", code);
                    printf("-----------------------------------\n\n");
                }
                break;
            case c_searchObj:
                printf("Enter NAME to search: ");
                scanf("%s", name);
                searchedObj=searchObjCMD(inventario, name);
                if(searchedObj!=NULL){
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    printf("| %-5s\t%-20s%-20s|\tHP\tMP\tATK\tDEF\tMAG\tSPR\t|\n", "ID", "NAME", "CLASS");
                    printf("---------------------------------------------------------------------------------------------------------\n");
                    printObj(stdout, searchedObj, 1);
                    printf("---------------------------------------------------------------------------------------------------------\n\n");
                }
                else{
                    printf("---------------------------------\n");
                    printf("NO OBJECT WITH CODE '%s'!\n", name);
                    printf("---------------------------------\n\n");
                }
                break;
            case c_editEquip:
                stampaPg(infolist, inventario);
                printf("Enter CODE of the character to edit: ");
                scanf("%s", code);
                searchedPg=searchPgCMD(infolist, code);
                if(searchedPg!=NULL)
                    editEquipCMD(searchedPg, inventario);
                else{
                    printf("--------------------------------\n");
                    printf("NO CHARACTER WITH CODE '%s'!\n", code);
                    printf("--------------------------------\n");
                }
                break;
            case c_showStats: stampaPg(infolist, inventario);
                break;
            case c_end:
                    printf("\nThanks for using this program!\nClosing in progress...");
                    return EXIT_SUCCESS;
                break;
            default:
                printf("Error: invalid command!\n");
        }
    }while(cmd!=c_end);

    return EXIT_SUCCESS;
}
