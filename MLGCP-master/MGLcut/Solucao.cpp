#include "Solucao.h"
#include<stdio.h>
#include <iostream>
#define NO_MOVIMENTS -1
#define LEFT_SIDE 1
#define RIGHT_SIDE 0

//Recebe um ponteiro para um grafo e inicia cFreq, aval com 0's.
Solucao::Solucao(Grafo *grafo) : cFreq(grafo->nLabels, 0), aval(0), g(grafo)
{
}
//cópia da solução

Solucao::Solucao(Solucao &sol) : cFreq(sol.cFreq), aval(sol.aval), g(sol.g), right(sol.right), left(sol.left)
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
    std::vector<int>::iterator it2 = this->left.begin();
    // Referenciando posição a ser apagada.
    it2 = it2 + pos;

    // Adciona na direita e o apaga na esquerda
    this->right.push_back(this->left[pos]);
    this->left.erase(it2);

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
    std::vector<int>::iterator it = this->right.begin();
// Referenciando a posição a ser apagada.
    it = it + pos;

    this->left.push_back(this->right[pos]);
    this->right.erase(it);

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

void Solucao::avalChangePartition(Data *d){
    int menor = this->aval; // Assumindo que o menor é meu aval da solução original;
    int ladoF = -1; // Assumind0 que -1 é o lado da solução original.
    int posF = -1;// Assumind0 que -1 é a pos da solução original.

    // for que percorre todos os vertices da esquerda.
    for(int i = 0; i<this->left.size();i++){
        vector<int> cFreqCopy = this-> cFreq; // vector de cópia. se der errado faz um for.
        int fS = 0; // variavel que recebe a f(s').
        int newColors = 0;// cores novas.
        int cRemoved = 0; // cores removidas.
        int lado = 1;// Assumimos que ele começa no lado direito.
        int pos = i; // posição em que se encontra meu elemento .

        printf("LADO: %d, POS: %d\n", lado, pos);
        // Caso ele esteja no lado esquerdo indo para o direito:
        // Verifica existencia de ligações com elementos da esquerda.
            for(int j=0; j<this->left.size();j++){

                int color = this->g->M[left[pos]][left[j]];
        //Incrementação do aval e frequencia.
                if (color != this->g->nLabels) {
                   // printf("Cor: %d\n", color);
                    // verifca se a cor já foi computada.
                    if (cFreqCopy[color] == 0) {

                        newColors++;
                        cFreqCopy[color]++;
                    }else{
                        cFreqCopy[color]++;
                    }
                }
            }
            // Verifica a existencia de ligações com elementos da direita.
            for(int j = 0; j<this->right.size();j++){

               int color = this->g->M[left[pos]][right[j]];
                //Cores removidas.
                if (color != this->g->nLabels) {
                    cFreqCopy[color]--;
                    // verifica se a frequencia da cor foi pra zero, caso positivo, incremento cores removidas.
                    if(cFreqCopy[color]==0){

                        cRemoved++;
                    }
                }
            }

            printf("Calculo do fs: %d + %d - %d\n", this->aval, newColors , cRemoved);
        // Calculo da minha f(s'):
            fS = (this->aval + newColors - cRemoved);
            printf("Minha f(s') atual: %d\n", fS);

            if(fS <= menor){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posF = pos; // Posição da menor f(s').
                ladoF = lado; // lado da menor f(s').
            }
    }


    // Caso ele esteja no lado direito indo para o esquerdo:
    // for que percorre os vertices da direita.
       for(int i = 0; i<this->right.size();i++){
            vector<int> cFreqCopy = this-> cFreq; // vector de cópia. se der errado faz um for.
            int fS = 0; // variavel que recebe a f(s').
            int newColors = 0;// cores novas.
            int cRemoved = 0; // cores removidas.
            int lado = 0;// Assumimos que ele começa no lado direito.
            int pos = i; // posição em que se encontra meu elemento .

            // Verifica existencia de ligações com elementos da direita.
            for(int j=0; j<this->right.size();j++){

                int color = this->g->M[right[pos]][right[j]];
            //Incrementação do aval e frequencia.
                if (color != this->g->nLabels) {
                   // printf("Cor: %d\n", color);
                    // verifca se a cor já foi computada.
                    if (cFreqCopy[color] == 0) {
                        newColors++;
                        cFreqCopy[color]++;
                    }else{
                        cFreqCopy[color]++;
                    }
                }
            }
            // Verifica a existencia de ligações com elementos da direita.
            for(int j = 0; j<this->left.size();j++){
               int color = this->g->M[right[pos]][left[j]];
                //Cores removidas.
                if (color != this->g->nLabels) {
                    cFreqCopy[color]--;
                    // verifica se a frequencia da cor foi pra zero, caso positivo, incremento cores removidas.
                    if(cFreqCopy[color]==0){
                        cRemoved++;
                    }
                }
            }
            printf("Calculo do fs: %d + %d - %d\n", this->aval, newColors , cRemoved);
            // Calculo da minha f(s'):
            fS = (this->aval + newColors - cRemoved);
            printf("Minha f(s') atual: %d\n", fS);

            if(fS <= menor){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posF = pos; // Posição da menor f(s').
                ladoF = lado; // lado da menor f(s').
            }


       }

        printf("Minha menor f(s') tem valor: %d, POS: %d e lado: %d\n", menor, posF, ladoF);
        d->lado = ladoF; // retorna o lado .
        d->pos = posF;
       // printf("Lado: %d, pos: %d\n", d->lado, d->pos);


}
void Solucao::avalInterchangePartition(Data *d){
    int menor = this->aval; // Assumindo que o menor é meu aval da solução original;
    int posEsqF = -1;// Assumind0 que -1 é a pos da solução original.
    int posDirF = -1;// Assumind0 que -1 é a pos da solução original.

    //For que faz as combinações necessarias.
    for (int i = 0; i < this->left.size(); i++) {
		for (int j = 0; j < this->right.size(); j++) {
            vector<int> cFreqCopy = this-> cFreq; // vector de cópia. se der errado faz um for.
            int fS = 0; // variavel que recebe a f(s').
            int newColors = 0;// cores novas.
            int cRemoved = 0; // cores removidas.
            int posEsq = i;
            int posDir = j;
            // Comparação com os elementos da esquerda.
            for (int k = 0; k < this->left.size(); k++){
                // Recebe a "cor" do elemento da esquerda e compara com a esquerda.
                int color = this->g->M[left[posEsq]][left[k]];
                //Recebe a "cor" do elemento da direita e compara com a esquerda.
                int color2 = this->g->M[right[posDir]][left[k]];
                //Incrementação do aval e frequencia para o elemento que está indo da esquerda pra direita.
                if (color != this->g->nLabels) {
                    // verifca se a cor já foi computada.
                    if (this->cFreq[color] == 0) {
                        this->aval++;
                        this->cFreq[color]++;
                    }else{
                        this->cFreq[color]++;
                    }
                }
                //Decrementação do aval e frequencia para o elemento que está indo da direita pra esquerda.
                if(color2 != this->g->nLabels){
                    cFreqCopy[color2]--;
                    // verifica se a frequencia da cor foi pra zero, caso positivo, incremento cores removidas.
                    if(cFreqCopy[color2]==0){
                        cRemoved++;
                    }
                }

            }
            // Comparação com os elementos da direita.
            for (int k = 0; k < this->right.size(); k++){
                // Recebe a "cor" do elemento da direta e compara com a direita.
                int color = this->g->M[right[posDir]][right[k]];
                //Recebe a "cor" do elemento da esquerda e compara com a direita.
                int color2 = this->g->M[left[posEsq]][right[k]];
                //Incrementação do aval e frequencia para o elemento que está indo da direta pra esquerda.
                if (color != this->g->nLabels) {
                    // verifca se a cor já foi computada.
                    if (this->cFreq[color] == 0) {
                        this->aval++;
                        this->cFreq[color]++;
                    }else{
                        this->cFreq[color]++;
                    }
                }
                //Decrementação do aval e frequencia para o elemento que está indo da esquerda pra direita.
                if(color2 != this->g->nLabels){
                    cFreqCopy[color2]--;
                    // verifica se a frequencia da cor foi pra zero, caso positivo, incremento cores removidas.
                    if(cFreqCopy[color2]==0){
                        cRemoved++;
                    }
                }

            }
            //Calculo minha f(s') antes de incrementar meu lado direito.
            printf("Calculo do fs entre as posições %d e %d: %d + %d - %d\n", this->left[i], this->right[j], this->aval, newColors , cRemoved);
            // Calculo da minha f(s'):
            fS = (this->aval + newColors - cRemoved);
            printf("Minha f(s') atual: %d\n", fS);

            if(fS <= menor){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posEsqF = posEsq; // Posição da esquerda da menor f(s').
                posDirF = posDir; // Posição da direita da menor f(s').
            }
		}
            //Calculo minha f(s') antes de incrementar meu lado esquerdo.
            printf("Calculo do fs entre as posições %d e %d: %d + %d - %d\n", this->left[i], this->right[j], this->aval, newColors , cRemoved);
            // Calculo da minha f(s'):
            fS = (this->aval + newColors - cRemoved);
            printf("Minha f(s') atual: %d\n", fS);

            if(fS <= menor){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posEsqF = posEsq; // Posição da esquerda da menor f(s').
                posDirF = posDir; // Posição da direita da menor f(s').
            }
    }
     printf("Minha menor f(s') tem valor: %d, POS: %d e lado: %d\n", menor, posF, ladoF);
        d->leftPosInter = posEsqF; // Posição da esquerda da menor f(s').
        d->rightPosInter = posDirF;// Posição da direita da menor f(s').
}
// Função que retorna uma cópia da minha f(s) com a movimentação adequada.
void Solucao::BestMoviment(Solucao *solCopy, Data *d){
    //printf("Lado: %d, pos: %d\n", d->lado, d->pos);
    //Teste: mudança na posição do f(s'):
        // Caso o menor valor seja propria f(s'):
        if(d->lado == NO_MOVIMENTS){
            printf("Minha f(s') eh minha propria f(s).\n");
        }else if(d->lado == LEFT_SIDE){// left -> right
            solCopy->leftoright(d->pos);
        }else if(d->lado == RIGHT_SIDE){//right -> left
            solCopy->rightoleft(d->pos);
        }
}
void Solucao::BestMovimentInterchange(Solucao *solCopy, Data *d){
    //printf("Lado: %d, pos: %d\n", d->lado, d->pos);
    //Teste: mudança na posição do f(s'):
        // Caso o menor valor seja propria f(s'):
        if(d->leftPosInter == NO_MOVIMENTS){
            printf("Minha f(s') eh minha propria f(s).\n");
        }else{
            solCopy->leftoright(d->leftPosInter);
            solCopy->rightoleft(d->rightPosInter);
        }



}
