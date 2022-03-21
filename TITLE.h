#ifndef TITLE_H_INCLUDED
#define TITLE_H_INCLUDED

#include "QLIST.h"

#ifndef MAXC
#define MAXC 20
#endif // MAXC

typedef struct title_s *TITLE;

TITLE TITLEread(FILE *fp);
int TITLEcmp(TITLE t1, TITLE t2);
int TITLEcmp2(TITLE t1, char *toSearch);
void TITLEprint(TITLE x, int strategy);
QLIST TITLEgetQTS(TITLE titolo);
float TITLEgetMAX(TITLE titolo);
float TITLEgetMIN(TITLE titolo);
int TITLEgetMAXheight(TITLE titolo);
int TITLEgetMINheight(TITLE titolo);

#endif // TITLE_H_INCLUDED
