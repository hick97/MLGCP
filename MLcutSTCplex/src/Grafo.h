#include <vector>

using namespace std;

struct Data
{
         vector<int> virtualVertex;
};
struct Grafo
{
       int n, nLabels;
       //Matriz do Fecho cromatico
       vector< vector< vector<int> > > M; 
       // adjacency lists
       vector< vector<int> > L;
         
       //Estruturas separadas por cor
       //matriz (Mlij)
       vector< vector< vector<int> > > Ml;
       //Lista de adjacencia Lli
       vector< vector< vector<int> > > Ll;
         
       Grafo(int nVert, int nl);

       void AddVirtualEdges(Data *d, int color);
       void DFSVisitColor(int v, int c, bool visited[]);
       void DFScolor(int pos, int c, Data *d);
       void VirtualEdges();
       //void FillsMatrix();
};
