#include "Solucao.h"
#include<stdio.h>
#include <iostream>

//Recebe um ponteiro para um grafo e inicia cFreq, aval com 0's.
Solucao::Solucao(Grafo *grafo) : cFreq(grafo->nLabels, 0), aval(0), g(grafo)
{
}
// Encontra o meu aval.
int Solucao::f()
{
    this->aval = 0;
	//Acessa as listas da esquerda e direita e verifica a frequência de cada cor.
	for (int i = 0; i < this->left.size(); i++) {
		for (int j = 0; j < this->right.size(); j++) {
			printf("Comparando: %d com %d\n ", this->left[i], this->right[j]);
			int color = this->g->M[left[i]][right[j]];
			if (color != this->g->nLabels) {
				printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				} else {
					this->cFreq[color]++;
				}
			}else{
				printf("Sem cor!\n");
			}
          }

      }
      return this->aval;
}
// Movimento esquerda-direta.
void Solucao::leftoright (int pos){
    printf("Movimento ESQUERDA-DIREITA\n");
// Garantindo que meu iterador sempre ficará no inicio do vector.
    this->it2 = this->left.begin();
    // Referenciando posição a ser apagada.
    it2 = it2 + pos;

    // Adciona na direita e o apaga na esquerda
    this->right.push_back(this->left[pos]);
    this->left.erase(this->it2);

    // verifica as ligações com o lado esquerdo.
    for(int i = 0; i<this->left.size();i++){
            // Recebe a "cor" do ultimo elemento da direita e compara com a esquerda.
            int color = this->g->M[right[right.size()-1]][left[i]];
        //Incrementação do aval e frequencia.
            if (color != this->g->nLabels) {
               // printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				}else{
                    this->cFreq[color]++;
				}
            }
    }
    //Verifica as ligações com o lado direito.
    for(int i = 0; i<this->right.size();i++){

           int color = this->g->M[right[right.size()-1]][right[i]];

        //Decrementação do aval e frequencia.
        if (color != this->g->nLabels) {
            this->cFreq[color]--;
            // verifica se a frequencia da cor foi pra zero, caso positivo, decremento aval.
            if(cFreq[color]==0){
                this->aval--;
            }
        }

    }
    return;

}
//Movimento direita-esquerda.
void Solucao::rightoleft (int pos){
    printf("Movimento DIREITA-ESQUERDA: \n");
// Garantindo que meu iterador sempre ficará no inicio do vector.
   this->it = this->right.begin();
// Referenciando a posição a ser apagada.
    it = it + pos;

    this->left.push_back(this->right[pos]);
    this->right.erase(this->it);

    // verifica as ligações com o lado direito.
    for(int i = 0; i<this->right.size();i++){

            int color = this->g->M[left[left.size()-1]][right[i]];

    //Incrementação do aval e frequencia.
            if (color != this->g->nLabels) {
                //printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				}else{
                    this->cFreq[color]++;
				}
            }
    }
    //Verifica as ligações com o lado esquerdo.
    for(int i = 0; i<this->left.size();i++){

        int color = this->g->M[left[left.size()-1]][left[i]];

//Decrementação do aval e frequencia.
        if (color != this->g->nLabels) {
            this->cFreq[color]--;
            // verifica se a frequencia da cor foi pra zero, caso positivo, decremento aval.
            if(cFreq[color]==0){
                this->aval--;
            }
        }

    }
    return;

}
