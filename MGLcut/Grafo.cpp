#include "Grafo.h"
#include <stdio.h>

Grafo::Grafo(int nVert, int nl) : M(nVert), L(nVert), n(nVert), nLabels(nl)
{
     for(int i=0; i<this->n; ++i)
           M[i].resize(this->n);
}

