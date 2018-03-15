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

	// Divide os vertices em dois grupos.
        for (int i = 0; i < g.n; i++) {

            if (i < (g.n / 2)) {
                sol.left.push_back(i);
            } else {
                sol.right.push_back(i);

            }
        }
        printf("Parte esquerda: \n");
        for (int i = 0; i < sol.left.size(); i++) {
            printf("%d", sol.left[i]);

        }
        printf("\nParte direita: \n");
        for (int i = 0; i < sol.right.size(); i++) {
            printf("%d", sol.right[i]);

        }
        printf("\n");

        //Frequencia de cada cor.
        sol.f();

        //Imprime a frequencia.
        printf("Frequencia: ");
        for (int i = 0; i < g.nLabels; i++) {
            printf("%d,", sol.cFreq[i]);
        }
        printf("\n");
        //Imprime o numero de cores:
        printf("Aval: %d \n", sol.aval);
        //Struct que recebe posi��o e lado da melhor f(s').

        sol.avalChangePartition();

        Solucao *solCopy = new Solucao(sol);
        sol.BestMoviment(solCopy);
        //printf("%d, %d", fsl[0], fsl[1]);


        //Imprime a frequencia.
        printf("Frequencia pos movimentacao: ");
        for (int i = 0; i < g.nLabels; i++) {
            printf("%d,", solCopy->cFreq[i]);
        }
        printf("\n");
        //Imprime o numero de cores:
        printf("Aval: %d \n", solCopy->aval);





        //getchar();

	return 0;
}
