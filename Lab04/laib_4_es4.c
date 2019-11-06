/*
=============================================================
Name        : laib_4_es4.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_4 Exercise 4 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAXC 15
#define MAXFILE 100
#define MAXENTRIES 500

typedef enum{
    r_search, r_code, r_date, r_partenza, r_capolinea, r_stampa, r_fine, r_err
}comando_e;

typedef struct{
    char code[MAX+1];
    char departure[MAX+1];
    char arrival[MAX+1];
    int date[3];
    int datetoint;
    int hour_dep[3];
    int hour_arr[3];
    int delay;
}info_log;

void STL(char *string);
int fill_log(FILE *log, info_log total_log[MAXENTRIES]);
comando_e leggiComando(comando_e *lastcmd);
void selezionaDati(comando_e pick, comando_e lastcmd, info_log total_log[MAXENTRIES], int total_entries);
void order(info_log total_log[MAXENTRIES], int total_entries, int ord_type);
void search(comando_e pick, info_log total_log[MAXENTRIES], int total_entries);
void printfunct(info_log total_log[MAXENTRIES], int total_entries);

int main(){
    int total_entries=0;
    char filename[MAX+1];
    comando_e pick, lastcmd=r_search;
    FILE *log;
    info_log total_log[MAXENTRIES];

    printf("Enter filename: ");
    scanf("%s", filename);

    log=fopen(filename, "r");
    if(log==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    total_entries=fill_log(log, total_log);
    do{
        printf("\n");
        pick=leggiComando(&lastcmd);
        selezionaDati(pick, lastcmd, total_log, total_entries);
    }while(pick!=r_fine);

    fclose(log);

    return EXIT_SUCCESS;
}

int fill_log(FILE *log, info_log total_log[MAXENTRIES]){
    int i=0, j;
    char line[MAXFILE+1];

    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", total_log[i].code, total_log[i].departure, total_log[i].arrival,
               &total_log[i].date[0], &total_log[i].date[1], &total_log[i].date[2], &total_log[i].hour_dep[0], &total_log[i].hour_dep[1], &total_log[i].hour_dep[2],
               &total_log[i].hour_arr[0], &total_log[i].hour_arr[1], &total_log[i].hour_arr[2], &total_log[i].delay);
        total_log[i].datetoint=total_log[i].date[0]+total_log[i].date[1]*31+total_log[i].date[2]*365;
        i++;
    }

    printf("\nContents of the log file:\n");
    printf("-------------------------\n");
    for(j=0 ; j<i ; j++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", total_log[j].code, total_log[j].departure, total_log[j].arrival,
               total_log[j].date[0], total_log[j].date[1], total_log[j].date[2], total_log[j].hour_dep[0], total_log[j].hour_dep[1], total_log[j].hour_dep[2],
               total_log[j].hour_arr[0], total_log[j].hour_arr[1], total_log[j].hour_arr[2], total_log[j].delay);
    printf("-------------------------\n");

    return i;
}

void STL(char *string){
    int i;

    for(i=0 ; i<strlen(string) ; i++)
        string[i]=tolower(string[i]);
}

comando_e leggiComando(comando_e *lastcmd){
    comando_e cmd;
    char line[MAXC+1];
    char table[r_err][MAXC+1]={"cerca", "codice", "data", "partenza", "capolinea", "stampa", "fine"};

    printf("Enter sort/search command (cerca/codice/data/partenza/capolinea/stampa/fine): ");
    scanf("%s", line);

    STL(line);
    cmd=r_search;
    while(cmd<r_err && strcmp(line, table[cmd])!=0)
        cmd++;
    if(cmd!=r_search && cmd!=r_err) *lastcmd=cmd;
    return cmd;
}

void selezionaDati(comando_e pick, comando_e lastcmd, info_log total_log[MAXENTRIES], int total_entries){
    int ord_type;
    switch(pick){
        case r_search:   search(lastcmd, total_log, total_entries);
            break;
        case r_code:   ord_type=1; order(total_log, total_entries, ord_type); printf("Sort by code done!\n");
            break;
        case r_date:   ord_type=2; order(total_log, total_entries, ord_type); printf("Sort by date done!\n");
            break;
        case r_partenza:   ord_type=3; order(total_log, total_entries, ord_type); printf("Sort by departure done!\n");
            break;
        case r_capolinea:   ord_type=4; order(total_log, total_entries, ord_type); printf("Sort by arrival done!\n");
            break;
        case r_stampa:   printfunct(total_log, total_entries);
            break;
        case r_fine:
            printf("\nChiusura del programma in corso...\n");
            break;
        case r_err:
            default:
                printf("\nWrong command!\n");
            break;
    }
}

void search(comando_e lastcmd, info_log total_log[MAXENTRIES], int total_entries){
    int i, l=0, r=total_entries-1, m, found=0;
    char searched[MAX+1];

    printf("Enter departure station to search: ");
    scanf("%s", searched);

    printf("-------------------------\n");

    if(lastcmd==r_partenza){            /* binary search */
        while(l<=r){
            m=(l+r)/2;
            if(strcmp(total_log[m].departure, searched)==0){
                found++;
                printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", total_log[m].code, total_log[m].departure, total_log[m].arrival,
                    total_log[m].date[0], total_log[m].date[1], total_log[m].date[2], total_log[m].hour_dep[0], total_log[m].hour_dep[1], total_log[m].hour_dep[2],
                    total_log[m].hour_arr[0], total_log[m].hour_arr[1], total_log[m].hour_arr[2], total_log[m].delay);
            }
            if(strcmp(total_log[m].departure, searched)<0)
                l=m+1;
            else
                r=m-1;
        }
    }
    else{           /* linear search */
        for(i=0 ; i<total_entries ; i++){
            if(strstr(total_log[i].departure, searched)!=NULL){
                found++;
                printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", total_log[i].code, total_log[i].departure, total_log[i].arrival,
                    total_log[i].date[0], total_log[i].date[1], total_log[i].date[2], total_log[i].hour_dep[0], total_log[i].hour_dep[1], total_log[i].hour_dep[2],
                    total_log[i].hour_arr[0], total_log[i].hour_arr[1], total_log[i].hour_arr[2], total_log[i].delay);
            }
        }
    }
    if(found)
        printf("\n");
    printf("Found %d matches!\n", found);
    printf("-------------------------\n");
}

void order(info_log total_log[MAXENTRIES], int total_entries, int ord_type){
    int i, j, r=total_entries-1, flag=1;
    info_log tmp;

    for(i=0 ; i<r && flag==1 ; i++){
        flag=0;
        for(j=0 ; j<r-i ; j++){
            switch(ord_type){
            case 1:         /* sort by code */
                if(strcmp(total_log[j].code, total_log[j+1].code)>0){
                    flag=1;
                    tmp=total_log[j];
                    total_log[j]=total_log[j+1];
                    total_log[j+1]=tmp;
                }
                break;
            case 2:         /* sort by date */
                if(total_log[j].datetoint>total_log[j+1].datetoint){
                    flag=1;
                    tmp=total_log[j];
                    total_log[j]=total_log[j+1];
                    total_log[j+1]=tmp;
                }
                break;
            case 3:         /* sort by departure */
                if(strcmp(total_log[j].departure, total_log[j+1].departure)>0){
                    flag=1;
                    tmp=total_log[j];
                    total_log[j]=total_log[j+1];
                    total_log[j+1]=tmp;
                }
                break;
            case 4:         /* sort by arrival */
                if(strcmp(total_log[j].arrival, total_log[j+1].arrival)>0){
                    flag=1;
                    tmp=total_log[j];
                    total_log[j]=total_log[j+1];
                    total_log[j+1]=tmp;
                }
                break;
            }
        }
    }
}

void printfunct(info_log total_log[MAXENTRIES], int total_entries){
    int i;
    char command[MAX+1], filenm[MAX+1];
    FILE *fp;

    printf("Enter print destination (stdout, file): ");
    scanf("%s", command);
    printf("\n");
    printf("-------------------------\n");

    if(strcmp(command, "stdout")==0){           /* print on stdout */
        for(i=0 ; i<total_entries ; i++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", total_log[i].code, total_log[i].departure, total_log[i].arrival,
               total_log[i].date[0], total_log[i].date[1], total_log[i].date[2], total_log[i].hour_dep[0], total_log[i].hour_dep[1], total_log[i].hour_dep[2],
               total_log[i].hour_arr[0], total_log[i].hour_arr[1], total_log[i].hour_arr[2], total_log[i].delay);
    }
    else if(strcmp(command, "file")==0){            /* print on file */
        printf("Enter filename: ");
        scanf("%s", filenm);
        fp=fopen(filenm, "w");
        for(i=0 ; i<total_entries ; i++)
            fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", total_log[i].code, total_log[i].departure, total_log[i].arrival,
               total_log[i].date[0], total_log[i].date[1], total_log[i].date[2], total_log[i].hour_dep[0], total_log[i].hour_dep[1], total_log[i].hour_dep[2],
               total_log[i].hour_arr[0], total_log[i].hour_arr[1], total_log[i].hour_arr[2], total_log[i].delay);
        fclose(fp);
    }
    printf("\nPrint done!\n");
    printf("-------------------------\n");
}
