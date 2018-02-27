import java.util.LinkedList;
import java.util.Scanner;

public class Main {
    public static int cNumber = 0;
    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        // Recebe a quantidade de vértices e cores.
        int nVertex = sc.nextInt();
        int nLabels = sc.nextInt();

        // Cria a matriz de adjacencia.
        int[][] Matrix = new int[nVertex][nVertex];

        // Prennche Matriz.
        Matrix = FillsMatrix(nVertex);

        // Divide os vertices em dois grupos. obs: Assumindo uma quantidade de vertices pares.
        int[] leftPart = new int[nVertex / 2];
        int[] rightPart = new int[nVertex / 2];
        int j = 0;
        for (int i = 0; i < nVertex; i++){
            
            if(i<(nVertex/2)){
                leftPart[i] = i;
            }else{
                rightPart[j] = i;
                j++;
            }
        }
//        for (int i = 0; i < nVertex/2; i++){
//        System.out.println("lado esquerdo: "+ leftPart[i]+"\nlado direito: "+ rightPart[i]);
//        }
        //Frequancia de cada cor.
        int[] cFreq = new int[nLabels];
        cFreq = ColorNumber(leftPart, rightPart,Matrix,nLabels);
        
        //Imprime a frequencia.
        System.out.printf("Frequência: ");       
        for (int i = 0; i < nLabels; i++){           
            System.out.printf("%d", cFreq[i]);
        }
        //Imprime o numero de cores:
        System.out.println("\nNumero de cores: "+ cNumber);

    }
    // Metodo que preenche a matriz.
    public static int[][] FillsMatrix(int nVert) {
        Scanner sc = new Scanner(System.in);
        int[][] MatrixP = new int[nVert][nVert];

        for (int i = 0; i < nVert; i++) {
            for (int j = 0; j < nVert; j++) {
                int label = sc.nextInt();
                MatrixP[i][j] = label;

            }

        }

        return MatrixP;

    }
    // Metodo que calcula o numero de cores diferentes entre a parte da direita e esquerda.
    public static int[] ColorNumber (int left[], int right[],int Matrix[][], int nLabels){
        
        // Mede a frequencia das cores.
        int[] cFreq =  new int [nLabels];
        // Preenche a frequencia com zeros.
        for (int i = 0; i < nLabels; i++){
            cFreq[i] = 0;
        }
       //Acessa as listas da esquerda e direita e verifica a frequência de cada cor.
       for (int i = 0; i < left.length; i++) {
            for (int j = 0; j < right.length; j++) {
                int color = Matrix[left[i]][right[j]];
                if(color != nLabels){
                    // verifca se a cor já foi computada.
                    if(cFreq[color]==0){
                        cNumber++;
                        cFreq [color]++;
                    }else{
                        cFreq [color]++;
                    }
                }
                
            }

        }
  
        return cFreq;
    }
}
