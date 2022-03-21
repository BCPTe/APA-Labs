#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

typedef struct{
    int year, month, day;
    int hh, mm;
}TIME;

TIME TIMEread(FILE *fp);
TIME TIMEdataread(FILE *fp);
TIME TIMEsetNULL();
int TIMEcmp(TIME t1, TIME t2);
int TIMEdatacmp(TIME t1, TIME t2);
void TIMEprint(TIME time);

#endif // TIME_H_INCLUDED
