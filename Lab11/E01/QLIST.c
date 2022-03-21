#include <stdio.h>
#include <stdlib.h>
#include "QLIST.h"
#include "QUOTE.h"
#include "TIME.h"

typedef struct nodeQLIST *linkQLIST;
struct nodeQLIST{
    QUOTE quote;
    linkQLIST l, r;
};

struct qlist_s{
    linkQLIST root;
    linkQLIST z; //nodo sentinella
    int tot;
    float min, max;
};

/* PROTOTYPES */
static linkQLIST newNODEQLIST(QUOTE quote, linkQLIST l, linkQLIST r);
static linkQLIST insertR(linkQLIST root, QUOTE quote, linkQLIST z);
static void QLISTprintR(linkQLIST h, linkQLIST z, int strategy);
static linkQLIST QLISTsearchR(linkQLIST h, TIME data, linkQLIST z);
static int QLISTheightMAXR(linkQLIST h, linkQLIST z);
static int QLISTheightMINR(linkQLIST h, linkQLIST z);
/* ---------- */

static linkQLIST newNODEQLIST(QUOTE quote, linkQLIST l, linkQLIST r){
    linkQLIST x=malloc(sizeof *x);

    x->quote=quote;
    x->l=l;
    x->r=r;

    return x;
}

QLIST QLISTinit(FILE *fp){
    int i;
    QLIST tmp=malloc(sizeof *tmp);

    tmp->z=newNODEQLIST(QUOTEsetNULL(), NULL, NULL);
    tmp->root=tmp->z;
    tmp->min=tmp->max=-1.0;

    fscanf(fp, "%d\n", &tmp->tot);
    for(i=0 ; i<tmp->tot ; i++)
        QLISTinsert_leafR(tmp, QUOTEread(fp));

    return tmp;
}

void QLISTinsert_leafR(QLIST tmp, QUOTE quote){
    tmp->root=insertR(tmp->root, quote, tmp->z);
    if(quote.value>tmp->max)
        tmp->max=quote.value;
    if(quote.value<tmp->min || tmp->min<0)
        tmp->min=quote.value;
    return;
}

static linkQLIST insertR(linkQLIST root, QUOTE quote, linkQLIST z){
    if(root==z)
        return newNODEQLIST(quote, z, z);
    if(TIMEcmp(quote.time, root->quote.time))
        root->l=insertR(root->l, quote, z);
    else
        root->r=insertR(root->r, quote, z);

    return root;
}

void QLISTvisit(QLIST bst, int strategy){
    QLISTprintR(bst->root, bst->z, strategy);

    return;
}

static void QLISTprintR(linkQLIST h, linkQLIST z, int strategy){
    if(h==z)
        return;

    if(strategy==PREORDER)
        QUOTEprint(h->quote);
    QLISTprintR(h->l, z, strategy);
    if(strategy==INORDER)
        QUOTEprint(h->quote);
    QLISTprintR(h->r, z, strategy);
    if(strategy==POSTORDER)
        QUOTEprint(h->quote);

    return;
}

void QLISTsearch(QLIST qts, TIME data){
    linkQLIST x;

    x=QLISTsearchR(qts->root, data, qts->z);
    if(x!=NULL)
        QUOTEprint(x->quote);
    else printf("NOT FOUND IN SELECTED DATE!\n");

    return;
}

static linkQLIST QLISTsearchR(linkQLIST h, TIME data, linkQLIST z){
    if(h==z)
        return NULL;
    if(TIMEdatacmp(h->quote.time, data)==0)
        return h;
    if(TIMEdatacmp(h->quote.time, data)==-1)
        return QLISTsearchR(h->l, data, z);

    return QLISTsearchR(h->r, data, z);
}

float QLISTgetMAX(QLIST qts){
    return qts->max;
}

float QLISTgetMIN(QLIST qts){
    return qts->min;
}

int QLISTgetMAXheight(QLIST qts){
    return QLISTheightMAXR(qts->root, qts->z);
}

int QLISTgetMINheight(QLIST qts){
    return QLISTheightMINR(qts->root, qts->z);
}

static int QLISTheightMAXR(linkQLIST h, linkQLIST z){
    if(h==z)
        return 0;
    int maxL=QLISTheightMAXR(h->l, z);
    int maxR=QLISTheightMAXR(h->r, z);

    return ((maxL>maxR) ? maxL : maxR)+1;
}

static int QLISTheightMINR(linkQLIST h, linkQLIST z){
    if(h==z)
        return 0;
    int minL=QLISTheightMINR(h->l, z);
    int minR=QLISTheightMINR(h->r, z);

    return ((minL<minR) ? minL : minR)+1;
}
