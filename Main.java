import java.util.LinkedList;
import java.util.Scanner;

public class Main {

    public static int cNumber = 0;

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);

        // Recebe a quantidade de vértices e cores.
        int nVertex = sc.nextInt();
        int nLabels = sc.nextInt();
        boolean par;

        // Cria a matriz de adjacencia.
        int[][] Matrix = new int[nVertex][nVertex];

        // Prennche Matriz.
        Matrix = FillsMatrix(nVertex);
        LinkedList<Integer> leftPart = new LinkedList<Integer>();
        LinkedList<Integer> rightPart = new LinkedList<Integer>();
      
        // Divide os vertices em dois grupos.       
        for (int i = 0; i < nVertex; i++) {

            if (i < (nVertex / 2)) {
                leftPart.add(i);
            } else {
                rightPart.add(i);
            
            }
        }
        System.out.println("Parte esquerda: ");
        for (int a : leftPart) {
            System.out.printf("%d", a);

        }
        System.out.println("\nParte direita: ");
        for (int a : rightPart) {
            System.out.printf("%d", a);

        }
        System.out.println("");

        //Frequencia de cada cor.
        int[] cFreq = new int[nLabels];
        cFreq = ColorNumber(leftPart, rightPart, Matrix, nLabels);

        //Imprime a frequencia.
        System.out.printf("Frequência: ");
        for (int i = 0; i < nLabels; i++) {
            System.out.printf("%d", cFreq[i]);
        }
        //Imprime o numero de cores:
        System.out.println("\nNumero de cores: " + cNumber);

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
    public static int[] ColorNumber(LinkedList<Integer> left, LinkedList<Integer> right, int Matrix[][], int nLabels) {

        // Mede a frequencia das cores.
        int[] cFreq = new int[nLabels];
        // Preenche a frequencia com zeros.
        for (int i = 0; i < nLabels; i++) {
            cFreq[i] = 0;
        }
        //Acessa as listas da esquerda e direita e verifica a frequência de cada cor.
        for (int i = 0; i < left.size(); i++) {
            for (int j = 0; j < right.size(); j++) {
                System.out.printf("Comparando: %d com %d\n ", left.get(i), right.get(j));
                int color = Matrix[left.get(i)][right.get(j)];     
                if (color != nLabels) {
                    System.out.println("Cor: "+ color);
                    // verifca se a cor já foi computada.
                    if (cFreq[color] == 0) {
                        cNumber++;
                        cFreq[color]++;
                    } else {
                        cFreq[color]++;
                    }
                }else{
                    System.out.println("Sem cor!");
                }

            }

        }

        return cFreq;
    }
}
