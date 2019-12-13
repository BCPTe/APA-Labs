/*
=============================================================
Name        : laib_8_es2.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_8 Exercise 2 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "TILES.h"
#include "BOARD.h"

int remaining=0, actualmax=0;

int main(){
    int nr, nc, total_tiles;
    tiles *tile;
    tiles_boards **board, **sol;

    load_tiles(&tile, &total_tiles);
    load_board(&board, tile, &nr, &nc);

    sol=malloc(nr*sizeof(tiles_boards *));
    for(int i=0 ; i<nr; i++)
        sol[i]=malloc(nr*sizeof(tiles_boards));

    printf("Starting board:\n\n");
    printBoard(board, nr, nc);

    solve(tile, total_tiles, board, sol, nr, nc);

    printf("\nSolved board:\n\n");
    printBoard(sol, nr, nc);
    printf("VALUE: %d!\n", actualmax);

    return EXIT_SUCCESS;
}
