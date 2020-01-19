#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GRAPH.h"
#include "ST.h"

struct node{
    int v; //vertice
    int wt; //peso arco
    link next;
};

struct graph_s{
    int V; //numero vertici
    int E; //numero archi
    int **mAdj; //matrice di adiacenza
    link *lAdj; //lista di adiacenza
    ST tab; //tabella di simboli
    link z; //sentinella (-1,0,NULL)
};

static link newNODE(int v, int wt, link next);
static void GRAPHcreateE(graph_ptr G, int id1, int id2, int wt);
static int **MATRIXint(int righe, int colonne, int val);

static link newNODE(int v, int wt, link next){
    link x=malloc(sizeof *x);

    x->v=v;
    x->wt=wt;
    x->next=next;

    return x;
}

graph_ptr GRAPHload(){
    int V=0, id1, id2, wt;
    char label1[MAXC+1], label2[MAXC+1], net1[MAXC+1], net2[MAXC+1];
    graph_ptr G;
    FILE *fp=fopen(filename, "r");

    if(fp==NULL){
        /* if file doesn't exist exit with code error 99 */
        printf("Error: file doesn't exist!\n");
        exit(99);
    }

    while(fscanf(fp, "%*s%*s%*s%*s%*d\n")!=EOF)
        V++;
    G=GRAPHinit(V);
    rewind(fp);
    while(fscanf(fp, "%s%s%s%s%d", label1, net1, label2, net2, &wt)!=EOF){
        id1=STsearch(G->tab, label1);
        id2=STsearch(G->tab, label2);
        if(id1==-1){
            STinsert(G->tab, label1, net1);
            id1=STsearch(G->tab, label1);
        }
        if(id2==-1){
            STinsert(G->tab, label2, net2);
            id2=STsearch(G->tab, label2);
        }
        if(id1>=0 && id2>=0)
            GRAPHcreateE(G, id1, id2, wt);
    }
    G->V=STcount(G->tab);

    fclose(fp);
    return G;
}

graph_ptr GRAPHinit(int V){
    int i;
    graph_ptr G=malloc(sizeof *G);

    G->E=0;
    G->mAdj=MATRIXint(V, V, 0);
    G->z=newNODE(-1, 0, NULL);
    G->lAdj=malloc(V*sizeof(link));
    for(i=0 ; i<V ; i++)
        G->lAdj[i]=G->z;
    G->tab=STinit(V);

    return G;
}

void GRAPHfree(graph_ptr G){
    int i;

    for(i=0 ; i<G->V ; i++)
        free(G->mAdj[i]);
    free(G->mAdj);

    STfree(G->tab);
    free(G);

    return;
}

static void GRAPHcreateE(graph_ptr G, int id1, int id2, int wt){
    if(G->mAdj[id1][id2]==0)
        G->E++;
    G->mAdj[id1][id2]=wt;
    G->mAdj[id2][id1]=wt;

    return;
}

static int **MATRIXint(int righe, int colonne, int val){
    int **matrix=malloc(righe*sizeof(int *));

    for(int i=0 ; i<righe ; i++){
        matrix[i]=malloc(colonne*sizeof(int));
        for(int j=0 ; j<colonne ; j++)
            matrix[i][j]=val;
    }

    return matrix;
}

void printVertex(graph_ptr G){
    int i, j, actindex;
    char **names=malloc(G->V*sizeof(char *));
    char **namesAdj=malloc((G->V-1)*sizeof(char *));

    for(i=0 ; i<G->V ; i++)
        names[i]=strdup(STsearchByIndex(G->tab, i));
    MergeSort(names, G->V);

    for(i=0 ; i<G->V ; i++){
        actindex=0;
        printf("%s\n", names[i]);
        for(j=0 ; j<G->V ; j++)
            if(G->mAdj[STsearch(G->tab, names[i])][j]!=0)
                namesAdj[actindex++]=strdup(STsearchByIndex(G->tab, j));
        MergeSort(namesAdj, actindex);
        for(j=0 ; j<actindex ; j++){
            printf("----->%s\n", namesAdj[j]);
            free(namesAdj[j]);
        }
        printf("\n");
    }

    return;
}

void print_mAdj(graph_ptr G){
    int i, j;

    printf("---------------\n");
    printf("ADJACENCY MATRIX\n");
    printf("---------------\n\n");

    printf("     ---------------------------------------------------------------------\n");
    printf("INDEX");
    for(i=0 ; i<G->V ; i++)
        printf("%4d ", i);
    printf("\n     ---------------------------------------------------------------------\n");

    for(i=0 ; i<G->V ; i++){
        printf("|%2d |", i);
        for(j=0 ; j<G->V ; j++)
            printf("%4d ", G->mAdj[i][j]);
        printf("\n\n");
    }

    return;
}

void gen_lAdj(graph_ptr G){
    int i, j;

    for(i=0 ; i<G->V ; i++)
        for(j=0 ; j<G->V ; j++)
            if(G->mAdj[i][j]!=0)
                G->lAdj[i]=newNODE(j, G->mAdj[i][j], G->lAdj[i]);

    return;
}

void print_lAdj(graph_ptr G){
    int i;
    link x;

    printf("---------------\n");
    printf("ADJACENCY LIST\n");
    printf("---------------\n");
    for(i=0 ; i<G->V ; i++){
        printf("%s ---> ", STsearchByIndex(G->tab, i));
        if(G->lAdj[i]==G->z)
            printf("NONE RELATED VERTEXES");
        for(x=G->lAdj[i] ; x!=G->z ; x=x->next)
            printf("%s ", STsearchByIndex(G->tab, x->v));
        printf("\n");
    }

    return;
}

void verifySubGraphMAT(graph_ptr G, char vertex[][MAXC+1]){
    int i, j, cnt=0;
    int ind[3];

    for(i=0 ; i<3 ; i++){
        ind[i]=STsearch(G->tab, vertex[i]);
        if(ind[i]==-1){
            printf("Invalid input!\n");
            return;
        }
    }

    for(i=0 ; i<3 ; i++)
        for(j=0 ; j<3 ; j++)
            if(G->mAdj[ind[i]][ind[j]]!=0)
                cnt++;

    printf("------------------------------\n");
    printf("%s un sottografo completo!\n", cnt==6? "E'":"Non e'");
    printf("------------------------------\n");

    return;
}

void verifySubGraphLADJ(graph_ptr G, char vertex[][MAXC+1], int checkLADJ){
    int i, j, cnt=0;
    int ind[3];
    link x;

    if(!checkLADJ)
        gen_lAdj(G);

    for(i=0 ; i<3 ; i++){
        ind[i]=STsearch(G->tab, vertex[i]);
        if(ind[i]==-1){
            printf("Invalid input!\n");
            return;
        }
    }

    for(i=0 ; i<3 ; i++)
        for(x=G->lAdj[ind[i]] ; x!=G->z ; x=x->next)
            for(j=0 ; j<3 ; j++)
                if(x->v==ind[j])
                    cnt++;

    printf("------------------------------\n");
    printf("%s un sottografo completo!\n", cnt==6? "E'":"Non e'");
    printf("------------------------------\n");

    return;
}

/* ALGORITMO DI ORDINAMENTO */
void MergeSort(char **toOrder, int n){
    char **ordered=malloc(n*sizeof(char *));
    for(int i=0 ; i<n ; i++)
        ordered[i]=malloc((MAXC+1)*sizeof(char));

    MergeSortR(toOrder, ordered, 0, n-1);

    return;
}

void MergeSortR(char **toOrder, char **ordered, int l, int r){
    int q=(l+r)/2;
    if(r<=l)
        return;
    MergeSortR(toOrder, ordered, l, q);
    MergeSortR(toOrder, ordered, q+1, r);
    Merge(toOrder, ordered, l, q, r);

    return;
}

void Merge(char **toOrder, char **ordered, int l, int q, int r){
    int i=l, j=q+1, k;

    for(k=l ; k<=r ; k++)
        if(i>q)
            ordered[k]=toOrder[j++];
        else if(j>r)
            ordered[k]=toOrder[i++];
        else if(strcmp(toOrder[i], toOrder[j])<=0)
            ordered[k]=toOrder[i++];
        else
            ordered[k]=toOrder[j++];
    for(k=l ; k<=r ; k++)
        toOrder[k]=ordered[k];

    return;
}
/* ------------------------ */
