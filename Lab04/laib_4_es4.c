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
int fill_log(FILE *log, info_log ptr_log[MAXENTRIES]);
comando_e leggiComando(comando_e *lastcmd);
void selezionaDati(comando_e pick, comando_e lastcmd, info_log ptr_log[MAXENTRIES], int total_entries);
void order(info_log ptr_log[MAXENTRIES], int total_entries, int ord_type);
void search(comando_e pick, info_log ptr_log[MAXENTRIES], int total_entries);
void printfunct(info_log ptr_log[MAXENTRIES], int total_entries);

int main(){
    int total_entries=0;
    char filename[MAX+1];
    comando_e pick, lastcmd=r_search;
    FILE *log;
    info_log ptr_log[MAXENTRIES];

    printf("Enter filename: ");
    scanf("%s", filename);

    log=fopen(filename, "r");
    if(log==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    total_entries=fill_log(log, ptr_log);
    do{
        printf("\n");
        pick=leggiComando(&lastcmd);
        selezionaDati(pick, lastcmd, ptr_log, total_entries);
    }while(pick!=r_fine);

    fclose(log);

    return EXIT_SUCCESS;
}

int fill_log(FILE *log, info_log ptr_log[MAXENTRIES]){
    int i=0, j;
    char line[MAXFILE+1];

    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", ptr_log[i].code, ptr_log[i].departure, ptr_log[i].arrival,
               &ptr_log[i].date[0], &ptr_log[i].date[1], &ptr_log[i].date[2], &ptr_log[i].hour_dep[0], &ptr_log[i].hour_dep[1], &ptr_log[i].hour_dep[2],
               &ptr_log[i].hour_arr[0], &ptr_log[i].hour_arr[1], &ptr_log[i].hour_arr[2], &ptr_log[i].delay);
        ptr_log[i].datetoint=ptr_log[i].date[0]+ptr_log[i].date[1]*31+ptr_log[i].date[2]*365;
        i++;
    }

    printf("\nContents of the log file:\n");
    printf("-------------------------\n");
    for(j=0 ; j<i ; j++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_log[j].code, ptr_log[j].departure, ptr_log[j].arrival,
               ptr_log[j].date[0], ptr_log[j].date[1], ptr_log[j].date[2], ptr_log[j].hour_dep[0], ptr_log[j].hour_dep[1], ptr_log[j].hour_dep[2],
               ptr_log[j].hour_arr[0], ptr_log[j].hour_arr[1], ptr_log[j].hour_arr[2], ptr_log[j].delay);
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

void selezionaDati(comando_e pick, comando_e lastcmd, info_log ptr_log[MAXENTRIES], int total_entries){
    int ord_type;
    switch(pick){
        case r_search:   search(lastcmd, ptr_log, total_entries);
            break;
        case r_code:   ord_type=1; order(ptr_log, total_entries, ord_type); printf("Sort by code done!\n");
            break;
        case r_date:   ord_type=2; order(ptr_log, total_entries, ord_type); printf("Sort by date done!\n");
            break;
        case r_partenza:   ord_type=3; order(ptr_log, total_entries, ord_type); printf("Sort by departure done!\n");
            break;
        case r_capolinea:   ord_type=4; order(ptr_log, total_entries, ord_type); printf("Sort by arrival done!\n");
            break;
        case r_stampa:   printfunct(ptr_log, total_entries);
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

void search(comando_e lastcmd, info_log ptr_log[MAXENTRIES], int total_entries){
    int i, l=0, r=total_entries-1, m, found=0;
    char searched[MAX+1];

    printf("Enter departure station to search: ");
    scanf("%s", searched);

    printf("-------------------------\n");

    if(lastcmd==r_partenza){            /* binary search */
        while(l<=r){
            m=(l+r)/2;
            if(strcmp(ptr_log[m].departure, searched)==0){
                found++;
                printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_log[m].code, ptr_log[m].departure, ptr_log[m].arrival,
                    ptr_log[m].date[0], ptr_log[m].date[1], ptr_log[m].date[2], ptr_log[m].hour_dep[0], ptr_log[m].hour_dep[1], ptr_log[m].hour_dep[2],
                    ptr_log[m].hour_arr[0], ptr_log[m].hour_arr[1], ptr_log[m].hour_arr[2], ptr_log[m].delay);
            }
            if(strcmp(ptr_log[m].departure, searched)<0)
                l=m+1;
            else
                r=m-1;
        }
    }
    else{           /* linear search */
        for(i=0 ; i<total_entries ; i++){
            if(strstr(ptr_log[i].departure, searched)!=NULL){
                found++;
                printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_log[i].code, ptr_log[i].departure, ptr_log[i].arrival,
                    ptr_log[i].date[0], ptr_log[i].date[1], ptr_log[i].date[2], ptr_log[i].hour_dep[0], ptr_log[i].hour_dep[1], ptr_log[i].hour_dep[2],
                    ptr_log[i].hour_arr[0], ptr_log[i].hour_arr[1], ptr_log[i].hour_arr[2], ptr_log[i].delay);
            }
        }
    }
    if(found)
        printf("\n");
    printf("Found %d matches!\n", found);
    printf("-------------------------\n");
}

void order(info_log ptr_log[MAXENTRIES], int total_entries, int ord_type){
    int i, j, min;
    info_log tmp;

    for(i=0 ; i<total_entries ; i++){
        min=i;
        for(j=i+1 ; j<total_entries ; j++){
            switch(ord_type){
            case 1:         /* sort by code */
                if(strcmp(ptr_log[j].code, ptr_log[min].code)<0) min=j;
                break;
            case 2:         /* sort by date */
                if(ptr_log[j].datetoint<ptr_log[min].datetoint) min=j;
                break;
            case 3:         /* sort by departure */
                if(strcmp(ptr_log[j].departure, ptr_log[min].departure)<0) min=j;
                break;
            case 4:         /* sort by arrival */
                if(strcmp(ptr_log[j].arrival, ptr_log[min].arrival)<0) min=j;
                break;
            }
        }
        if(min!=i){
            tmp=ptr_log[i];
            ptr_log[i]=ptr_log[min];
            ptr_log[min]=tmp;
        }
    }
}

void printfunct(info_log ptr_log[MAXENTRIES], int total_entries){
    int i;
    char command[MAX+1], filenm[MAX+1];
    FILE *fp;

    printf("Enter print destination (stdout, file): ");
    scanf("%s", command);
    printf("\n");
    printf("-------------------------\n");

    if(strcmp(command, "stdout")==0){           /* print on stdout */
        for(i=0 ; i<total_entries ; i++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_log[i].code, ptr_log[i].departure, ptr_log[i].arrival,
               ptr_log[i].date[0], ptr_log[i].date[1], ptr_log[i].date[2], ptr_log[i].hour_dep[0], ptr_log[i].hour_dep[1], ptr_log[i].hour_dep[2],
               ptr_log[i].hour_arr[0], ptr_log[i].hour_arr[1], ptr_log[i].hour_arr[2], ptr_log[i].delay);
    }
    else if(strcmp(command, "file")==0){            /* print on file */
        printf("Enter filename: ");
        scanf("%s", filenm);
        fp=fopen(filenm, "w");
        for(i=0 ; i<total_entries ; i++)
            fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", ptr_log[i].code, ptr_log[i].departure, ptr_log[i].arrival,
               ptr_log[i].date[0], ptr_log[i].date[1], ptr_log[i].date[2], ptr_log[i].hour_dep[0], ptr_log[i].hour_dep[1], ptr_log[i].hour_dep[2],
               ptr_log[i].hour_arr[0], ptr_log[i].hour_arr[1], ptr_log[i].hour_arr[2], ptr_log[i].delay);
        fclose(fp);
    }
    printf("\nPrint done!\n");
    printf("-------------------------\n");
}

