#include <stdio.h>
#include <stdlib.h>
#include "INV.h"
#include "PG.h"
#include "INVARRAY.h"
#include "EQUIPARRAY.h"

int addPg(FILE *fp, pg_t *ptr){
    int check1=fscanf(fp, "%s %s %s", ptr->code, ptr->name, ptr->clas);
    int check2=readStat(fp, &(ptr->statPg));
    ptr->eqStat=ptr->statPg;
    return ((check1==EOF || check2==EOF) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void printPg(FILE *fp, pg_t *ptr){
    fprintf(fp, "| %-7s  %-15s%-15s\t|", ptr->code, ptr->name, ptr->clas);
    printStatPg(fp, &ptr->eqStat);
}

void printStatPg(FILE *fp, stat_t *ptr){
    fprintf(fp, "\t%d\t%d\t%d\t%d\t%d\t%d\t|\n", ptr->hp, ptr->mp, ptr->atk, ptr->def, ptr->mag, ptr->spr);
}

void editEquipCMD(pg_t *searchedPg, ptr_invArray inventario){               /*funzione di modifica equip -- si appoggia ad */
    int i, index, check;                                            /* altre funzioni poiche' lavora con dati non di sua proprieta' */
    stat_t tmp;
    char name[7];
    inv_t *searchedObj;

    stampaInv(inventario);
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("\aN.B.: if the item is already equipped it will be automatically removed, otherwise it will be added!\n");
    printf("-----------------------------------------------------------------------------------------------------\n\n");
    printf("Enter NAME of the object to add/remove: ");
    scanf("%s", name);
    searchedObj=searchObjCMD(inventario, name);         /* ritorna il puntatore all'oggetto cercato per vedere se esiste */
    if(searchedObj!=NULL){
        index=getIndex(inventario, name);                        /* acquisisce l'indice dell'oggetto cercato */
        if(index!=-1){                                           /* se l'indice e' valido prosegue */
            check=updateEquip(searchedPg->actualEquip, index);          /* funzione che effettua l'equipaggiamento */
            if(check==10 || check==11){
                searchedPg->eqStat.hp=searchedPg->statPg.hp;
                searchedPg->eqStat.mp=searchedPg->statPg.mp;
                searchedPg->eqStat.atk=searchedPg->statPg.atk;
                searchedPg->eqStat.def=searchedPg->statPg.def;
                searchedPg->eqStat.mag=searchedPg->statPg.mag;
                searchedPg->eqStat.spr=searchedPg->statPg.spr;
                for(i=0 ; i<getInUso(searchedPg->actualEquip) ; i++){
                    tmp=getStat_index(inventario, getIndexArray(searchedPg->actualEquip, i));       /* funzione che prende le statistiche di */
                    searchedPg->eqStat.hp+=tmp.hp;                                              /* ogni oggetto equipaggiato per calcolare quella totale attuale */
                    searchedPg->eqStat.mp+=tmp.mp;
                    searchedPg->eqStat.atk+=tmp.atk;
                    searchedPg->eqStat.def+=tmp.def;
                    searchedPg->eqStat.mag+=tmp.mag;
                    searchedPg->eqStat.spr+=tmp.spr;
                }
                printf("------------------\n");
                printf("EQUIPMENT EDITED!\n");
                printf("------------------\n");
            }
            else if(check==23){
                printf("-------------------------------------\n");
                printf("MAXIMUM NUMBER OF EQUIPMENT REACHED!\n");
                printf("-------------------------------------\n");
            }
        }
    }
    else{
        printf("--------------------------------\n");
        printf("NO OBJECT WITH NAME '%s'!\n", name);
        printf("--------------------------------\n");
    }
}
