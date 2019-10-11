/*
=============================================================
Name        : laib_1_es2_wo_memset.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_1 Exercise 2 w/o memset - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

void encode(FILE *source, FILE *dest);

int main(){
    char s_filename[MAX+1], t_filename[MAX+1];
    FILE *source, *thesaurus;

    /* ask user to enter source filename */
    printf("Enter source filename: ");
    scanf("%s", s_filename);

    source=fopen(s_filename, "r");
    if(source==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file %s doesn't exist!\n", s_filename);
        exit(99);
    }

    /* ask user to enter thesaurus filename */
    printf("Enter thesaurus filename: ");
    scanf("%s", t_filename);
    thesaurus=fopen(t_filename, "r");
    if(thesaurus==NULL){
        /* if file doesn't exist exit with code error 98 */
        printf("Error: file %s doesn't exist!\n", t_filename);
        exit(98);
    }

    encode(source, thesaurus);

    return EXIT_SUCCESS;
}

void encode(FILE *source, FILE *thesaurus){
    int i, j, found, s_max;
    char *ptr;
    char delimiter;
    char s_line[201], d_filename[MAX+1], modified[31]={0};
    FILE *dest;
    struct{
        char code[MAX+11];
        char word[MAX+11];
    }word_encode[30];
    
    /* ask user to enter dest filename */
    printf("Enter destination filename: ");
    scanf("%s", d_filename);

    dest=fopen(d_filename, "w");

    fscanf(thesaurus, "%d\n", &s_max);
    for(i=0 ; i<s_max ; i++)
        fscanf(thesaurus, "%s %s\n", word_encode[i].code, word_encode[i].word);

    while(fscanf(source, "%s%c", s_line, &delimiter)!=EOF){
        found=0;
        for(i=0 ; i<s_max && !found ; i++){
            ptr=strstr(s_line, word_encode[i].word);
            if(ptr!=NULL){
                found=1;
                strncpy(modified, s_line, ptr-s_line);
                strcat(modified, word_encode[i].code);
                strcat(modified, ptr+strlen(word_encode[i].word));
                strcpy(s_line, modified);
            }
        }
        for(j=0 ; j<31 ; j++)
            modified[j]='\0';
        fputs(s_line, dest);
        fputc(delimiter, dest);
    }
    fclose(dest);
    fclose(source);
    fclose(thesaurus);
}
