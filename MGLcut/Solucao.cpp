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
// Garantindo que meus iteradores sempre ficaram no inicio do vector.
    this->it = this->right.begin();
    this->it2 = this->left.begin();
// Verifica se a posição para adicionar é valida, caso não seja adiciona no final do vector;
if(pos<right.size()){
// Fazendo meus iteradores apontarem para a posição desejada.
for (this->it=this->right.begin(); this->it<this->right.end(); it++){
        if(*it == right[pos]){
            break;
        }
}
for (this->it2=this->left.begin(); this->it2<this->left.end(); it2++){
        if(*it2 == left[pos]){
            break;
        }
}
    // Insiro no lado direito.
    this->right.insert(this->it,this->left[pos]);
    // Removo no lado esquerdo.
    this->left.erase(this->it2);
}else{
    //Posição da esquerda que será apagada.
    for (this->it2=this->left.begin(); this->it2<this->left.end(); it2++){
        if(*it2 == left[pos]){
            break;
        }
}
    this->right.push_back(this->left[pos]);
    this->left.erase(this->it2);
}
    // verifica as ligações com o lado esquerdo.
    for(int i = 0; i<this->left.size();i++){
            printf("Comparando o elemento com lado esquerdo: \n");
            //printf("Comparando: %d com %d\n ", this->right[pos], this->left[i]);
             // Verifica se o vertice movimentado está no final do vector.
            int color = 0;
            if(pos<right.size()){
                 color = this->g->M[right[pos]][left[i]];
            }else{
                color = this->g->M[right[right.size()-1]][left[i]];
            }

            if (color != this->g->nLabels) {
                printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				}else{
                    this->cFreq[color]++;
				}
            }else{
				printf("Sem cor!\n");
			}
    }
    //Verifica as ligações com o lado direito.
    for(int i = 0; i<this->right.size();i++){
        printf("Comparando elemento com lado direito: \n");
        //printf("Comparando: %d com %d\n ", this->right[pos], this->right[i]);
        // Verifica se o vertice movimentado está no final do vector.
        int color = 0;
        if(pos<right.size()){
           color = this->g->M[right[pos]][right[i]];
        }else{
           color = this->g->M[right[right.size()-1]][right[i]];
        }

        if (color != this->g->nLabels) {
            this->cFreq[color]--;
            // verifica se a frequencia da cor foi pra zero, caso positivo, decremento aval.
            if(cFreq[color]==0){
                this->aval--;
            }
        }else{
            printf("Sem cor!\n");
        }

    }
    return;

}
//Movimento direita-esquerda.
void Solucao::rightoleft (int pos){
    printf("Movimento DIREITA-ESQUERDA: \n");
// Garantindo que meus iteradores sempre ficaram no inicio do vector.
    this->it = this->right.begin();
    this->it2 = this->left.begin();
// Verifica se a posição para adicionar é valida, caso não seja adiciona no final do vector;
if(pos<left.size()){
// Fazendo meus iteradores apontarem para a posição desejada.
for (this->it=this->right.begin(); this->it<this->right.end(); it++){
        if(*it == right[pos]){
            break;
        }
}
for (this->it2=this->left.begin(); this->it2<this->left.end(); it2++){
        if(*it2 == left[pos]){
            break;
        }
}

    // Insiro no lado esquerdo.
    this->left.insert(this->it2,this->right[pos]);
    // Removo no lado direito.
    this->right.erase(this->it);
}else{
    //ponteiro para elemento da direita que será apagado.
    for (this->it=this->right.begin(); this->it<this->right.end(); it++){
        if(*it == right[pos]){
            break;
        }
}
    this->left.push_back(this->right[pos]);
    this->right.erase(this->it);
}
    // verifica as ligações com o lado direito.
    for(int i = 0; i<this->right.size();i++){
            printf("Comparando o elemento com lado direito: \n");
            printf("Estamos falando no n: %d e n: %d\n", this->left[0], this->left[1]);
            //printf("Comparando: %d com %d\n ", this->left[pos], this->right[i]);
            int color = 0;
            // Verifica se o vertice movimentado está no final do vector.
            if(pos<left.size()){
                color = this->g->M[left[pos]][right[i]];
            }else{
                color = this->g->M[left[left.size()-1]][right[i]];
            }

            if (color != this->g->nLabels) {
                printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				}else{
                    this->cFreq[color]++;
				}
            }else{
				printf("Sem cor!\n");
			}
    }
    //Verifica as ligações com o lado esquerdo.
    for(int i = 0; i<this->left.size();i++){
        printf("Comparando elemento com lado esquerdo: \n");
        //printf("Comparando: %d com %d\n ", this->left[pos], this->left[i]);
        int color = 0;
        // Verifica se o vertice movimentado está no final do vector.
            if(pos<left.size()){
                color = this->g->M[left[pos]][left[i]];
            }else{
                color = this->g->M[left[left.size()-1]][left[i]];
            }

        if (color != this->g->nLabels) {
            this->cFreq[color]--;
            // verifica se a frequencia da cor foi pra zero, caso positivo, decremento aval.
            if(cFreq[color]==0){
                this->aval--;
            }
        }else{
            printf("Sem cor!\n");
        }

    }
    return;

}
