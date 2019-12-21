#ifndef PG_H_INCLUDED
#define PG_H_INCLUDED

#include "INV.h"
#include "INVARRAY.h"
#include "EQUIPARRAY.h"

#ifndef MAX
#define MAX 50
#endif // MAX

#define filename_pg "pg.txt"

typedef struct{
    char code[7], name[MAX+1], clas[MAX+1];
    stat_t statPg, eqStat;
    ptr_equipArray actualEquip;
}pg_t;

int addPg(FILE *fp, pg_t *ptr);
void printPg(FILE *fp, pg_t *ptr);
void printStatPg(FILE *fp, stat_t *ptr);
void editEquipCMD(pg_t *searchedPg, ptr_invArray inventario);

#endif // PG_H_INCLUDED
