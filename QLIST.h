#ifndef QLIST_H_INCLUDED
#define QLIST_H_INCLUDED

#include "QUOTE.h"

typedef enum{PREORDER=-1, INORDER, POSTORDER}strat;
typedef struct qlist_s *QLIST;

QLIST QLISTinit(FILE *fp);
void QLISTinsert_leafR(QLIST tmp, QUOTE quote);
void QLISTvisit(QLIST bst, int strategy);
void QLISTsearch(QLIST qts, TIME data);
float QLISTgetMAX(QLIST qts);
float QLISTgetMIN(QLIST qts);
int QLISTgetMAXheight(QLIST qts);
int QLISTgetMINheight(QLIST qts);

#endif // QLIST_H_INCLUDED
