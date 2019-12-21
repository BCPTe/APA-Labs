#include <stdio.h>
#include <stdlib.h>
#include "INV.h"

int readStat(FILE *fp, stat_t *ptr){
    return fscanf(fp, "%d %d %d %d %d %d\n", &(ptr->hp), &(ptr->mp), &(ptr->atk), &(ptr->def), &(ptr->mag), &(ptr->spr));
}

int addObj(FILE *fp, inv_t *ptr){
    int check1=fscanf(fp, "%s %s", ptr->nameObj, ptr->clasObj);
    int check2=readStat(fp, &(ptr->statObj));
    return ((check1==EOF || check2==EOF) ? EXIT_FAILURE : EXIT_SUCCESS);
}

void printObj(FILE *fp, inv_t *ptr, int index){
    fprintf(fp, "| EQ%03d\t%-20s%-20s|", index, ptr->nameObj, ptr->clasObj);
    printStatObj(fp, &ptr->statObj);
}

void printStatObj(FILE *fp, stat_t *ptr){
    fprintf(fp, "\t%+d\t%+d\t%+d\t%+d\t%+d\t%+d\t|\n", ptr->hp, ptr->mp, ptr->atk, ptr->def, ptr->mag, ptr->spr);
}
