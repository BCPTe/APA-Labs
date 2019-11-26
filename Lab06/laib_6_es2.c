/*
=============================================================
Name        : laib_6_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_6 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

/*
N.B.:
    1) NON VIENE GESTITO APPOSITAMENTE IL CASO IN CUI SI AGGIUNGANO ELEMENTI CON LO STESSO CODICE.
       CI SI ASPETTA CHE, IN GENERALE, L'UTENTE PROVVEDA A CONTROLLARE I FILE DI ACQUISIZIONE AL FINE DI EVITARE POSSIBILI ERRORI.
    2) L'ORDINAMENTO DELLE DATE VIENE EFFETTUATO SECONDO UN ALGORITMO ROZZO, SENZA ALCUNA GESTIONE DEI POSSIBILI ERRORI.
       CI SI ASPETTA CHE, IN GENERALE, L'UTENTE PROVVEDA AD INSERIRE DATI VALIDI AL FINE DI EVITARE QUALSIASI TIPO DI CRASH IMPREVISTO.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 25
#define MAXCODE 6
#define MAXLINE 200

typedef enum{
    InsCmdLine=1, InsFile, search, delCode, delDates, print, printCMD, end=0
}commands;

typedef struct{
    int firstday, firstmonth, firstyear, firstdatetoint;
    int lastday, lastmonth, lastyear, lastdatetoint;
}dateDel;

typedef struct{
    char code[MAXCODE];
    char name[MAX+1], surname[MAX+1];
    int day, month, year, datetoint;
    char via[MAX+1], city[MAX+1];
    int CAP;
}registry;

typedef struct list *link;
struct list{
    registry info;
    link next;
};

link ListIniz(link head);
link newNode(registry val, link next);
link SortListIns(link head, registry val);
link SearchFunct(link head, char *searchcode);
link SortListDel(link head, char *delcode);
link delBetweenTwoDates(link *head, dateDel twodates);
void printactual(link head);
void printfunct(link head);

int main(){
    int cmd;
    char InsFilename[MAX+1], tempcode[MAXCODE];
    link head=NULL, ptrSearched, deleted;
    registry tmp;
    dateDel twodates;
    FILE *fp;

    /* acquire file items */
    head=ListIniz(head);

    do{
            /* print menu */
        printf("\tMENU'\n");
        printf("1) ADD ELEMENT FORM CMD LINE\n");
        printf("2) ADD ELEMENT FORM FILE\n");
        printf("3) SEARCH BY CODE\n");
        printf("4) DELETE ELEMENT BY CODE\n");
        printf("5) DELETE ELEMENT BETWEEN TWO DATES\n");
        printf("6) PRINT ON FILE\n");
        printf("7) PRINT ACTUAL LIST\n");
        printf("0) CLOSE PROGRAM\n\n");

        printf("Enter command: ");
        scanf("%d", &cmd);

        switch(cmd){
            /* command line input */
            case InsCmdLine:
                printf("Enter item in the following form (<codice> <nome> <cognome> <data_di_nascita-gg/mm/aaaa> <via> <citta'> <cap>):\n");
                scanf("%s %s %s %d/%d/%d %s %s %d", tempcode, tmp.name, tmp.surname, &tmp.day, &tmp.month, &tmp.year, tmp.via, tmp.city, &tmp.CAP);
                while(strlen(tempcode)!=5 || tempcode[0]!='A'){
                    printf("Error! (max. 5 ch. && first char='A')\n");
                    scanf("%s", tempcode);
                }
                strcpy(tmp.code, tempcode);
                tmp.datetoint=tmp.day+tmp.month*31+tmp.year*365;
                head=SortListIns(head, tmp);
                break;
            /* file input */
            case InsFile:
                printf("Enter filename: ");
                scanf("%s", InsFilename);
                fp=fopen(InsFilename, "r");
                if(fp==NULL){
                    /* if file doesn't exist exit with code error 99 */
                    printf("Error: file doesn't exist!\n");
                    exit(11);
                }
                while(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", tmp.code, tmp.name, tmp.surname, &tmp.day, &tmp.month, &tmp.year, tmp.via, tmp.city, &tmp.CAP)!=EOF){
                    tmp.datetoint=tmp.day+tmp.month*31+tmp.year*365;
                    head=SortListIns(head, tmp);
                }
                fclose(fp);
                printf("----------------------------------------\n");
                printf("DONE!\n");
                printf("----------------------------------------\n\n");
                break;
            /* search by code */
            case search:
                do{
                    printf("Enter code to search in the list: ");
                    scanf("%s", tempcode);
                    if(strlen(tempcode)!=5 || tempcode[0]!='A')
                        printf("Error! (max. 5 ch. && first char='A')\n");
                }while(strlen(tempcode)!=5 || tempcode[0]!='A');
                ptrSearched=SearchFunct(head, tempcode);
                printf("----------------------------------------\n");
                if(ptrSearched!=NULL)
                    printf("%s %s %s %d/%d/%d %s %s %d\n", ptrSearched->info.code, ptrSearched->info.name, ptrSearched->info.surname,
                        ptrSearched->info.day, ptrSearched->info.month, ptrSearched->info.year, ptrSearched->info.via, ptrSearched->info.city, ptrSearched->info.CAP);
                else printf("Searched item isn't in list!\n");
                printf("----------------------------------------\n\n");
                break;
            /* delete by code */
            case delCode:
                do{
                    printf("Enter code to delete from the list: ");
                    scanf("%s", tempcode);
                    if(strlen(tempcode)!=5 || tempcode[0]!='A')
                        printf("Error! (max. 5 ch. && first char='A')\n");
                }while(strlen(tempcode)!=5 || tempcode[0]!='A');
                head=SortListDel(head, tempcode);
                break;
            /* delete between two dates */
            case delDates:
                printf("Enter first date: ");
                scanf("%d/%d/%d", &twodates.firstday, &twodates.firstmonth, &twodates.firstyear);
                twodates.firstdatetoint=twodates.firstday+twodates.firstmonth*31+twodates.firstyear*365;
                printf("Enter last date: ");
                scanf("%d/%d/%d", &twodates.lastday, &twodates.lastmonth, &twodates.lastyear);
                twodates.lastdatetoint=twodates.lastday+twodates.lastmonth*31+twodates.lastyear*365;
                deleted=delBetweenTwoDates(&head, twodates);
                if(deleted!=NULL){
                    printf("\tACTUAL LIST DELETED\n");
                    printactual(deleted);
                }
                else{
                    printf("----------------------------------------\n");
                    printf("NO ITEMS DELETED!\n");
                    printf("----------------------------------------\n\n");
                }
                break;
            /* print on file */
            case print: printfunct(head);
                break;
            /* print on command line */
            case printCMD:
                printf("\tACTUAL LIST CONTENT\n");
                printactual(head);
                break;
            /* end-->closure */
            case end:
                    printf("\nThanks for using this program!\nClosing in progress...");
                    return EXIT_SUCCESS;
                break;
            /* all other cases = error */
            default:
                printf("Error: invalid command!\n");
        }
    }while(cmd!=end); /* or 'while(1)' --> because the closure occurs only through the end command - unstructured exit*/

    return EXIT_SUCCESS;
}

link newNode(registry val, link next){          /* new node creator function */
    link x=malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    x->info=val;
    x->next=next;
    return x;
}

link ListIniz(link head){       /* read list from file for the first time */
    FILE *fp;
    registry tmp;

    fp=fopen("info.txt", "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    while(fscanf(fp, "%s %s %s %d/%d/%d %s %s %d\n", tmp.code, tmp.name, tmp.surname,
                &tmp.day, &tmp.month, &tmp.year, tmp.via, tmp.city, &tmp.CAP)!=EOF){
        tmp.datetoint=tmp.day+tmp.month*31+tmp.year*365;
        head=SortListIns(head, tmp);
    }
    fclose(fp);
    return head;
}

link SortListIns(link head, registry val){      /* sorted input */
    link x, p;

    if(head==NULL || head->info.datetoint>val.datetoint)
        return newNode(val, head);
    for(x=head->next, p=head ; x!=NULL && val.datetoint>x->info.datetoint ; p=x, x=x->next);
    p->next=newNode(val, x);
    return head;
}

link SearchFunct(link head, char *searchcode){
    link x;

    for(x=head ; x!=NULL ; x=x->next)
        if(strcmp(searchcode, x->info.code)==0)
            return x;
    return NULL;
}

link SortListDel(link head, char *delcode){         /* delete by code in sorted list function */
    int flag=0;
    link x, p;

    if(head==NULL)
        return NULL;
    for(x=head, p=NULL ; x!=NULL ; p=x, x=x->next){
        if(strcmp(delcode, x->info.code)==0){
            flag=1;
            printf("Item to del:\n");
            printf("----------------------------------------\n");
            printf("%s %s %s %d/%d/%d %s %s %d\n", x->info.code, x->info.name, x->info.surname,
                    x->info.day, x->info.month, x->info.year, x->info.via, x->info.city, x->info.CAP);
            printf("----------------------------------------\n\n");
            if(x==head)
                head=x->next;
            else
                p->next=x->next;
            free(x);
            break;
        }
    }
    if(!flag){
        printf("----------------------------------------\n");
        printf("NO ITEM WITH CODE %s!\n", delcode);
        printf("----------------------------------------\n\n");
    }

    return head;
}

link delBetweenTwoDates(link *head, dateDel twodates){      /* delete between two dates function */
    int flag=0;
    link x, p, y;
    link headDel=NULL;

    if(*head==NULL)
        return NULL;
    for(p=*head, y=NULL ; p!=NULL && p->info.datetoint<twodates.firstdatetoint ; y=p, p=p->next);
    if(p==*head)
        flag=1;
    if(p==NULL)
        return headDel;
    for(x=p->next ; p!=NULL && p->info.datetoint<=twodates.lastdatetoint && x->info.datetoint<=twodates.lastdatetoint; p=x, x=x->next){
        if(headDel==NULL)
            headDel=p;
        p->next=x;
    }
    if(flag)
        *head=x;
    else
        y->next=p->next;
    p->next=NULL;

    return headDel;
}

void printfunct(link head){         /* print on file function */
    char filename[MAX+1];
    link x;
    FILE *fp;

    printf("Enter filename: ");
    scanf("%s", filename);
    fp=fopen(filename, "a+");
    for(x=head ; x!=NULL ; x=x->next){
        fprintf(fp, "%s %s %s %d/%d/%d %s %s %d\n", x->info.code, x->info.name, x->info.surname,
               x->info.day, x->info.month, x->info.year, x->info.via, x->info.city, x->info.CAP);
    }
    fclose(fp);
    printf("----------------------------------------\n");
    printf("DONE!\n");
    printf("----------------------------------------\n\n");
}

void printactual(link head){            /* print on command line function */
    link x;

    printf("----------------------------------------\n");
    for(x=head ; x!=NULL ; x=x->next){
        printf("%s %s %s %d/%d/%d %s %s %d\n", x->info.code, x->info.name, x->info.surname,
               x->info.day, x->info.month, x->info.year, x->info.via, x->info.city, x->info.CAP);
    }
    printf("----------------------------------------\n\n");
}
