#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#define filename_tiles "tiles.txt"

enum{NO, YES};

typedef struct{
    char colorOrizz, colorVert;
    int valueOriz, valueVert;
    int mark;
}tiles;

void load_tiles(tiles **tile, int *total_tiles);
void rotate(tiles *toRotate);

#endif // TILES_H_INCLUDED
