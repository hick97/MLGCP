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
         //matriz separada por cor (Mlij)
       vector< vector< vector<int> > > Ml;
         
       Grafo(int nVert, int nl);

       void AddVirtualEdges(Data *d, int color);
       void DFSUtil(int v, bool visited[]);
       void DFS(int pos,Data *d);
       //void FillsMatrix();
};
