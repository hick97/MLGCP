#include <stdio.h>
#include <stdlib.h>
#include "Solucao.h"
#include <fstream>

using namespace std;

int main(void){

    // Leitura do numero de vertices e labels.
    std::ifstream file("matriz.txt");
    if(!file){/*falhou em abrir o arquivo*/}

    int nVertex;
    if(!(file >> nVertex)){/*falhou em ler o primeiro valor*/}

    int nLabels;
    if(!(file >> nLabels)){/*falhou em ler o segundo valor*/}

    //Preenche meu Grafo de acordo com o arquivo.
	Grafo g(nVertex, nLabels);
	for (int i = 0; i < g.n; i++) {
            for (int j = i; j < g.n; j++) {
                if(!(file >> g.M[i][j])) {/*falhou em ler um dos valores*/}

                g.M[j][i] = g.M[i][j];
                //Lista de adjacencia:
                if(g.M[i][j] < g.nLabels)
                {
                    g.L[i].push_back(j);
                    g.L[j].push_back(i);
                }
            }
     }

	Solucao sol(&g);
    Solucao *bestSol;
    bestSol = sol.MultiVND(3);

    printf("MELHOR SOLUCAO GERAL: %d\n", bestSol->aval);


/*
	// Divide os vertices em dois grupos.
        for (int i = 0; i < g.n; i++) {

            if (i < (g.n / 2)) {
                sol.left.push_back(i);
            } else {
                sol.right.push_back(i);

            }
        }
  */
  // Construção aleatória.
  //sol.RandomConstruction();


        //Frequencia de cada cor.
       // sol.f();


/*
        //Struct que recebe posição e lado da melhor f(s').
        Data *d = new Data;
        sol.avalChangePartition(d);
        Solucao *solCopy = new Solucao(sol);

        sol.BestMoviment(solCopy, d);

         //Imprime a frequencia.
        printf("Frequencia pos movimentacao 1: ");
        for (int i = 0; i < g.nLabels; i++) {
            printf("%d,", solCopy->cFreq[i]);
        }
        printf("\n");
        //Imprime o numero de cores:
        printf("Aval: %d \n", solCopy->aval);

        sol.avalInterchangePartition(d);
        Solucao *solCopy2 = new Solucao(sol);
        sol.BestMovimentInterchange(solCopy2, d);

         //Imprime a frequencia.
        printf("Frequencia pos movimentacao 2: ");
        for (int i = 0; i < g.nLabels; i++) {
            printf("%d,", solCopy2->cFreq[i]);
        }
        printf("\n");
        //Imprime o numero de cores:
        printf("Aval: %d \n", solCopy2->aval);


*/






        //getchar();

	return 0;
}
