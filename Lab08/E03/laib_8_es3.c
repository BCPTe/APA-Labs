/*
=============================================================
Name        : laib_8_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_8 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "INV.h"
#include "PG.h"

typedef enum{
    c_addPg=1, c_removePg, c_searchPg, c_searchObj, c_editEquip, c_showStats, c_end=0
}command;

int main(){
    int cmd;            /* si sarebbe potuta usare, con lo stesso fine, il tipo command e creare una funzione che leggesse il comando */
    tabInv_t object_t={0};
    tabInv_t *tabInv=&object_t;
    tabPg_t infolist={0};
    tabPg_t *tabPg=&infolist;

    tabInv=ObjIniz(tabInv);
    PgListIniz(tabPg, tabInv);

    do{
        printf("\tMENU'\n");
        printf("1) AGGIUNGI PERSONAGGIO\n");
        printf("2) RIMUOVI PERSONAGGIO\n");
        printf("3) CERCA PERSONAGGIO PER CODICE\n");
        printf("4) CERCA OGGETTO PER NOME\n");
        printf("5) AGGIUNGI/RIMUOVI ELEMENTO DALL'EQUIPAGGIAMENTO DI UN PERSONAGGIO\n");
        printf("6) VISUALIZZA STATISTICHE DI TUTTI I PERSONAGGI\n");
        printf("0) ESCI\n\n");

        printf("Enter command:");
        scanf("%d", &cmd);

        switch(cmd){
            case c_addPg: tabPg->headPg=addPg(tabPg, tabInv);
                break;
            case c_removePg: tabPg->headPg=removePg(tabPg);
                break;
            case c_searchPg: searchPg(tabPg->headPg);
                break;
            case c_searchObj: searchObj(tabInv);
                break;
            case c_editEquip: editEquip(tabPg->headPg, tabInv);
                break;
            case c_showStats: showStats(tabPg->headPg);
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
