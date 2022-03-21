#include <stdio.h>
#include <stdlib.h>
#include "QUOTE.h"
#include "TIME.h"

QUOTE QUOTEread(FILE *fp){
    QUOTE tmp;

    tmp.time=TIMEread(fp);
    fscanf(fp, "%f%d\n", &tmp.value, &tmp.number);

    return tmp;
}

QUOTE QUOTEsetNULL(){
    QUOTE tmp;

    tmp.number=-1;
    tmp.value=-1;
    tmp.time=TIMEsetNULL();

    return tmp;
}

void QUOTEprint(QUOTE quote){
    TIMEprint(quote.time);
    printf("%.2f %d\n", quote.value, quote.number);

    return;
}
