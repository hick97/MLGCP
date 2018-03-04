#include <stdio.h>
#include <stdlib.h>
#include "Solucao.h"

using namespace std;

int main(void){
	// Recebe a quantidade de vértices e cores.
	int nVertex;
	int nLabels;
	scanf("%d %d", &nVertex, &nLabels);

	Grafo g(nVertex, nLabels);

	// Prennche Matriz.
	g.FillsMatrix();
	
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
            printf("%d", sol.cFreq[i]);
        }
        //Imprime o numero de cores:
        printf("\nNumero de cores: %d \n", sol.aval);
        
        getchar();

	return 0;
}
