#include <vector>
#include "Grafo.h"

using namespace std;

struct Solucao
{
       vector<int> right;

       vector<int> left;

       vector<int> cFreq;

       int aval;
       Grafo *g;


       Solucao(Grafo *grafo);
       Solucao(Solucao &sol);
       int f();
       void leftoright(int a);
       void rightoleft(int b);
       void avalChangePartition(int *v);
};
