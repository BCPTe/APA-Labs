/*
=============================================================
Name        : laib_10_es4.c
Author      : BCPTe
Version     : 1.0
Copyright   : ++NONE++
Description : Laib_10 Exercise 4 - APA 19/20 PoliTO
=============================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "GRAPH.h"

int main(){
    int cmd, checkLADJ=0;
    char vertexToCheck[3][MAXC+1];
    graph_ptr grafo=GRAPHload();

    printf("\tMENU'\n");
    printf("1) STAMPA IN ORDINE ALFABETICO\n");
    printf("2) STAMPA MATRICE DI ADIACENZA\n");
    printf("3) GENERA/STAMPA LISTA DI ADIACENZA\n");
    printf("4) VERIFICA SOTTOGRAFO COMPLETO\n");
    printf("0) ESCI\n\n");

    do{
        printf("Enter command: ");
        scanf("%d", &cmd);

        switch(cmd){
            case 1:
                printVertex(grafo);
                break;
            case 2:
                print_mAdj(grafo);
                break;
            case 3:
                if(!checkLADJ){
                    gen_lAdj(grafo);
                    checkLADJ=1;
                }
                print_lAdj(grafo);
                break;
            case 4:
                printf("Enter the names of 3 vertexes: ");
                for(int i=0 ; i<3 ; i++)
                    scanf("%s", vertexToCheck[i]);
                //verifySubGraphMAT(grafo, vertexToCheck);
                verifySubGraphLADJ(grafo, vertexToCheck, checkLADJ);
                break;
            case 0:
                printf("Closing in progress...\n\n");
                break;
            default:
                printf("Invalid command!\n");
        }
    }while(cmd!=0);
    
    GRAPHfree(grafo);
    
    return EXIT_SUCCESS;
}
