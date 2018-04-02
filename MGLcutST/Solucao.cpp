#include "Solucao.h"
#include <time.h>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#define NO_MOVIMENTS -1
#define LEFT_SIDE 1
#define RIGHT_SIDE 0
#include<vector>

//Recebe um ponteiro para um grafo e inicia cFreq, aval com 0's.
Solucao::Solucao(Grafo *grafo) : cFreq(grafo->nLabels, 0), aval(0), g(grafo)
{
}
//cópia da solução

Solucao::Solucao(Solucao &sol) : cFreq(sol.cFreq), aval(sol.aval), g(sol.g), right(sol.right), left(sol.left)
{
}

void Solucao::VirtualEdges(){
    Data *d =  new Data; //Guarda os vertices da minha DFS;
    vector<int>initialPos; // Vertices iniciais para DFS;

    int aux = 0; // Variavell auxiliar (label atual);
    Grafo gVirtual(this->g->n, this->g->nLabels); // Meu grafo com arestas virtuais;

   // while(aux != this->g->nLabels){ // Percorre todas as minhas labels, montando as matrizes de cada uma.

        Grafo gAtual(this->g->n, this->g->nLabels); // Grafo de label especifica trabalhado atualmente.
        // Percorre minha matriz orginal, indentificando quais vertices apresentam a label atual.
        for (int i = 0; i < this->g->n; i++) {
            for (int j = i; j < this->g->n; j++) {
                // verifica se o indice da matriz = label trabalhada.
                if(this->g->M[i][j] == aux){
                    //Preencho meu grafo de trabalho atual.
                    gAtual.M[i][j] = aux;
                    gAtual.M[j][i] = aux;
                    initialPos.push_back(i); // Capturo as posições inicias da minha DFS.
                    // Preencho lista de adjacencia
                    gAtual.L[i].push_back(j);
                    gAtual.L[j].push_back(i);
                }else{
                    // Sem cor.
                    gAtual.M[i][j] = this->g->nLabels;
                    gAtual.M[j][i] = this->g->nLabels;
                }

            }
        }
        // Grafo atual.
        printf("Grafo da cor %d:\n", aux);
        for (int i = 0; i < this->g->n; i++) {
            for (int j = 0; j < this->g->n; j++) {
                printf("%d ", gAtual.M[i][j]);

            }
            printf("\n");
        }
        // DFS nas posições inciais capturadas.
        for(int k = 0; k<initialPos.size(); k++){
             printf("Front: %d\n", initialPos[k]);
             if(gAtual.L[initialPos[k]].size()>1){ // verifica apenas os vertices com mais de uma vizinhança.
                printf("Fiz DFS\n");
                gAtual.DFS(initialPos[k], d); // DFS.
                gAtual.AddVirtualEdges(d, aux);
             }
             d->virtualVertex.clear();// Limpa meus vertices encontrados na DFS.
        }
        // Somando meu grafos encontrados em cada cor.
        for(int i = 0; i< this->g->n; i++){
            for(int j = i; j< this->g->n; j++){
                // Restrição para nao somar quando ambos estiverem sem cor.

                if((gVirtual.M[i][j] == 0)||((gVirtual.M[i][j] != this->g->nLabels)&&(gAtual.M[i][j] != this->g->nLabels ))) {
                    gVirtual.M[i][j] += gAtual.M[i][j];
                    gVirtual.M[j][i] = gVirtual.M[i][j];
                }else if(gVirtual.M[i][j]== this->g->nLabels){
                    gVirtual.M[i][j] = gAtual.M[i][j];
                    gVirtual.M[j][i] = gVirtual.M[i][j];
                }

            }
        }
      //  aux++; //prox label.
        // Esvazia minhas posições iniciais ao passar para proxima label.
        initialPos.clear();

    //}
    // Grafo original.
    printf("Grafo ORIGINAL:\n");
    for (int i = 0; i < this->g->n; i++) {
            for (int j = 0; j < this->g->n; j++) {
                printf("%d ", this->g->M[i][j]);
            }
            printf("\n");
    }
    printf("Grafo VIRTUAL:\n");
    for (int i = 0; i < gVirtual.n; i++) {
            for (int j = 0; j < gVirtual.n; j++) {
                printf("%d ", gVirtual.M[i][j]);
            }
            printf("\n");
    }
}



