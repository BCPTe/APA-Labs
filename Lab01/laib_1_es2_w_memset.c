/*
=============================================================
Name        : laib_X_esX.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_X Exercise X - APA 19/20 PoliTO
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

    /* ask user to enter dest filename */
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
    int i, j, s_max, change;
    char *ptr;
    char delimiter;
    char s_line[201], d_filename[MAX+1], saver[11];
    FILE *dest;
    struct{
        char code[MAX+11];
        char word[MAX+11];
    }word_encode[30];

    printf("Enter destination filename: ");
    scanf("%s", d_filename);

    dest=fopen(d_filename, "w");

    fscanf(thesaurus, "%d\n", &s_max);
    for(i=0 ; i<s_max ; i++)
        fscanf(thesaurus, "%s %s\n", word_encode[i].code, word_encode[i].word);

    while(fscanf(source, "%s%c", s_line, &delimiter)!=EOF){
        for(i=0 ; i<s_max ; i++){
            ptr=strstr(s_line, word_encode[i].word);
            if(ptr!=NULL){
                strcpy(saver, ptr+strlen(word_encode[i].word));
                for(j=0 ; j<strlen(s_line) ; j++){
                    change=word_encode[i].code[j];
                    memset(ptr, change, 1);
                    ptr++;
                }
            }
        }
        strcat(s_line, saver);
        for(j=0 ; j<11 ; j++)
            saver[j]='\0';
        fputs(s_line, dest);
        fputc(delimiter, dest);
    }
    fclose(dest);
    fclose(source);
    fclose(thesaurus);
}
