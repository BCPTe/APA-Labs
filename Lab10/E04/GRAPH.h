#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define filename "grafo.txt"

#ifndef MAXC
#define MAXC 30
#endif // MAXC

typedef struct graph_s *graph_ptr;
typedef struct node *link;

typedef struct{
    int v; //vertice partenza
    int w; //vertice arrivo
    int peso; //peso arco
}Edge;

graph_ptr GRAPHload();
graph_ptr GRAPHinit(int V);
void GRAPHfree(graph_ptr G);
void printVertex(graph_ptr G);
void print_mAdj(graph_ptr G);
void gen_lAdj(graph_ptr G);
void print_lAdj(graph_ptr G);
void verifySubGraphMAT(graph_ptr G, char vertex[][MAXC+1]);
void verifySubGraphLADJ(graph_ptr G, char vertex[][MAXC+1], int checkLADJ);
/* ORDINAMENTO */
void MergeSort(char **toOrder, int n);
void MergeSortR(char **toOrder, char **ordered, int l, int r);
void Merge(char **toOrder, char **ordered, int l, int q, int r);
/* ----------- */

#endif // GRAPH_H_INCLUDED
