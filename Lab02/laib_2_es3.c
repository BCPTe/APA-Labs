/*
=============================================================
Name        : laib_2_es3.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_2 Exercise 3 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 25
#define MAXFILE 20
#define LEN_SEQ 5

#define temp_filename "temp.txt"

void tolow(char *string);
void isaln(char *string);
void findocc(char *tosearch, FILE *text);

int main(){
    char seq_total[LEN_SEQ+1], line[201];
    char s_filename[MAXFILE+1], t_filename[MAXFILE+1];
    FILE *sequences, *text, *text_temp;

    /* ask user to enter sequences filename */
    printf("Enter sequences filename: ");
    scanf("%s", s_filename);

    sequences=fopen(s_filename, "r");
    if(sequences==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file %s doesn't exist!\n", s_filename);
        exit(99);
    }

    /* ask user to enter text filename */
    printf("Enter text filename: ");
    scanf("%s", t_filename);
    text=fopen(t_filename, "r");
    if(text==NULL){
        /* if file doesn't exist exit with code error 98 */
        printf("Error: file %s doesn't exist!\n", t_filename);
        exit(98);
    }
    else{
        text_temp=fopen(temp_filename, "w+");
        while(fgets(line, 201, text)!=NULL){
            tolow(line);
            isaln(line);
            fputs(line, text_temp);
            fputs("\n", text_temp);
        }
        rewind(text_temp);
    }

    fscanf(sequences, "%*d\n");
    while(fscanf(sequences, "%s\n", seq_total)==1){
        printf("\nOccurences of '%s':\n", seq_total);
        tolow(seq_total);
        findocc(seq_total, text_temp);
        printf("\n");
    }

    fclose(text_temp);
    remove(temp_filename);
    fclose(sequences);
    fclose(text);

    return EXIT_SUCCESS;
}

void tolow(char *string){
    int i;

    for(i=0 ; i<strlen(string) ; i++)
        string[i]=tolower(string[i]);
}

void isaln(char *string){
    int i;

    for(i=0 ; i<strlen(string) ; i++)
        if(!isalnum(string[i]))
            string[i]=' ';
}

void findocc(char *tosearch, FILE *text_temp){
    int pos=0, tot_occ=0;
    char *ptr;
    char word[MAX+1];

    while(fscanf(text_temp, "%s", word)==1){
        pos++;
        ptr=strstr(word, tosearch);
        if(ptr!=NULL){
            tot_occ++;
            if(tot_occ<=10){
                fputs(word, stdout);
                printf("\t --- \t(pos %d)\n", pos);
            }
        }
    }
    if(!tot_occ)
        printf("No occurrence found!");
    else if(tot_occ>10)
        printf("Displayed 10 occurences of %d!", tot_occ);
    else
        printf("Total occurrence: %d!", tot_occ);

    printf("\n///////////////////////");
    rewind(text_temp);
}
