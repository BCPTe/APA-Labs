#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "INV.h"
#include "INVARRAY.h"

struct invArray_s{
    inv_t *objArray;
    int nObj, maxObj;
};

ptr_invArray invIniz(){                         /* inizializzazione array inventario */
    ptr_invArray ptr=malloc(sizeof *ptr);
    FILE *fp=fopen(filename_inv, "r");

    fscanf(fp, "%d", &(ptr->nObj));
    ptr->objArray=malloc(ptr->nObj*sizeof(inv_t));
    for(int i=0 ; i<ptr->nObj ; i++)
        addObj(fp, &(ptr->objArray[i]));
    ptr->maxObj=MAXEQUIP;

    fclose(fp);
    return ptr;
}

inv_t *searchObjCMD(ptr_invArray ptr, char *name){          /* funzione di ricerca oggetto con ritorno di pointer non nullo se presente */
    int i;

    for(i=0 ; i<ptr->nObj ; i++){
        if(strcmp(name, ptr->objArray[i].nameObj)==0)
            return &(ptr->objArray[i]);
    }

    return NULL;
}

int getIndex(ptr_invArray inventario, char *name){          /* ritorna l'indice dell'oggetto nell'inventario oppure un indice non valido */
    int i;

    for(i=0 ; i<inventario->nObj ; i++){
        if(strcmp(inventario->objArray[i].nameObj, name)==0)
            return i;
    }

    return -1;
}

stat_t getStat_index(ptr_invArray inventario, int index){           /* ritorna un puntatore a dato di tipo stat_t che poi verra' usato */
    stat_t tmp={0};                                               /* per calcolare le statistiche di un personaggio con equipaggiamento */

    if(index!=-1)
        return inventario->objArray[index].statObj;
    else return tmp;
}

inv_t getInv(ptr_invArray inventario, int index){
    return inventario->objArray[index];
}

void stampaInv(ptr_invArray ptr){               /* stampa di tutto l'inventario */
    printf("---------------\n");
    printf("| INVENTARIO: |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| %-5s\t%-20s%-20s|\tHP\tMP\tATK\tDEF\tMAG\tSPR\t|\n", "ID", "NAME", "CLASS");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for(int i=0 ; i<ptr->nObj ; i++){
        printObj(stdout, &ptr->objArray[i], i);
    }
    printf("---------------------------------------------------------------------------------------------------------\n\n");
}
