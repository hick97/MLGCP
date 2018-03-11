#include <vector>
#include "Grafo.h"

using namespace std;

struct Solucao
{
       vector<int> right;
       std::vector<int>::iterator it;
       vector<int> left;
       std::vector<int>::iterator it2;
       vector<int> cFreq;

       int aval;
       Grafo *g;


       Solucao(Grafo *grafo);
       int f();
       void leftoright(int a);
       void rightoleft(int b);
       void avalChangePartition(int *v);
};
