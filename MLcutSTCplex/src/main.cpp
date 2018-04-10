#include <stdio.h>
#include <stdlib.h>
#include "Solucao.h"
#include <fstream>
#include <ilcplex/ilocplex.h>


using namespace std;

void solveModel(Grafo &g)
{
	IloEnv env;
	IloModel modelo(env);


	//###############Variáveis do Modelo###################
	IloNumVarArray z(env, g.nLabels, 0, 1);

	char var[100];
	//Variável t que indica o tempo de início de cada operação
	for (int i = 0; i < g.nLabels; i++) {
		sprintf(var, "z(%d)", (int)i);           	
		z[i].setName(var);		
		modelo.add(z[i]);
	}

	//Variável x, booleana que indica, se igual a 1, que a operação i precede a operação j.
	IloBoolVarArray x(env, g.n);
	
	for (int i = 0; i < g.n; i++) {
		sprintf(var, "x(%d)", (int)i);           	
		x[i].setName(var);		
		modelo.add(x[i]);
	}

 	
	//Função objetivo
	IloExpr ExObj(env);
	for(int l=0; l<g.nLabels; ++l)
		ExObj += z[l];

	modelo.add(IloMinimize(env, ExObj));
	ExObj.end();


	//Restrições

	for(int i =0; i<g.n;i++){
		for(int j =0; j<g.n;j++){
			if(g.M[i][j].size()>0){
				IloExpr zlij(env);
				for(int k=0; k<g.M[i][j].size();k++){
					int l = g.M[i][j][k];				
					zlij += z[l]; 			
				}
				modelo.add(zlij - (g.M[i][j].size() -1) >= x[i] - x[j]);
				modelo.add(zlij - (g.M[i][j].size() -1) >= x[j] - x[i]);
				
			}	
		}	
	}

	IloCplex MLCutST(modelo);

	MLCutST.solve();

}


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
                if(!(file >> cor)) {/*falhou em ler um dos valores*/}

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

	
	solveModel(g);




        //getchar();

	return 0;
}
