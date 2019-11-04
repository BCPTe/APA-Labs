/*
=============================================================
Name        : laib_2_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_2 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 30
#define MAXC 15
#define MAXFILE 100

#define filename "log.txt"

typedef enum{
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
}comando_e;

void STL(char *string);
comando_e leggiComando(char *line_tot);
void selezionaDati(comando_e cmd, char *line_tot, FILE *log);
void date(char *line_tot, FILE *log, int flag);
void partenza(char *line_tot, FILE *log);
void capolinea(char *line_tot, FILE *log);
void ritardo_tot(char *line_tot, FILE *log);

int main(){
    char line_tot[MAX+1];
    comando_e pick;
    FILE *log;

    log=fopen(filename, "r");
    if(log==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    pick=leggiComando(line_tot);
    printf("\n");
    selezionaDati(pick, line_tot, log);

    fclose(log);

    return EXIT_SUCCESS;
}

void STL(char *string){
    int i;

    for(i=0 ; i<strlen(string) ; i++)
        string[i]=tolower(string[i]);
}

comando_e leggiComando(char *line_tot){
    comando_e cmd;
    char line[MAXC+1];
    char table[r_err][MAXC+1]={"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    printf("Enter command (date/partenza/capolinea/ritardo/ritardo_tot/fine): ");
    gets(line_tot);
    sscanf(line_tot, "%s", line);
    strcpy(line_tot, line_tot+strlen(line));

    STL(line);
    cmd=r_date;
    while(cmd<r_err && strcmp(line, table[cmd])!=0)
        cmd++;
    return cmd;
}

void selezionaDati(comando_e pick, char *line_tot, FILE *log){
    int flag=0;

    switch(pick){
        case r_date:   flag=0; date(line_tot, log, flag);
            break;
        case r_partenza:   partenza(line_tot, log);
            break;
        case r_capolinea:   capolinea(line_tot, log);
            break;
        case r_ritardo:   flag=1; date(line_tot, log, flag);
            break;
        case r_ritardo_tot:   ritardo_tot(line_tot, log);
            break;
        case r_fine:
            printf("Chiusura del programma in corso...\n");
            break;
        case r_err:
            default:
                printf("Wrong command!\n");
            break;
    }
}

void date(char *line_tot, FILE *log, int flag){
    char line[MAXFILE+1];
    struct{
        int ss_date[3];
        int ss_datetoint;
        int fs_date[3];
        int fs_datetoint;
    }search;
    struct{
        int date[3];
        int datetoint;
        int delay;
    }info_log;

    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%*s %*s %*s %d/%d/%d %*d:%*d:%*d %*d:%*d:%*d %d", &info_log.date[0], &info_log.date[1], &info_log.date[2], &info_log.delay);
        sscanf(line_tot, "%d/%d/%d %d/%d/%d", &search.ss_date[0], &search.ss_date[1], &search.ss_date[2],
               &search.fs_date[0], &search.fs_date[1], &search.fs_date[2]);
               info_log.datetoint=info_log.date[0]+info_log.date[1]*31+info_log.date[2]*365;
               search.ss_datetoint=search.ss_date[0]+search.ss_date[1]*31+search.ss_date[2]*365;
               search.fs_datetoint=search.fs_date[0]+search.fs_date[1]*31+search.fs_date[2]*365;
        if(info_log.datetoint>=search.ss_datetoint && info_log.datetoint<=search.fs_datetoint && flag==0)
            puts(line);
        else if(info_log.datetoint>=search.ss_datetoint && info_log.datetoint<=search.fs_datetoint && flag==1 && info_log.delay>0)
            puts(line);
    }
}

void partenza(char *line_tot, FILE *log){
    char line[MAXFILE+1], s_depart[MAX+1], depart[MAX+1];

    sscanf(line_tot, "%s", s_depart);
    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%*s %s", depart);
        if(strcmp(s_depart, depart)==0)
            puts(line);
    }
}

void capolinea(char *line_tot, FILE *log){
    char line[MAXFILE+1], s_arr[MAX+1], arr[MAX+1];

    sscanf(line_tot, "%s", s_arr);
    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%*s %*s %s", arr);
        if(strcmp(s_arr, arr)==0)
            puts(line);
    }
}

void ritardo_tot(char *line_tot, FILE *log){
    char line[MAXFILE+1], s_code[MAX+1], code[MAX+1];
    int cnt=0, delay, delay_tot=0;

    sscanf(line_tot, "%s", s_code);
    while(fgets(line, MAXFILE, log)!=NULL){
        sscanf(line, "%s %*s %*s %*d/%*d/%*d %*d:%*d:%*d %*d:%*d:%*d %d", code, &delay);
        if(strcmp(s_code, code)==0){
            cnt++;
            delay_tot+=delay;
        }
    }
    printf("Total runs: %d\nTotal delay: %d minute(s)\n", cnt, delay_tot);
}
