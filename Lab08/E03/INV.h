#ifndef INV_H_INCLUDED
#define INV_H_INCLUDED

#define MAX 50
#define MAXEQUIP 8

#define filename_invent "inventario.txt"

typedef struct{
    char nameObj[MAX+1], clasObj[MAX+1];
    int hpObj, mpObj, atkObj, defObj, magObj, sprObj;
}inv_t;

typedef struct{
    inv_t *vettInv;
    int nInv, maxInv;
}tabInv_t;

tabInv_t *ObjIniz(tabInv_t *object);
void searchObj(tabInv_t *inventario);
void showObject(tabInv_t *inventario);

#endif // INV_H_INCLUDED
