#include <stdio.h>
#include <stdlib.h>
#include "TILES.h"
#include "BOARD.h"

extern int remaining, actualmax;

void load_board(tiles_boards ***board, tiles *tile, int *nr, int *nc){      // inizializzo la scacchiera sulla base delle
    int i, j, index;                                                        // informazioni presenti all'interno del file
    FILE *f_board;

    f_board=fopen(filename_board, "r");
    if(f_board==NULL){
        /* if file doesn't exist exit with code error 98 */
        printf("Error: file doesn't exist!\n");
        exit(98);
    }
    fscanf(f_board, "%d%d\n", nr, nc);
    remaining=(*nr)*(*nc);

    *board=calloc(*nr, sizeof(tiles_boards *));
    for(i=0 ; i<*nr ; i++)
        (*board)[i]=calloc(*nc, sizeof(tiles_boards));

    for(i=0 ; i<*nr ; i++){
        for(j=0 ; j<*nc ; j++){
            fscanf(f_board, "%d/%d", &index, &(*board)[i][j].rotation);
            if(index!=-1){
                (*board)[i][j].tile=tile[index];
                tile[index].mark=YES;
                (*board)[i][j].editable=NO;
                (*board)[i][j].used=YES;
                remaining--;             /* diminuisco il contatore che indica i posti vuoti della scacchiera man mano che inizializzo */
            }
            else{
                (*board)[i][j].editable=YES;
                (*board)[i][j].rotation=NO;
            }
            if((*board)[i][j].rotation==YES)                /* ruoto gia' durante l'acquisizione le tessere da ruotare */
                rotate(&(*board)[i][j].tile);
        }
    }

    fclose(f_board);
}

void solve(tiles *tile, int total_tiles, tiles_boards **board, tiles_boards **sol, int nr, int nc){
    int i, j, x;
                                                /* funzione ricorsiva di risoluzione */
    if(remaining==0){
        if(checkMax(board, nr, nc))
            writeSol(board, sol, nr, nc);
        return;
    }

    for(x=0 ; x<total_tiles ; x++){
        if(tile[x].mark==NO){
            for(i=0 ; i<nr ; i++){
                for(j=0 ; j<nc ; j++){
                    if(board[i][j].editable==YES && board[i][j].used==NO){
                        board[i][j].used=tile[x].mark=YES;
                        board[i][j].tile=tile[x];
                        remaining--;
                        solve(tile, total_tiles, board, sol, nr, nc);
                        rotate(&board[i][j].tile);
                        solve(tile, total_tiles, board, sol, nr, nc);
                        rotate(&board[i][j].tile);
                        board[i][j].used=tile[x].mark=NO;
                        remaining++;
                    }
                }
            }
        }
    }

    return;
}

int checkMax(tiles_boards **board, int nr, int nc){
    int i, j, error=0, totVal=0, tempVal=0;

    //printBoard(board, nr, nc);

    for(i=0 ; i<nr ; i++){                  /* orizzontale */
        error=0;
        tempVal=0;
        for(j=0 ; j<nc && !error ; j++){
            if(board[i][0].tile.colorOrizz==board[i][j].tile.colorOrizz)
                tempVal+=board[i][j].tile.valueOriz;
            else{
                error=1;
                tempVal=0;
            }
        }
        if(!error)
            totVal+=tempVal;
    }

    for(i=0 ; i<nr ; i++){                  /* verticale */
        error=0;
        tempVal=0;
        for(j=0 ; j<nc && !error; j++){
            if(board[0][i].tile.colorVert==board[j][i].tile.colorVert)
                tempVal+=board[j][i].tile.valueVert;
            else{
                error=1;
                tempVal=0;
            }
        }
        if(!error)
            totVal+=tempVal;
    }

    if(totVal>actualmax){           /* dopo aver calcolato il valore, controllo se supera quello massimo attuale in memoria */
        actualmax=totVal;
        return YES;
    }

    return NO;
}

void writeSol(tiles_boards **board, tiles_boards **sol, int nr, int nc){        /* funzione che trascrive le soluzioni */
    for(int i=0 ; i<nr ; i++)
        for(int j=0 ; j<nc ; j++)
            sol[i][j]=board[i][j];
}

void printBoard(tiles_boards **board, int nr, int nc){          /* funzione di stampa (quasi formattata)*/

    for(int x=0 ; x<nc*8+1 ; x++)
        printf("-");
    printf("\n");
    for(int i=0 ; i<nr; i++){
        for(int j=0 ; j<3 ; j++){
            printf("|");
            for(int colonna=0 ; colonna<nc ; colonna++){
                if(board[i][colonna].used==YES){
                    if(j==0)
                        printf("   %c   |", board[i][colonna].tile.colorVert);
                    else if(j==1)
                        printf("%c     %d|", board[i][colonna].tile.colorOrizz, board[i][colonna].tile.valueOriz);
                    else if(j==2)
                        printf("   %d   |", board[i][colonna].tile.valueVert);
                }
                else
                    printf("       |");
                if(colonna==nc-1)
                    printf("\n");
            }
        }
        for(int x=0 ; x<nc*8+1 ; x++)
            printf("-");
        printf("\n");
    }
}
