#include <stdio.h>
#include <stdlib.h>
#include "Solucao.h"
#include <fstream>

using namespace std;

int main(void){

    // Leitura do numero de vertices e labels.
    std::ifstream file("100_67_20.txt");
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

	//MultiVND:
    Solucao *bestSolMultVND;
    bestSolMultVND = sol.MultiVND(25);
    printf("MELHOR SOLUCAO GERAL MULTI VND: %d\n", bestSolMultVND->aval);

    //VNS
    // Solucao *bestSolVNS;
   //  bestSolVNS = sol.VNS(15);
    // printf("MELHOR SOLUCAO GERAL MULTI VNS: %d\n", bestSolVNS->aval);





        //getchar();

	return 0;
}
