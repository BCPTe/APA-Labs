#include <stdio.h>
#include <stdlib.h>
#include "TILES.h"

void load_tiles(tiles **tile, int *total_tiles){        /* acquisisco le tessere dal file -- salvate in vettore di strutture */
    int i;
    FILE *f_tiles;

    f_tiles=fopen(filename_tiles, "r");
    if(f_tiles==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }
    fscanf(f_tiles, "%d\n", total_tiles);
    *tile=malloc(*total_tiles*sizeof(tiles));
    for(i=0 ; i<*total_tiles ; i++){
        fscanf(f_tiles, "%c %d %c %d\n", &(*tile)[i].colorOrizz, &(*tile)[i].valueOriz, &(*tile)[i].colorVert, &(*tile)[i].valueVert);
        (*tile)[i].mark=NO;
    }

    fclose(f_tiles);
}

void rotate(tiles *toRotate){           /* funzione di rotazione delle tessere */
    char tmpC;
    int tmpI;

    tmpC=toRotate->colorOrizz;
    toRotate->colorOrizz=toRotate->colorVert;
    toRotate->colorVert=tmpC;
    tmpI=toRotate->valueOriz;
    toRotate->valueOriz=toRotate->valueVert;
    toRotate->valueVert=tmpI;
}
