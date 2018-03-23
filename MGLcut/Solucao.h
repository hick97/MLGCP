#include <vector>
#include "Grafo.h"

using namespace std;
struct Data
{
         int pos = 0;
         int side = 0;
         int leftPosInter = 0;
         int rightPosInter = 0;
};

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
       void avalChangePartition(Data *d);
       void avalInterchangePartition(Data *d2);
       int BestMoviment(Solucao *solCopy, Data *d);
       int BestMovimentInterchange(Solucao *solCopy, Data *d2);
       void RandomConstruction();
       void VND(Solucao *s, Data *d3);
       Solucao* MultiVND(int iter);
       void Srand();

};




