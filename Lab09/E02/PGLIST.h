#ifndef PGLIST_H_INCLUDED
#define PGLIST_H_INCLUDED

#include "PG.h"

typedef struct pgList_s *ptr_pgList;
typedef struct nodoPg_t *link;

ptr_pgList listIniz();
link newNode(pg_t val, link next);
ptr_pgList addPgCMD(FILE *fp, ptr_pgList infolist);
pg_t *searchPgCMD(ptr_pgList infolist, char *name);
ptr_pgList removePgCMD(FILE *fp, ptr_pgList infolist);
link insInTail(link h, pg_t val);
void stampaPg(ptr_pgList infolist, ptr_invArray inventario);

#endif // PGLIST_H_INCLUDED
