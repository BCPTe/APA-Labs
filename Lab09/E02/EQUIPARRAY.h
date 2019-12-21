#ifndef EQUIPARRAY_H_INCLUDED
#define EQUIPARRAY_H_INCLUDED

typedef struct equipArray_s *ptr_equipArray;

ptr_equipArray equipIniz();
int updateEquip(ptr_equipArray actual, int index);
int getInUso(ptr_equipArray actual);
int getIndexArray(ptr_equipArray actual, int index);

#endif // EQUIPARRAY_H_INCLUDED
