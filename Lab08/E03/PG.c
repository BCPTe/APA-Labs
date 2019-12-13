#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PG.h"

link newNode(pg_t val, link next){
    link x=malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->info=val;
    x->next=next;
    return x;
}

link insInTail(tabPg_t *infolist, pg_t tmp){
    link x;

    if(infolist->headPg==NULL){
        infolist->nPg++;
        return newNode(tmp, NULL);
    }
    for(x=infolist->headPg ; x->next!=NULL ; x=x->next);       /* cerco ultimo nodo */
    x->next=infolist->tailPg=newNode(tmp, NULL);
    infolist->nPg++;
    return infolist->headPg;
}

void PgListIniz(tabPg_t *tabPg, tabInv_t *inventario){
    link x;
    FILE *fp;
    pg_t tmp;

    fp=fopen(filename_pg, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    while(fscanf(fp, "%s%s%s %d%d%d%d%d%d\n", tmp.code, tmp.name, tmp.clas, &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr)!=EOF)
        tabPg->headPg=insInTail(tabPg, tmp);

    for(x=tabPg->headPg ; x!=NULL ; x=x->next){
        x->info.equip=malloc(inventario->maxInv*sizeof(tabEquip_t));
        x->info.equip->inUso=0;
        for(int i=0 ; i<inventario->maxInv ; i++){
            x->info.equip->vettEq=malloc(inventario->maxInv*sizeof(inv_t *));
            x->info.equip->vettEq[i]=malloc(inventario->maxInv*sizeof(inv_t));
        }
    }

    fclose(fp);
}

link addPg(tabPg_t *infolist, tabInv_t *inventario){
    link x;
    pg_t tmp;

    printf("Enter info of the character to add (<code> <name> <clas> <hp> <mp> <atk> <def> <mag> <spr>):\n");
    scanf("%s %s %s %d %d %d %d %d %d", tmp.code, tmp.name, tmp.clas, &tmp.hp, &tmp.mp, &tmp.atk, &tmp.def, &tmp.mag, &tmp.spr);
    while(tmp.code[0]!='P' || tmp.code[1]!='G' || strlen(tmp.code)!=6){
        if(tmp.code[0]!='P' || tmp.code[1]!='G' || strlen(tmp.code)!=6)
            printf("Error: code must be in the form 'PGXXXX'! (X are numbers)\n");
        scanf("%s", tmp.code);
    }
    infolist->headPg=insInTail(infolist, tmp);
    for(x=infolist->headPg ; x->next!=NULL ; x=x->next);
    x->info.equip=malloc(inventario->maxInv*sizeof(tabEquip_t));
    x->info.equip->inUso=0;
    x->info.equip->vettEq=malloc(inventario->maxInv*sizeof(inv_t));

    return infolist->headPg;
}

link removePg(tabPg_t *infolist){
    int flag=0;
    char tmpCode[7];
    link x, p;

    printf("Enter code of the character to remove: ");
    scanf("%s", tmpCode);
    while(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6){
        if(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6)
            printf("Error: code must be in the form 'PGXXXX'! (X are numbers)\n");
        scanf("%s", tmpCode);
    }

    for(x=infolist->headPg, p=NULL ; x!=NULL ; p=x, x=x->next){
        if(strcmp(x->info.code, tmpCode)==0){
            flag=1;
            infolist->nPg--;
            printf("Character to remove:\n");
            printf("----------------------------------------\n");
            printf("%s\t%-15s%-15s\t\t---\t%d\t%d\t%d\t%d\t%d\t%d\n", x->info.code, x->info.name, x->info.clas,
                x->info.hp, x->info.mp, x->info.atk, x->info.def, x->info.mag, x->info.spr);
            printf("----------------------------------------\n\n");
            if(x==infolist->headPg)
                infolist->headPg=x->next;
            else if(x==infolist->tailPg)
                p->next=NULL;
            else
                p->next=x->next;
        }
    }

    if(!flag){
        printf("----------------------------------------\n");
        printf("NO CHARACTER WITH CODE %s!\n", tmpCode);
        printf("----------------------------------------\n\n");
    }
    return infolist->headPg;
}

void searchPg(link head){
    int i, found=0;
    char tmpCode[7];
    link x;

    for(x=head ; x!=NULL ; x=x->next){                          /* aggiorno le statistiche in base agli equipaggiamenti attuali */
        if(x->info.equip->inUso>0){
            for(int i=0 ; i<x->info.equip->inUso ; i++){
                x->info.atk+=x->info.equip->vettEq[i]->atkObj;
                if(x->info.atk<0)                                       /* le statistiche non possono essere negative */
                    x->info.atk=0;
                x->info.def+=x->info.equip->vettEq[i]->defObj;
                if(x->info.def<0)                                       /* le statistiche non possono essere negative */
                    x->info.def=0;
                x->info.hp+=x->info.equip->vettEq[i]->hpObj;
                if(x->info.hp<0)                                       /* le statistiche non possono essere negative */
                    x->info.hp=0;
                x->info.mag+=x->info.equip->vettEq[i]->magObj;
                if(x->info.mag<0)                                       /* le statistiche non possono essere negative */
                    x->info.mag=0;
                x->info.mp+=x->info.equip->vettEq[i]->mpObj;
                if(x->info.mp<0)                                       /* le statistiche non possono essere negative */
                    x->info.mp=0;
                x->info.spr+=x->info.equip->vettEq[i]->sprObj;
                if(x->info.spr<0)                                       /* le statistiche non possono essere negative */
                    x->info.spr=0;
            }
        }
    }

    printf("Enter code to be searched: ");
    scanf("%s", tmpCode);
    while(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6){
        if(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6)
            printf("Error: code must be in the form 'PGXXXX'! (X are numbers)\n");
        scanf("%s", tmpCode);
    }

    for(x=head ; x!=NULL && !found ; x=x->next){
        if(strcmp(x->info.code, tmpCode)==0){
            found=1;
            printf("\n%s\t%-20s%-20s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n", "CODE", "NAME", "CLASS");
            printf("-------------------------------------------------------------------------------------------------------------\n");
            printf("%s\t%-20s%-20s\t|\t%d\t%d\t%d\t%d\t%d\t%d\n", x->info.code, x->info.name, x->info.clas,
                   x->info.hp, x->info.mp, x->info.atk, x->info.def, x->info.mag, x->info.spr);
            printf("-------------------------------------------------------------------------------------------------------------\n");
            if(x->info.equip->inUso>0){
                printf("\t%-6s\t%-20s%-15s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n", "ID","NAME", "CLASS");
            }
            else{
                printf("ACTUALLY NO EQUIPMENT FOUND!\n");
                printf("-----------------------------\n\n");
            }
            for(i=0 ; i<x->info.equip->inUso ; i++){
                printf("\tEQ%04d\t%-20s%-15s\t|\t%+d\t%+d\t%+d\t%+d\t%+d\t%+d\n", i+1, x->info.equip->vettEq[i]->nameObj, x->info.equip->vettEq[i]->clasObj,
                        x->info.equip->vettEq[i]->hpObj, x->info.equip->vettEq[i]->mpObj, x->info.equip->vettEq[i]->atkObj,
                        x->info.equip->vettEq[i]->defObj, x->info.equip->vettEq[i]->magObj, x->info.equip->vettEq[i]->sprObj);
            }
            if(x->info.equip->inUso>0)
                printf("-------------------------------------------------------------------------------------------------------------\n\n");
        }
        else found=0;
    }
    if(!found){
        printf("\n---------------------------------\n");
        printf("NO CHARACTER WITH CODE '%s'!\n", tmpCode);
        printf("---------------------------------\n\n");
    }
}

void editEquip(link head, tabInv_t *inventario){
    int i, j, found=0, flag=0, remove=0, maxreached=0;
    char tmpCode[7], tmpName[MAX+1];
    link x;

    showStats(head);
    showObject(inventario);

    printf("Enter code of the character to edit: ");
    scanf("%s", tmpCode);
    while(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6){
        if(tmpCode[0]!='P' || tmpCode[1]!='G' || strlen(tmpCode)!=6)
            printf("Error: code must be in the form 'PGXXXX'! (X are numbers)\n");
        scanf("%s", tmpCode);
    }

    for(x=head ; x!=NULL && !flag && !remove && !maxreached ; x=x->next){
        if(strcmp(x->info.code, tmpCode)==0){
            found=1;
            printf("-----------------------------\n");
            printf("ACTUAL EQUIPMENT FOR '%s':\n", x->info.code);
            if(x->info.equip->inUso>0){
                for(i=0 ; i<x->info.equip->inUso ; i++){
                    printf("\n------------------------------------------------------------------------------------------------------\n");
                    printf("%-20s%-20s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n\n", "NAME", "CLASS");
                    printf("%-20s%-20s\t|\t%d\t%d\t%d\t%d\t%d\t%d\n", x->info.equip->vettEq[i]->nameObj, x->info.equip->vettEq[i]->clasObj,
                            x->info.equip->vettEq[i]->hpObj, x->info.equip->vettEq[i]->mpObj, x->info.equip->vettEq[i]->atkObj,
                            x->info.equip->vettEq[i]->defObj, x->info.equip->vettEq[i]->magObj, x->info.equip->vettEq[i]->sprObj);
                    printf("------------------------------------------------------------------------------------------------------\n\n");
                }
            }
            else{
                printf("----------------------\n");
                printf("ACTUALLY NO EQUIPMENT FOUND!\n");
                printf("----------------------\n\n");
            }
            printf("Enter name of the object to add/remove: ");
            scanf("%s", tmpName);
            for(i=0 ; i<inventario->nInv && !flag && !remove ; i++){
                if(x->info.equip->inUso>0){
                    for(j=0 ; j<x->info.equip->inUso && !remove && !flag && !maxreached ; j++){
                        if(strcmp(x->info.equip->vettEq[j]->nameObj, tmpName)==0){
                            remove=1;
                            x->info.equip->vettEq[j]=NULL;
                            x->info.equip->inUso--;
                            printf("--------------------------------------------\n");
                            printf("THE CHARACTER'S EQUIPMENT WAS REMOVED!\n");
                            printf("--------------------------------------------\n\n");
                        }
                    }
                }
                if(strcmp(inventario->vettInv[i].nameObj, tmpName)==0 && !remove && !maxreached && (x->info.equip->inUso)<(inventario->maxInv)){
                    flag=1;
                    x->info.equip->vettEq[x->info.equip->inUso]=&(inventario->vettInv[i]);
                    x->info.equip->inUso++;
                    printf("--------------------------------------------\n");
                    printf("THE CHARACTER'S EQUIPMENT WAS PERFORMED!\n");
                    printf("--------------------------------------------\n\n");
                }
            }
        }
        else found=0;
        if((x->info.equip->inUso)>=(inventario->maxInv) && !remove && !flag){
            maxreached=1;
            printf("---------------------------------------------\n");
            printf("ERROR: MAXIMUM NUMBER OF EQUIPMENT REACHED!\n");
            printf("---------------------------------------------\n\n");
        }
    }
    if(!found){
        printf("-----------------------------\n");
        printf("NO CHARACTER WITH CODE '%s'!\n", tmpCode);
        printf("-----------------------------\n");
    }
    if(found && !flag && !remove && !maxreached){
        printf("----------------------------\n");
        printf("EQUIPMENT '%s' NOT FOUND!\n", tmpName);
        printf("----------------------------\n\n");
    }
}

void showStats(link head){
    int i;
    link x;

    for(x=head ; x!=NULL ; x=x->next){                          /* aggiorno le statistiche in base agli equipaggiamenti attuali */
        if(x->info.equip->inUso>0){
            for(int i=0 ; i<x->info.equip->inUso ; i++){
                x->info.atk+=x->info.equip->vettEq[i]->atkObj;
                if(x->info.atk<0)                                       /* le statistiche non possono essere negative */
                    x->info.atk=0;
                x->info.def+=x->info.equip->vettEq[i]->defObj;
                if(x->info.def<0)                                       /* le statistiche non possono essere negative */
                    x->info.def=0;
                x->info.hp+=x->info.equip->vettEq[i]->hpObj;
                if(x->info.hp<0)                                       /* le statistiche non possono essere negative */
                    x->info.hp=0;
                x->info.mag+=x->info.equip->vettEq[i]->magObj;
                if(x->info.mag<0)                                       /* le statistiche non possono essere negative */
                    x->info.mag=0;
                x->info.mp+=x->info.equip->vettEq[i]->mpObj;
                if(x->info.mp<0)                                       /* le statistiche non possono essere negative */
                    x->info.mp=0;
                x->info.spr+=x->info.equip->vettEq[i]->sprObj;
                if(x->info.spr<0)                                       /* le statistiche non possono essere negative */
                    x->info.spr=0;
            }
        }
    }

    printf("\n-----------------------\n");
    printf("\tALL CHARACTERS:");
    printf("\n-------------------------------------------------------------------------------------------------------------\n");
    printf("%s\t%-20s%-20s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n\n", "CODE", "NAME", "CLASS");
    for(x=head ; x!=NULL ; x=x->next){
            printf("%s\t%-20s%-20s\t|\t%d\t%d\t%d\t%d\t%d\t%d\n", x->info.code, x->info.name, x->info.clas,
                   x->info.hp, x->info.mp, x->info.atk, x->info.def, x->info.mag, x->info.spr);
        if(x->info.equip->inUso>0){
            printf("-------------------------------------------------------------------------------------------------------------\n");
            printf("\t%-6s\t%-20s%-15s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\n", "ID","NAME", "CLASS");
        }
        for(i=0 ; i<x->info.equip->inUso ; i++){
            printf("\tEQ%04d\t%-20s%-15s\t|\t%+d\t%+d\t%+d\t%+d\t%+d\t%+d\n", i+1, x->info.equip->vettEq[i]->nameObj, x->info.equip->vettEq[i]->clasObj,
                    x->info.equip->vettEq[i]->hpObj, x->info.equip->vettEq[i]->mpObj, x->info.equip->vettEq[i]->atkObj,
                   x->info.equip->vettEq[i]->defObj, x->info.equip->vettEq[i]->magObj, x->info.equip->vettEq[i]->sprObj);
        }
        if(x->info.equip->inUso>0)
            printf("-------------------------------------------------------------------------------------------------------------\n");
    }
    printf("-------------------------------------------------------------------------------------------------------------\n\n");

    for(x=head ; x!=NULL ; x=x->next){                      /* azzero nuovamente le statistiche */
        if(x->info.equip->inUso>0){
            for(int i=0 ; i<x->info.equip->inUso ; i++){
                x->info.atk-=x->info.equip->vettEq[i]->atkObj;
                x->info.def-=x->info.equip->vettEq[i]->defObj;
                x->info.hp-=x->info.equip->vettEq[i]->hpObj;
                x->info.mag-=x->info.equip->vettEq[i]->magObj;
                x->info.mp-=x->info.equip->vettEq[i]->mpObj;
                x->info.spr-=x->info.equip->vettEq[i]->sprObj;
            }
        }
    }
}
