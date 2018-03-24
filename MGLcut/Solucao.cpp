#include "Solucao.h"
#include <time.h>
#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
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
    //this->aval = 0;
    // Devido a chamada sucessiva da função.

	//Acessa as listas da esquerda e direita e verifica a frequência de cada cor.
	for (int i = 0; i < this->left.size(); i++) {
		for (int j = 0; j < this->right.size(); j++) {
			printf("Comparando: %d com %d\n ", this->left[i], this->right[j]);
			int color = this->g->M[left[i]][right[j]];
			if (color != this->g->nLabels) {
				//printf("Cor: %d\n", color);
				// verifca se a cor já foi computada.
				if (this->cFreq[color] == 0) {
					this->aval++;
					this->cFreq[color]++;
				} else {
					this->cFreq[color]++;
				}
			}else{
				//printf("Sem cor!\n");
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
    int ladoF = NO_MOVIMENTS; // Assumind0 que -1 é o lado da solução original.
    int posF = NO_MOVIMENTS;// Assumind0 que -1 é a pos da solução original.

    if(this->left.size()>1){
    // for que percorre todos os vertices da esquerda.
    for(int i = 0; i<this->left.size();i++){
        vector<int> cFreqCopy = this-> cFreq; // vector de cópia. se der errado faz um for.
        int fS = this->aval; // variavel que recebe a f(s').
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


        // Verifica o menor e garante que um dos lados nao zere.
            if((fS < menor) && (fS != 0)){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posF = pos; // Posição da menor f(s').
                ladoF = lado; // lado da menor f(s').
            }
    }
    }

    // Caso ele esteja no lado direito indo para o esquerdo:
    // for que percorre os vertices da direita.
       if(this->right.size()>1){
       for(int i = 0; i<this->right.size();i++){
            vector<int> cFreqCopy = this-> cFreq; // vector de cópia. se der errado faz um for.
            int fS = this->aval; // variavel que recebe a f(s').
            int newColors = 0;// cores novas.
            int cRemoved = 0; // cores removidas.
            int lado = 0;// Assumimos que ele começa no lado direito.
            int pos = i; // posição em que se encontra meu elemento .

            printf("LADO: %d, POS: %d\n", lado, pos);

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

        // Verifica o menor e garante que um dos lados nao zere.
            if(fS < menor && fS != 0){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posF = pos; // Posição da menor f(s').
                ladoF = lado; // lado da menor f(s').
            }


       }
       }

        printf("Minha menor f(s') tem valor: %d, POS: %d e lado: %d\n", menor, posF, ladoF);
        d->side = ladoF; // retorna o lado .
        d->pos = posF;
        //printf("Lado: %d, pos: %d\n", d->lado, d->pos);


}
void Solucao::avalInterchangePartition(Data *d2){
    int menor = this->aval; // Assumindo que o menor é meu aval da solução original;
    int posEsqF = NO_MOVIMENTS;// Assumind0 que -1 é a pos da solução original.
    int posDirF = NO_MOVIMENTS;// Assumind0 que -1 é a pos da solução original.

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
                    if (cFreqCopy[color] == 0) {
                        newColors++;
                        cFreqCopy[color]++;
                    }else{
                        cFreqCopy[color]++;
                    }
                }
                //Decrementação do aval e frequencia para o elemento que está indo da direita pra esquerda.
                if((color2 != this->g->nLabels)&& (color2 != this->g->M[right[posDir]][left[posEsq]])){
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
                    if (cFreqCopy[color] == 0) {
                        newColors++;
                        cFreqCopy[color]++;
                    }else{
                        cFreqCopy[color]++;
                    }
                }
                //Decrementação do aval e frequencia para o elemento que está indo da esquerda pra direita.
                if((color2 != this->g->nLabels)&&(color2 != this->g->M[right[posDir]][left[posEsq]])){
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

            if(fS < menor){
                printf("%d eh menor ou igual do que %d\n", fS, menor);
                menor = fS; // minha menor f(s) passa a ser f(s').
                posEsqF = posEsq; // Posição da esquerda da menor f(s').
                posDirF = posDir; // Posição da direita da menor f(s').
            }
		}

    }
     printf("Minha menor f(s') tem valor: %d, POS esq: %d e pos Dir: %d\n", menor, posEsqF, posDirF);
        d2->leftPosInter = posEsqF; // Posição da esquerda da menor f(s').
        d2->rightPosInter = posDirF;// Posição da direita da menor f(s').
}
// Função que retorna uma cópia da minha f(s) com a movimentação adequada.
int Solucao::BestMoviment(Data *d){
    //printf("Lado: %d, pos: %d\n", d->lado, d->pos);
    //Teste: mudança na posição do f(s'):
        // Caso o menor valor seja propria f(s'):
        if(d->side == NO_MOVIMENTS){
            return NULL;
        }else if(d->side == LEFT_SIDE){// left -> right
            this->leftoright(d->pos);
        }else if(d->side == RIGHT_SIDE){//right -> left
            this->rightoleft(d->pos);
        }
       return 1;
}
int Solucao::BestMovimentInterchange(Data *d2){
    //printf("Lado: %d, pos: %d\n", d->lado, d->pos);
    //Teste: mudança na posição do f(s'):
        // Caso o menor valor seja propria f(s'):
        if(d2->leftPosInter == NO_MOVIMENTS){
            return NULL;

        }else{
            this->leftoright(d2->leftPosInter);
             //Imprime a frequencia.
        printf("Frequencia pos movimentacao: ");
        for (int i = 0; i < this->g->nLabels; i++) {
            printf("%d,", this->cFreq[i]);
        }
        printf("\n");
            this->rightoleft(d2->rightPosInter);
             //Imprime a frequencia.
        printf("Frequencia pos movimentacao: ");
        for (int i = 0; i < this->g->nLabels; i++) {
            printf("%d,", this->cFreq[i]);
        }
        printf("\n");

        }
        return 1;
}
void Solucao::Srand(){
     //inicializando função randômica
     srand(time(NULL));
}
void Solucao::RandomConstruction (){

	// Variavel que decide quanto elementos irao pra esquerda.
	int x = 1+(rand()%(this->g->n -2));
	printf("X = %d\n", x);

	//declaração das variáveis
	int vetor[x];
	int i=0, j=0;

	//preenchendo vetor com numero aleatorios.
	for(i=0; i<x; i++)
	{
		vetor[i] = (rand()%this->g->n);

		//verificando se o número já existe, afim de evitar elementos repetidos

		for(j=0; j<i; j++)
		{
			if(vetor[j] == vetor[i]|| vetor[0] == vetor[i])
			{
				vetor[i] = (rand()%this->g->n);
				j=0;
			}
		}
	}

    // Preenche meu vetor da esquerda.
	for(i=0; i<x; i++)
	{
	    this->left.push_back(vetor[i]);
	    //printf("left[%d] = %d\n", i, this->left[i]);
	}
    // Preenche meu vetor da direita.
    for (i=0; i<this->g->n;i++){
        int aux = 0;

        for(int j=0; j<this->left.size(); j++){
       // printf("Comparando :%d com %d\n", this->left[j], i );
          if(this->left[j] == i){
            aux = 1;
            break;
          }
        }
        // Caso não esteja no vetor da esquerda:
        if (aux == 0){
            this->right.push_back(i);
        }

    }

}


Solucao* Solucao::MultiVND(int iter){
    Solucao *bestGlobal;
    // Só pode ser inicializado uma vez.
    this->Srand();
    for(int i=0; i< iter; i++){
        Solucao *solCopy = new Solucao(this->g);
        solCopy->RandomConstruction();
        solCopy->f();
        if(solCopy->aval == 0){
            abort();
        }
        printf("Parte esquerda: \n");
        for (int i = 0; i < solCopy->left.size(); i++) {
            printf("%d", solCopy->left[i]);

        }
        printf("\nParte direita: \n");
        for (int i = 0; i < solCopy->right.size(); i++) {
            printf("%d", solCopy->right[i]);

        }
        printf("\n");


        //Imprime a frequencia.
        printf("Frequencia: ");
        for (int i = 0; i < solCopy->g->nLabels; i++) {
            printf(" %d,", solCopy->cFreq[i]);
        }
        printf("\n");
        //Imprime o numero de cores:
        printf("Aval: %d \n", solCopy->aval);


        Data *d = new Data;
        solCopy->VND(d);

        // Definindo a primeira VND como melhor solução.
        if(i==0){
             bestGlobal = solCopy;
        }

        printf("GLOBAL: %d // VND: %d\n", bestGlobal->aval, solCopy->aval);
        if(solCopy->aval < bestGlobal->aval){
            bestGlobal = solCopy;
        }
    }
    return bestGlobal;
}
void Solucao::VND(Data *d){
    //Solucao *solCopy = new Solucao(this);

    while(1){
        while(1){
            printf("Movimentacao simples:\n");
            this->avalChangePartition(d);

            if(this->BestMoviment(d) == NULL){
                break;
            }

        }
        printf("Movimentacao Dupla:\n");
        this->avalInterchangePartition(d);

        if(this->BestMovimentInterchange(d)== NULL){
            break;

            printf("Melhor aval encontrado na VND: %d", this->aval);

        }

    }
    //return solCopy;
}

void Solucao::SimpleDisturbance(){

	int side = (rand()% 2); // Decide o lado a ser pertubado.
	//printf("Side: %d\n", side);
	int pos = NULL; // Variavel que armazena a posição a ser movimentada;

	if(side == 1){
        pos = (rand()% this->left.size()); // Escolhe uma posição aleatoria;
       // printf("pos random esq: %d\n", pos);
        if(this->left.size()!=1){ // Para não zerar um dos lados.
            printf("MOV PARA DIR\n");
            this->leftoright(pos);
        }else{
          //  printf("MOV PARA ESQ\n");
            this->rightoleft(pos);
        }

	}else{
         pos = (rand()% this->right.size()); // Escolhe uma posição aleatoria;
        // printf("pos random dir: %d\n", pos);
         if(this->right.size()!=1){ // Para não zerar um dos lados.
           // printf("MOV PARA ESQ\n");
            this->rightoleft(pos);
        }else{
         //   printf("MOV PARA DIR\n");
            this->leftoright(pos);
        }
	}

}
void Solucao::DoubleDisturbance(){

   int posLeft = (rand()% this->left.size()); // Escolhe uma posição aleatoria esquerda;
   int posRight = (rand()% this->right.size()); // Escolhe uma posição aleatoria direita;
   //printf("POS ESQ: %d // POS DIR: %d\n", posLeft, posRight);

   this->leftoright(posLeft);
   this->rightoleft(posRight);

}
Solucao* Solucao::VNS(int notImprove){
        Solucao *bestGlobalVNS;
        Data *d = new Data;
        int aux = 0, aux2 = 0,aux3 = 0; // Variaveis auxiliares.
        int percentage = ceil(0.1*this->g->n); // Numero de chamadas das pertubações.
        printf("Porcentagem: %d\n", percentage);
        this->Srand();
        //Solucao *solCopy = new Solucao(this->g);
        this->RandomConstruction();
        this->f();
        while(aux != notImprove){
            while(1){
                 printf("Nao melhora simples: %d\n", aux);
                //Chamando pertubação simples.
                printf("Pertubacao simples!\n");
                for(int i = 0; i< percentage;i++){
                    this->SimpleDisturbance();
                }
                this->VND(d);
                // Definindo a primeira VND como melhor solução.
                if(aux2==0){
                     bestGlobalVNS = this;
                     aux2++;
                }
                printf("GLOBAL: %d // VNS: %d\n", bestGlobalVNS->aval, this->aval);
                if(this->aval < bestGlobalVNS->aval){ // Se minha nova solução encontrada é melhor que a global.
                    bestGlobalVNS = this;
                    aux = 0;
                }else{
                    aux++;
                }
                if(aux == notImprove){
                    aux = 0;
                    break;
                }
            }
            while(1){
                printf("Nao melhora dupla: %d\n", aux);
                //Chamando pertubação Dupla.
                printf("Pertubacao dupla!\n");
                for(int i = 0; i< percentage;i++){
                    this->DoubleDisturbance();
                }
                this->VND(d);
                printf("GLOBAL: %d // VNS: %d\n", bestGlobalVNS->aval, this->aval);
                if(this->aval < bestGlobalVNS->aval){ // Se minha nova solução encontrada é melhor que a global.
                    bestGlobalVNS = this;
                    aux = 0;
                    break;
                }else{
                    aux++;
                }
                if(aux == notImprove){
                    break;
                }
            }


    }
    return bestGlobalVNS;
}

