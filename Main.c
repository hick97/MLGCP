#include <stdio.h>
#include <vector>


static int cNumber = 0;
int main(void){
	// Recebe a quantidade de vértices e cores.
	int nVertex;
	int nLabels;
	scanf("%d %d", &nVertex, &nLabels);

	// Cria a matriz de adjacencia.
	int Matrix[nVertex][nVertex];
	// Prennche Matriz.
	Matrix = FillsMatrix(nVertex);
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
        int cFreq[nLabels];
        cFreq = ColorNumber(leftPart, rightPart, Matrix, nLabels);

        //Imprime a frequencia.
        printf("Frequência: ");
        for (int i = 0; i < nLabels; i++) {
            printf("%d", cFreq[i]);
        }
        //Imprime o numero de cores:
        printf("\nNumero de cores: \n", cNumber);



	return 0;
}
// Metodo que preenche a matriz.
    public static int[][] FillsMatrix(int nVert) {

        int[][] MatrixP = new int[nVert][nVert];

        for (int i = 0; i < nVert; i++) {
            for (int j = 0; j < nVert; j++) {
                int label;
                scanf("%d", &label);
                MatrixP[i][j] = label;

            }

        }

        return MatrixP;

    }
// Metodo que calcula o numero de cores diferentes entre a parte da direita e esquerda.
int[] ColorNumber(vector<int> left, vector<int> right, int Matrix[][], int nLabels) {

	// Mede a frequencia das cores.
	int cFreq[nLabels];

	// Preenche a frequencia com zeros.
	for (int i = 0; i < nLabels; i++) {
		cFreq[i] = 0;
	}
	//Acessa as listas da esquerda e direita e verifica a frequência de cada cor.
	for (int i = 0; i < left.size(); i++) {
		for (int j = 0; j < right.size(); j++) {
			printf("Comparando: %d com %d\n ", left[i], right[i]);
			int color = Matrix[left[i]][right[i]];
			if (color != nLabels) {
				printf("Cor: \n", color);
				// verifca se a cor já foi computada.
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

        return cFreq;
    }
