#ifndef QUOTE_H_INCLUDED
#define QUOTE_H_INCLUDED

#include "TIME.h"

typedef struct{
    TIME time;
    float value;
    int number;
}QUOTE;

QUOTE QUOTEread(FILE *fp);
QUOTE QUOTEsetNULL();
void QUOTEprint(QUOTE quote);

#endif // QUOTE_H_INCLUDED
