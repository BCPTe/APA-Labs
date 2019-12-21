#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PG.h"
#include "PGLIST.h"
#include "EQUIPARRAY.h"

struct pgList_s{
    link head;
    int totPg;
};

struct nodoPg_t{
    pg_t info;
    link next;
};

ptr_pgList listIniz(){                          /* inizializzazione della lista personaggi */
    pg_t tmp;
    FILE *fp=fopen(filename_pg, "r");
    ptr_pgList x=malloc(sizeof *x);
    x->head=NULL;

    while(addPg(fp, &tmp)!=EXIT_FAILURE){
        x->head=insInTail(x->head, tmp);
        x->totPg++;
    }

    fclose(fp);
    return x;
}

ptr_pgList addPgCMD(FILE *fp, ptr_pgList infolist){             /* funzione di aggiunta personaggio */
    pg_t tmp;

    if(fp==stdin)
        printf("Enter info of the new character(s) and press CTRL+Z (<code><name><class><hp><mp><atk><def><mag><spr>):\n");
    while(fscanf(fp, "%s %s %s %d %d %d %d %d %d", tmp.code, tmp.name, tmp.clas,
                            &tmp.statPg.hp, &tmp.statPg.mp, &tmp.statPg.atk,
                            &tmp.statPg.def, &tmp.statPg.mag, &tmp.statPg.spr)!=EOF)
        infolist->head=insInTail(infolist->head, tmp);
    return infolist;
}

ptr_pgList removePgCMD(FILE *fp, ptr_pgList infolist){      /* funzione di rimozione personaggio */
    int found=0, headcheck=0;
    link p, x;
    char code[7];

    if(fp==stdin)
        printf("Enter code to remove: ");
    fscanf(fp, "%s", code);
    for(x=infolist->head, p=NULL ; x!=NULL && !found ; p=x, x=x->next){
        if(strcmp(code, x->info.code)==0){
            if(x==infolist->head){
                headcheck=1;
                infolist->head=x->next;
            }
            found=1;
            printf("---------------------------------------------------------------------------------------------------------\n");
            printf("| %-7s  %-15s%-15s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\t|\n", "CODE", "NAME", "CLASS");
            printf("---------------------------------------------------------------------------------------------------------\n");
            printPg(stdout, &x->info);
            printf("---------------------------------------------------------------------------------------------------------\n\n");
            if(!headcheck)
                p->next=x->next;
            free(x);
        }
    }
    if(!found){
        printf("-----------------------------------\n");
        printf("NO CHARACTER WITH CODE '%s'!\n", code);
        printf("-----------------------------------\n\n");
    }

    return infolist;
}

pg_t *searchPgCMD(ptr_pgList infolist, char *code){             /* funzione di ricerca ritornante un puntatore non nullo se trovato */
    link x;

    for(x=infolist->head ; x!=NULL ; x=x->next){
        if(strcmp(code, x->info.code)==0)
            return &(x->info);
    }

    return NULL;
}

link newNode(pg_t val, link next){
    link x=malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->info=val;
    x->next=next;
    x->info.actualEquip=equipIniz();

    return x;
}

link insInTail(link h, pg_t val){
    link x;
    if(h==NULL)
        return newNode(val, NULL);

    for(x=h ; x->next!=NULL ; x=x->next);
    x->next=newNode(val, NULL);

    return h;
}

void stampaPg(ptr_pgList infolist, ptr_invArray inventario){        /* funzione di stampa di tutti i personaggi */
    int i;
    inv_t tmp;
    link x;

    printf("---------------\n");
    printf("| PERSONAGGI: |\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("| %-7s  %-15s%-15s\t|\tHP\tMP\tATK\tDEF\tMAG\tSPR\t|\n", "CODE", "NAME", "CLASS");
    printf("---------------------------------------------------------------------------------------------------------\n");
    for(x=infolist->head ; x!=NULL ; x=x->next){
        printPg(stdout, &(x->info));
        if(getInUso(x->info.actualEquip)>0){
            printf("---------------------------------------------------------------------------------------------------------\n");
            for(i=0 ; i<getInUso(x->info.actualEquip) ; i++){
                tmp=getInv(inventario, getIndexArray(x->info.actualEquip, i));
                printObj(stdout, &tmp, i);
            }
            printf("---------------------------------------------------------------------------------------------------------\n");
        }
    }
    printf("---------------------------------------------------------------------------------------------------------\n\n");
}
