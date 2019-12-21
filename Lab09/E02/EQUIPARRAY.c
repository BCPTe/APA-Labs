#include <stdio.h>
#include <stdlib.h>
#include "INVARRAY.h"
#include "EQUIPARRAY.h"

struct equipArray_s{
    int inUso;
    int vettEq[MAXEQUIP];
};

ptr_equipArray equipIniz(){                         /* inizializzazione dell'array */
    ptr_equipArray tmp=malloc(sizeof *tmp);
    tmp->inUso=0;
    return tmp;
}

int updateEquip(ptr_equipArray actual, int index){              /* funzione che modifica l'array di equipaggiamento */
    int remove=0;                                       /* possible return values: 11->removed -- 10->added -- 23->max reached */

    if(actual->inUso<MAXEQUIP){
        for(int i=0 ; i<actual->inUso ; i++){
            if(index==actual->vettEq[i]){
                actual->vettEq[i]=-1;
                for(int j=i+1 ; j<actual->inUso ; j++)              /* shift del vettore equip */
                    actual->vettEq[j-1]=actual->vettEq[j];
                actual->inUso--;
                return 11;
            }
        }
        if(!remove){
            actual->vettEq[actual->inUso++]=index;
            return 10;
        }
    }

    return 23;
}

int getInUso(ptr_equipArray actual){            /* funzione che ritorna il numero di equipaggiamenti totali attuali */
    return actual->inUso;
}

int getIndexArray(ptr_equipArray actual, int index){            /* funzione che ritorna l'index dell'oggetto nell'inventario */
    return actual->vettEq[index];
}

