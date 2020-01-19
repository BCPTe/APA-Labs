#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

#ifndef MAXC
#define MAXC 30
#endif // MAXC

typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, char *label, char *net);
int STsearch(ST st, char *toSearch);
char *STsearchByIndex(ST st, int index);

#endif // ST_H_INCLUDED
