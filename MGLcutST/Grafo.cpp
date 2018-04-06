#include "Grafo.h"
#include <stdio.h>
#include <iostream>
using namespace std;

Grafo::Grafo(int nVert, int nl) : M(nVert), L(nVert), Ml(nl), n(nVert), nLabels(nl)
{
     for(int i=0; i<this->n; ++i)
           M[i].resize(this->n);
     
     for(int i=0; i<this->nLabels; ++i)
     {
          Ml[i].resize(this->n);
          for(int j=0; j<this->n; ++j)
               Ml[i][j].resize(this->n);
     }
      
}

void Grafo::DFSVisitColor(int v, int cor, bool visited[])
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
    for (i = Ll[cor][v].begin(); i != Ll[cor][v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);




}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Grafo::DFScolor(int v, int cor, Data *d)
{
    //vector <int> vizinhos;
    //std::vector<int>::iterator *k = vizinhos.begin();

    // Mark all the vertices as not visited
    bool *visited = new bool[this->n];
    for (int i = 0; i < this->n; i++)
        visited[i] = false;

    // Call the recursive helper function
    // to print DFS traversal
     DFSvisitColor(v, cor, visited);
     d->virtualVertex.clear();// Limpa meus vertices encontrados na DFS.
     for(int k = 0;k <this->n;k++){
        if(visited[k] == true){
            d->virtualVertex.push_back(k);
        }
     }
}
//Adicionando minhas arestas virtuais no grafo atual.
void Grafo::AddVirtualEdges(Data *d, int color){
    for(int i= 0; i<d->virtualVertex.size(); i++){
        int &v = d->virtualVertex[i];
        for(int j = i+1; j<d->virtualVertex.size(); j++){
            int &u = d->virtualVertex[j]; 
            if(this->Ml[cor][v][u] == 0){
                printf("Adcionei %d na aresta (%d, %d)\n", color, v, u);
                this->Ml[cor][v][u] = 1;
                this->Ml[cor][u][v] = 1;
                this->Ll[cor][v].push_back(u);
                this->Ll[cor][u].push_back(v);
                
                this->M[v][u].push_back(cor);
                this->M[u][v].push_back(cor);
                if(this->M[v][u].size() == 1)
                {
                     this->L[v].push_back(u);
                     this->L[u].push_back(v);
                }
            }
        }
    }
}

void Grafo::VirtualEdges()
{
    // Grafo original.
    printf("Grafo ORIGINAL:\n");
    for (int i = 0; i < this->g->n; i++) {
            for (int j = 0; j < this->this->n; j++) {
                vector<int> &cores = this->M[i][j];
                 printf("{");
                 for(int c=0; c < cores.size(); ++c)
                    printf("%d ", cores[c]);
                 printf("} ");
            }
            printf("\n");
    }
     
     
     Data *d =  new Data; //Guarda os vertices da minha DFS;
    vector<int>initialPos; // Vertices iniciais para DFS;

    int cor = 0; // Variavell auxiliar (label atual);
    while(cor != this->g->nLabels){ // Percorre todas as minhas labels, montando as matrizes de cada uma.
        // Grafo atual.
        printf("Grafo da cor %d:\n", cor);
        for (int i = 0; i < this->g->n; i++) {
            for (int j = 0; j < this->g->n; j++) {
                printf("%d ", this->Ml[cor][i][j]);

            }
            printf("\n");
        }
        // DFS nas posições inciais capturadas.
        vector<bool> isNewComponent(this->n, true); 
        for(int v = 0; v<this->n; v++){
             if(isNewComponent[v])
             {
               printf("Front: %d\n", v);
               if(this->.Ll[cor][v].size() > 1){ // verifica apenas os vertices com mais de uma vizinhança.
                    this->.DFS(v, d); // DFS.
                    this->AddVirtualEdges(d, cor);
                    printf("Fiz DFS\n");
               }
             }
        }
                aux++; //prox label.
        

    }
   
    printf("Grafo VIRTUAL:\n");
    for (int i = 0; i < this->g->n; i++) {
            for (int j = 0; j < this->this->n; j++) {
                vector<int> &cores = this->M[i][j];
                 printf("{");
                 for(int c=0; c < cores.size(); ++c)
                    printf("%d ", cores[c]);
                 printf("} ");
            }
            printf("\n");
    }
}
