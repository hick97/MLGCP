#include "Solucao.h"
#include <time.h>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#define NO_MOVIMENTS -1
#define LEFT_SIDE 1
#define RIGHT_SIDE 0
#include<vector>

//Recebe um ponteiro para um grafo e inicia cFreq, aval com 0's.
Solucao::Solucao(Grafo *grafo) : cFreq(grafo->nLabels, 0), aval(0), g(grafo)
{
}
//cópia da solução

Solucao::Solucao(Solucao &sol) : cFreq(sol.cFreq), aval(sol.aval), g(sol.g), right(sol.right), left(sol.left)
{
}




