#include <stdio.h>
#include <stdlib.h>
#include "TIME.h"

TIME TIMEread(FILE *fp){
    TIME tmp;

    fscanf(fp, "%d/%d/%d %d:%d\n", &tmp.year, &tmp.month, &tmp.day, &tmp.hh, &tmp.mm);

    return tmp;
}

TIME TIMEdataread(FILE *fp){
    TIME tmp;

    fscanf(fp, "%d/%d/%d", &tmp.year, &tmp.month, &tmp.day);

    return tmp;
}

TIME TIMEsetNULL(){
    TIME tmp;

    tmp.day=tmp.month=tmp.year=tmp.hh=tmp.mm=-1;

    return tmp;
}

int TIMEcmp(TIME t1, TIME t2){
    int timetoint1=t1.year*365+t1.month*12+t1.day*31+t1.hh*60+t1.mm;
    int timetoint2=t2.year*365+t2.month*12+t2.day*31+t2.hh*60+t2.mm;

    return timetoint1<=timetoint2;
}

int TIMEdatacmp(TIME t1, TIME t2){
    int timetoint1=t1.year*365+t1.month*12+t1.day*31;
    int timetoint2=t2.year*365+t2.month*12+t2.day*31;

    if(timetoint1<timetoint2)
        return 1;
    else if(timetoint1>timetoint2)
        return -1;
    else return 0;
}

void TIMEprint(TIME time){
    printf("%d/%d/%d %02d:%02d --> ", time.year, time.month, time.day, time.hh, time.mm);

    return;
}
