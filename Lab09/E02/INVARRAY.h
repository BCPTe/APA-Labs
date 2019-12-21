#ifndef INVARRAY_H_INCLUDED
#define INVARRAY_H_INCLUDED

#include "INV.h"

#ifndef MAXEQUIP
#define MAXEQUIP 8
#endif // MAXEQUIP

#define filename_inv "inventario.txt"

typedef struct invArray_s *ptr_invArray;

ptr_invArray invIniz();
inv_t *searchObjCMD(ptr_invArray ptr, char *name);
int getIndex(ptr_invArray inventario, char *name);
inv_t getInv(ptr_invArray inventario, int index);
stat_t getStat_index(ptr_invArray inventario, int index);
void stampaInv(ptr_invArray ptr);

#endif // INVARRAY_H_INCLUDED
