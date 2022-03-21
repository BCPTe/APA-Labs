#include <stdio.h>
#include <stdlib.h>
#include "TLIST.h"
#include "TITLE.h"

typedef struct nodeTLIST *linkTLIST;
struct nodeTLIST{
    TITLE title;
    linkTLIST next;
};

struct tlist_s{
    linkTLIST head;
    int tot;
};

/* PROTOTYPES */
static linkTLIST newNODETLIST(linkTLIST next, TITLE title);
static linkTLIST TLISTinsert(linkTLIST head, TITLE title);
/* ---------- */

static linkTLIST newNODETLIST(linkTLIST next, TITLE title){
    linkTLIST x=malloc(sizeof *x);

    x->title=title;
    x->next=next;

    return x;
}

TLIST TLISTload(FILE *fp){
    TLIST tmp;
    int i, totTitle;

    fscanf(fp, "%d\n", &totTitle);
    tmp=TLISTinit();
    for(i=0 ; i<totTitle ; i++){
        tmp->head=TLISTinsert(tmp->head, TITLEread(fp));
        tmp->tot++;
    }

    return tmp;
}

TLIST TLISTinit(){
    TLIST tmp=malloc(sizeof *tmp);

    tmp->head=NULL;
    tmp->tot=0;

    return tmp;
}

static linkTLIST TLISTinsert(linkTLIST head, TITLE title){
    linkTLIST p, x;

    if(head==NULL || TITLEcmp(title, head->title)<0)
        return newNODETLIST(head, title);

    for(p=head, x=head->next ; x!=NULL && TITLEcmp(title, x->title)>=0 ; p=x, x=x->next);
    p->next=newNODETLIST(x, title);

    return head;
}

void TLISTprint(TLIST titoli, int strategy){
    linkTLIST x;

    for(x=titoli->head ; x!=NULL ; x=x->next){
        TITLEprint(x->title, strategy);
        printf("\n");
    }

    return;
}

TITLE TLISTsearch(TLIST titoli, char *toSearch){
    linkTLIST x;

    for(x=titoli->head ; x!=NULL ; x=x->next)
        if(TITLEcmp2(x->title, toSearch)==0)
            return x->title;

    return NULL;
}
