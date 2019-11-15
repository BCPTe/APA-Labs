/*
=============================================================
Name        : laib_5_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_5 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAXC 15
#define MAXFILE 100

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
int fill_log(FILE *log, info_log **total_log, info_log ****ptr_sorted);
comando_e leggiComando(comando_e *lastcmd);
void selezionaDati(comando_e pick, comando_e lastcmd, info_log ***ptr_sorted, int total_entries);
void order(info_log **ptr_sorted, int total_entries, int ord_type);
void search(info_log **ptr_sorted, int total_entries);
void printfunct(info_log **ptr_sorted, int total_entries);

int main(){
    int total_entries=0, i, j;
    char filename[MAX+1];
    comando_e pick, lastcmd=r_search;
    FILE *log;
    info_log *total_log, ***ptr_sorted;

    printf("Enter filename: ");
    scanf("%s", filename);

    log=fopen(filename, "r");
    if(log==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    total_entries=fill_log(log, &total_log, &ptr_sorted);
    do{
        printf("\n");
        pick=leggiComando(&lastcmd);
        selezionaDati(pick, lastcmd, ptr_sorted, total_entries);
    }while(pick!=r_fine);

    fclose(log);

    /*
    //  IF U WANT TO VERIFY THAT THE ORDERS TAKE PLACE AT THE SAME TIME, DELETE THE '/ *  * /' AND COOHSE fine COMMAND!  //
    //  N.B.: U MUST FIRST WRITE ALL THE ORDER CODES  //
    for(j=0 ; j<r_capolinea ; j++){
        for(i=0 ; i<total_entries ; i++)
            fprintf(stdout, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", ptr_sorted[j][i]->code, ptr_sorted[j][i]->departure, ptr_sorted[j][i]->arrival,
                ptr_sorted[j][i]->date[j], ptr_sorted[j][i]->date[1], ptr_sorted[j][i]->date[2], ptr_sorted[j][i]->hour_dep[j], ptr_sorted[j][i]->hour_dep[1], ptr_sorted[j][i]->hour_dep[2],
                ptr_sorted[j][i]->hour_arr[j], ptr_sorted[j][i]->hour_arr[1], ptr_sorted[j][i]->hour_arr[2], ptr_sorted[j][i]->delay);
        printf("\n\n");
    }
    */

    return EXIT_SUCCESS;
}

int fill_log(FILE *log, info_log **total_log, info_log ****ptr_sorted){
    int i=0, j, entries=0;
    char line[MAXFILE+1];

    while(fgets(line, MAXFILE, log)!=NULL)
        entries++;

    *ptr_sorted=malloc(r_capolinea*sizeof(info_log **));
    for(i=0 ; i<r_capolinea ; i++)
        (*ptr_sorted)[i]=malloc(entries*sizeof(info_log *));

    *total_log=malloc(entries*sizeof(info_log));

    i=0;
    rewind(log);
    while(fgets(line, MAXFILE, log)!=NULL){
        /* delete newline */
        line[strlen(line)-1]='\0';
        sscanf(line, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", (*total_log)[i].code, (*total_log)[i].departure, (*total_log)[i].arrival,
               &(*total_log)[i].date[0], &(*total_log)[i].date[1], &(*total_log)[i].date[2],
               &(*total_log)[i].hour_dep[0], &(*total_log)[i].hour_dep[1], &(*total_log)[i].hour_dep[2],
               &(*total_log)[i].hour_arr[0], &(*total_log)[i].hour_arr[1], &(*total_log)[i].hour_arr[2], &(*total_log)[i].delay);
        (*total_log)[i].datetoint=(*total_log)[i].date[0]+(*total_log)[i].date[1]*31+(*total_log)[i].date[2]*365;
        for(j=0 ; j<r_capolinea ; j++){
            (*ptr_sorted)[j][i]=&(*total_log)[i];
        }
        i++;
    }

    printf("\nContents of the log file:\n");
    printf("-------------------------\n");
    for(j=0 ; j<i ; j++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", (*total_log)[j].code, (*total_log)[j].departure, (*total_log)[j].arrival,
               (*total_log)[j].date[0], (*total_log)[j].date[1], (*total_log)[j].date[2], (*total_log)[j].hour_dep[0], (*total_log)[j].hour_dep[1], (*total_log)[j].hour_dep[2],
               (*total_log)[j].hour_arr[0], (*total_log)[j].hour_arr[1], (*total_log)[j].hour_arr[2], (*total_log)[j].delay);
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
    if(cmd!=r_search && cmd!=r_stampa && cmd!=r_err) *lastcmd=cmd;
    return cmd;
}

void selezionaDati(comando_e pick, comando_e lastcmd, info_log ***ptr_sorted, int total_entries){
    int ord_type;
    switch(pick){
        case r_search:   search(ptr_sorted[0], total_entries);
            break;
        case r_code:   ord_type=1; order(ptr_sorted[0], total_entries, ord_type); printf("Sort by code done!\n");
            break;
        case r_date:   ord_type=2; order(ptr_sorted[1], total_entries, ord_type); printf("Sort by date done!\n");
            break;
        case r_partenza:   ord_type=3; order(ptr_sorted[2], total_entries, ord_type); printf("Sort by departure done!\n");
            break;
        case r_capolinea:   ord_type=4; order(ptr_sorted[3], total_entries, ord_type); printf("Sort by arrival done!\n");
            break;
        case r_stampa:
            if(lastcmd==r_code || lastcmd==r_search)
                printfunct(ptr_sorted[0], total_entries);
            else if(lastcmd==r_date)
                printfunct(ptr_sorted[1], total_entries);
            else if(lastcmd==r_partenza)
                printfunct(ptr_sorted[2], total_entries);
            else if(lastcmd==r_capolinea)
                printfunct(ptr_sorted[3], total_entries);
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

void search(info_log **ptr_sorted, int total_entries){
    int i, found=0;
    char searched[MAX+1];

    printf("WARNING: the search is carried out for convenience on the log ordered by code!\n");
    printf("Enter departure station to search: ");
    scanf("%s", searched);

    printf("-------------------------\n");

    /* linear search */
    for(i=0 ; i<total_entries ; i++){
        if(strstr(ptr_sorted[i]->departure, searched)!=NULL){
            found++;
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_sorted[i]->code, ptr_sorted[i]->departure, ptr_sorted[i]->arrival,
                ptr_sorted[i]->date[0], ptr_sorted[i]->date[1], ptr_sorted[i]->date[2], ptr_sorted[i]->hour_dep[0], ptr_sorted[i]->hour_dep[1], ptr_sorted[i]->hour_dep[2],
                ptr_sorted[i]->hour_arr[0], ptr_sorted[i]->hour_arr[1], ptr_sorted[i]->hour_arr[2], ptr_sorted[i]->delay);
        }
    }

    if(found)
        printf("\n");
    printf("Found %d matches!\n", found);
    printf("-------------------------\n");
}

void order(info_log **ptr_sorted, int total_entries, int ord_type){
    int i, j, r=total_entries-1, flag=1;
    info_log *tmp;

    for(i=0 ; i<r && flag==1 ; i++){
        flag=0;
        for(j=0 ; j<r-i ; j++){
            switch(ord_type){
            case 1:         /* sort by code */
                if(strcmp(ptr_sorted[j]->code, ptr_sorted[j+1]->code)>0){
                    flag=1;
                    tmp=ptr_sorted[j];
                    ptr_sorted[j]=ptr_sorted[j+1];
                    ptr_sorted[j+1]=tmp;
                }
                break;
            case 2:         /* sort by date */
                if(ptr_sorted[j]->datetoint>ptr_sorted[j+1]->datetoint){
                    flag=1;
                    tmp=ptr_sorted[j];
                    ptr_sorted[j]=ptr_sorted[j+1];
                    ptr_sorted[j+1]=tmp;
                }
                break;
            case 3:         /* sort by departure */
                if(strcmp(ptr_sorted[j]->departure, ptr_sorted[j+1]->departure)>0){
                    flag=1;
                    tmp=ptr_sorted[j];
                    ptr_sorted[j]=ptr_sorted[j+1];
                    ptr_sorted[j+1]=tmp;
                }
                break;
            case 4:         /* sort by arrival */
                if(strcmp(ptr_sorted[j]->arrival, ptr_sorted[j+1]->arrival)>0){
                    flag=1;
                    tmp=ptr_sorted[j];
                    ptr_sorted[j]=ptr_sorted[j+1];
                    ptr_sorted[j+1]=tmp;
                }
                break;
            }
        }
    }
}

void printfunct(info_log **ptr_sorted, int total_entries){
    int i;
    char command[MAX+1], filenm[MAX+1];
    FILE *fp;

    printf("Enter print destination (stdout, file): ");
    scanf("%s", command);
    printf("\n");
    printf("-------------------------\n");

    if(strcmp(command, "stdout")==0){           /* print on stdout */
        for(i=0 ; i<total_entries ; i++)
            printf("%s | %s -> %s\t| %d/%d/%d\t%d:%d:%d - %d:%d:%d\t%d\n", ptr_sorted[i]->code, ptr_sorted[i]->departure, ptr_sorted[i]->arrival,
               ptr_sorted[i]->date[0], ptr_sorted[i]->date[1], ptr_sorted[i]->date[2], ptr_sorted[i]->hour_dep[0], ptr_sorted[i]->hour_dep[1], ptr_sorted[i]->hour_dep[2],
               ptr_sorted[i]->hour_arr[0], ptr_sorted[i]->hour_arr[1], ptr_sorted[i]->hour_arr[2], ptr_sorted[i]->delay);

    }
    else if(strcmp(command, "file")==0){            /* print on file */
        printf("Enter filename: ");
        scanf("%s", filenm);
        fp=fopen(filenm, "w");
        for(i=0 ; i<total_entries ; i++)
            fprintf(fp, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d\n", ptr_sorted[i]->code, ptr_sorted[i]->departure, ptr_sorted[i]->arrival,
               ptr_sorted[i]->date[0], ptr_sorted[i]->date[1], ptr_sorted[i]->date[2], ptr_sorted[i]->hour_dep[0], ptr_sorted[i]->hour_dep[1], ptr_sorted[i]->hour_dep[2],
               ptr_sorted[i]->hour_arr[0], ptr_sorted[i]->hour_arr[1], ptr_sorted[i]->hour_arr[2], ptr_sorted[i]->delay);
        fclose(fp);
    }
    printf("\nPrint done!\n");
    printf("-------------------------\n");
}
