#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "INV.h"

tabInv_t *ObjIniz(tabInv_t *object){
    int i;
    FILE *fp;

    fp=fopen(filename_invent, "r");
        if(fp==NULL){
        /* if file doesn't exist exit with code error 98 */
        printf("Error: file doesn't exist!\n");
        exit(98);
    }

    fscanf(fp, "%d\n", &object->nInv);
    object->vettInv=malloc((object->nInv)*sizeof(inv_t));
    for(i=0 ; i<(object->nInv) ; i++)
        fscanf(fp, "%s%s %d%d%d%d%d%d", object->vettInv[i].nameObj, object->vettInv[i].clasObj,
               &object->vettInv[i].hpObj, &object->vettInv[i].mpObj, &object->vettInv[i].atkObj,
               &object->vettInv[i].defObj, &object->vettInv[i].magObj, &object->vettInv[i].sprObj);

    object->maxInv=MAXEQUIP;
    fclose(fp);
    return object;
}

void searchObj(tabInv_t *inventario){
    int found=0;
    char tmpName[MAX+1];

    printf("Enter name to be searched: ");
    scanf("%s", tmpName);
    for(int i=0 ; i<inventario->nInv && !found ; i++){
        if(strcmp(inventario->vettInv[i].nameObj, tmpName)==0){
            found=1;
            printf("\n----------------------------------------------------------------------------------------------------\n");
            printf("%-20s%-20s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n", "NAME", "CLASS");
            printf("----------------------------------------------------------------------------------------------------\n");
            printf("%-20s%-20s\t|\t%+d\t%+d\t%+d\t%+d\t%+d\t%+d\n", inventario->vettInv[i].nameObj, inventario->vettInv[i].clasObj,
                    inventario->vettInv[i].hpObj, inventario->vettInv[i].mpObj, inventario->vettInv[i].atkObj,
                    inventario->vettInv[i].defObj, inventario->vettInv[i].magObj, inventario->vettInv[i].sprObj);
            printf("----------------------------------------------------------------------------------------------------\n\n");
        }
        else found=0;
    }
    if(!found){
        printf("\n------------------------------------------\n");
        printf("NO OBJECT FOUND WITH NAME '%s'!\n", tmpName);
        printf("------------------------------------------\n\n");
    }
}

void showObject(tabInv_t *inventario){

    printf("\n--------------------\n");
    printf("\tALL OBJECTS:");
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("\t%-20s%-20s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n\n", "NAME", "CLASS");
    for(int i=0 ; i<inventario->nInv ; i++)
        printf("%06d\t%-20s%-20s\t|\t%+d\t%+d\t%+d\t%+d\t%+d\t%+d\n", i+1, inventario->vettInv[i].nameObj, inventario->vettInv[i].clasObj,
                inventario->vettInv[i].hpObj, inventario->vettInv[i].mpObj, inventario->vettInv[i].atkObj,
               inventario->vettInv[i].defObj, inventario->vettInv[i].magObj, inventario->vettInv[i].sprObj);
    printf("-------------------------------------------------------------------------------------------------------------\n\n");
}
