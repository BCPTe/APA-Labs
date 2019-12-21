#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED

#ifndef MAX
#define MAX 50
#endif // MAX

typedef struct{
    int hp, mp, atk, def, mag, spr;
}stat_t;

typedef struct{
    char nameObj[MAX+1], clasObj[MAX+1];
    stat_t statObj;
}inv_t;

int readStat(FILE *fp, stat_t *ptr);
void printStatObj(FILE *fp, stat_t *ptr);
int addObj(FILE *fp, inv_t *ptr);
void printObj(FILE *fp, inv_t *ptr, int index);

#endif // INV_H_INCLUDED
