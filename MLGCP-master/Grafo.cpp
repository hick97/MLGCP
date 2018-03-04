#include "Grafo.h"

Grafo::Grafo(int nVert, int nl) : M(nVert), L(nVert), n(nVert), nLabels(nl)
{
     for(int i=0; i<this->n; ++i)
           M[i].resize(this->n);
}

void Grafo::FillsMatrix()
{
     for (int i = 0; i < this->n; i++) {
            for (int j = 0; j < this->n; j++) {
                int label;
                scanf("%d", &label);
                this->M[i][j] = label;
                if(this->M[i][j] < this->nLabels)
                {
                    this->L[i].push_back(j);
                    this->L[j].push_back(i);
                }
            }
     }
     return;
}
