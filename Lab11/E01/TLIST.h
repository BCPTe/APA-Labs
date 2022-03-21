#ifndef TLIST_H_INCLUDED
#define TLIST_H_INCLUDED

#include "TITLE.h"

#ifndef MAXC
#define MAXC 20
#endif // MAXC

typedef struct tlist_s *TLIST;

TLIST TLISTinit();
TLIST TLISTload(FILE *fp);
void TLISTprint(TLIST titoli, int strategy);
TITLE TLISTsearch(TLIST titoli, char *toSearch);

#endif // TLIST_H_INCLUDED
