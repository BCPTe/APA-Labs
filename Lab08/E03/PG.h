#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "INV.h"
#ifndef MAX
#define MAX 50
#endif // MAX

#define filename_pg "pg.txt"

typedef struct{
    int inUso;
    inv_t **vettEq;
}tabEquip_t;

typedef struct{
    char code[7], name[MAX+1], clas[MAX+1];
    int hp, mp, atk, def, mag, spr;
    tabEquip_t *equip;
}pg_t;

typedef struct nodoPg_t *link;
struct nodoPg_t{
    pg_t info;
    link next;
};

typedef struct{
    link headPg;
    link tailPg;
    int nPg;
}tabPg_t;

link newNode(pg_t val, link next);
link insInTail(tabPg_t *infolist, pg_t tmp);
void PgListIniz(tabPg_t *tabPg, tabInv_t *inventario);
link addPg(tabPg_t *infolist, tabInv_t *inventario);
link removePg(tabPg_t *infolist);
void searchPg(link head);
void editEquip(link head, tabInv_t *inventario);
void showStats(link head);

#endif // PG_H_INCLUDED
