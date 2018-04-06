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
		vector<int>  posInitial;  
		int cor;
                if(!(file >> cor) {/*falhou em ler um dos valores*/}

                //Lista de adjacencia:
                if(cor < g.nLabels)
                {
         	    g.M[i][j].push_back(cor);
		    g.M[j][i].push_back(cor);
		    
		    g.Ml[cor][i][j] = 1;
		    g.Ml[cor][j][i] = 1;
			
		    g.L[i].push_back(j);
                    g.L[j].push_back(i);
				
		    g.Ll[cor][i].push_back(j);
                    g.Ll[cor][j].push_back(i);
                }else
		{
		    g.Ml[cor][i][j] = 0;
		    g.Ml[cor][j][i] = 0;
		
		}
            }
     }



	Solucao sol(&g);
	sol.VirtualEdges();





        //getchar();

	return 0;
}
