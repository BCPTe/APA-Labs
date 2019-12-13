#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include "TILES.h"

#define filename_board "board.txt"

typedef struct{
    tiles tile;
    int rotation, used, editable;
}tiles_boards;

void load_board(tiles_boards ***board, tiles *tile, int *nr, int *nc);
void solve(tiles *tile, int total_tiles, tiles_boards **board, tiles_boards **sol, int nr, int nc);
int checkMax(tiles_boards **board, int nr, int nc);
void writeSol(tiles_boards **board, tiles_boards **sol, int nr, int nc);
void printBoard(tiles_boards **board, int nr, int nc);

#endif // BOARD_H_INCLUDED
