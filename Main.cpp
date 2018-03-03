#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
// Metodo que preenche a matriz.
void FillsMatrix(int nVert, int** MatrixP) {

        for (int i = 0; i < nVert; i++) {
            for (int j = 0; j < nVert; j++) {
                int label;
                scanf("%d", &label);
                MatrixP[i][j] = label;

            }

        }

        return;

    }
// Metodo que calcula o numero de cores diferentes entre a parte da direita e esquerda.
int ColorNumber(vector<int> left, vector<int> right, int** Matrix, int nLabels, int *cFreq) {
    int cNumber = 0;
	// Preenche a frequencia com zeros.
	for (int i = 0; i < nLabels; i++) {
		cFreq[i] = 0;
	}
	//Acessa as listas da esquerda e direita e verifica a frequ�ncia de cada cor.
	for (int i = 0; i < left.size(); i++) {
		for (int j = 0; j < right.size(); j++) {
			printf("Comparando: %d com %d\n ", left[i], right[j]);
			int color = Matrix[left[i]][right[j]];
			if (color != nLabels) {
				printf("Cor: %d\n", color);
				// verifca se a cor j� foi computada.
				if (cFreq[color] == 0) {
					cNumber++;
					cFreq[color]++;
				} else {
					cFreq[color]++;
				}
			}else{
				printf("Sem cor!\n");
			}
            }

        }

        return cNumber;
    }

int main(void){
	// Recebe a quantidade de v�rtices e cores.
	int nVertex;
	int nLabels;
	scanf("%d %d", &nVertex, &nLabels);

	// Cria a matriz de adjacencia.
	int **Matrix;
    Matrix = new int *[nVertex];
    for(int i = 0; i <nVertex; i++){
       Matrix[i] = new int[nVertex];
    }

	// Prennche Matriz.
	FillsMatrix(nVertex, Matrix);
	vector<int> leftPart;
	vector<int> rightPart;

	// Divide os vertices em dois grupos.
        for (int i = 0; i < nVertex; i++) {

            if (i < (nVertex / 2)) {
                leftPart.push_back(i);
            } else {
                rightPart.push_back(i);

            }
        }
        printf("Parte esquerda: \n");
        for (int i = 0; i < leftPart.size(); i++) {
            printf("%d", leftPart[i]);

        }
        printf("\nParte direita: \n");
        for (int i = 0; i < rightPart.size(); i++) {
            printf("%d", rightPart[i]);

        }
        printf("\n");

        //Frequencia de cada cor.
        int *cFreq;
        cFreq = new int [nLabels];
        int cNumber = ColorNumber(leftPart, rightPart, Matrix, nLabels, cFreq);

        //Imprime a frequencia.
        printf("Frequencia: ");
        for (int i = 0; i < nLabels; i++) {
            printf("%d", cFreq[i]);
        }
        //Imprime o numero de cores:
        printf("\nNumero de cores: %d \n", cNumber);



	return 0;
}