/*
=============================================================
Name        : laib_5_es1.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_5 Exercise 1 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>

#define filename "brani.txt"
#define MAX 255

typedef struct{
    char **songs;
    int num_songs;
}friend;

int printplaylist(int pos, int total_friends, friend *friends, char **sol, int count);

int main(){
    int i, j, total_friends;
    char **playlist;
    FILE *fp;
    friend *friends;

    fp=fopen(filename, "r");
    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    fscanf(fp, "%d\n", &total_friends);
    friends=calloc(total_friends, sizeof(friend));
    playlist=calloc(total_friends, sizeof(char *));

    for(i=0 ; i<total_friends ; i++){
        fscanf(fp, "%d\n", &friends[i].num_songs);
        friends[i].songs=calloc(friends[i].num_songs, sizeof(char *));
        for(j=0 ; j<friends[i].num_songs ; j++){
            friends[i].songs[j]=calloc(MAX, sizeof(char));
            fscanf(fp, "%s\n", friends[i].songs[j]);
        }
    }

    printf("Printed all %d possible playlists!\n", printplaylist(0, total_friends, friends, playlist, 0));

    /* free previously allocated dynamic memory */
    for(i=0 ; i<total_friends ; i++){
        for(j=0 ; j<friends[i].num_songs ; j++)
            free(friends[i].songs[j]);
        free(friends[i].songs);
    }
    free(friends);
    free(playlist);

    return EXIT_SUCCESS;
}

int printplaylist(int pos, int total_friends, friend *friends, char **sol, int count){
    int i;

    if(pos>=total_friends){
        printf("Sol %d:\n", count+1);
        printf("---------------\n");
        for(i=0 ; i<total_friends ; i++)
            printf("Friend %d --> %s\n", i+1, sol[i]);
        printf("---------------\n");
        printf("\n");
        return count+1;
    }
    for(i=0 ; i<friends[pos].num_songs ; i++){
        sol[pos]=friends[pos].songs[i];
        count=printplaylist(pos+1, total_friends, friends, sol, count);
    }

    return count;
}
