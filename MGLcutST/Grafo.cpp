#include "Grafo.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Grafo::Grafo(int nVert, int nl) : M(nVert), L(nVert), n(nVert), nLabels(nl)
{
     for(int i=0; i<this->n; ++i)
           M[i].resize(this->n);
}

void Grafo::DFSUtil(int v, bool visited[])
{

    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v << " ";
    printf("\n");
   // vizinhos.push_back(v);



    // Recur for all the vertices adjacent
    // to this vertex
    std::vector<int>::iterator i;
    for (i = L[v].begin(); i != L[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);




}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Grafo::DFS(int v, Data *d)
{
    //vector <int> vizinhos;
    //std::vector<int>::iterator *k = vizinhos.begin();

    // Mark all the vertices as not visited
    bool *visited = new bool[this->n];
    for (int i = 0; i < this->n; i++)
        visited[i] = false;

    // Call the recursive helper function
    // to print DFS traversal
     DFSUtil(v, visited);
     for(int k = 0;k <this->n;k++){
        if(visited[k] == true){
            d->virtualVertex.push_back(k);
        }
     }
}
//Adicionando minhas arestas virtuais no grafo atual.
void Grafo::AddVirtualEdges(Data *d, int color){
    for(int i= 0; i<d->virtualVertex.size(); i++){
        for(int j= i; j<d->virtualVertex.size(); j++){
            if((this->M[d->virtualVertex[i]][d->virtualVertex[j]] != color) && (d->virtualVertex[i] != d->virtualVertex[j])){
                printf("Adcionei %d entre os vertices %d e %d\n", color, d->virtualVertex[i], d->virtualVertex[j]);
                this->M[d->virtualVertex[i]][d->virtualVertex[j]] = color;
            }
        }
    }
}

