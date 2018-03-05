#include <vector>

using namespace std;

struct Grafo
{
       int n, nLabels;
       vector< vector<int> > M;
       vector< vector<int> > L;

       Grafo(int nVert, int nl);
       //void FillsMatrix();
};
