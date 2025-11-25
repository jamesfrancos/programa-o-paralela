#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Linha de Comando: %s <rows> <columns>\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);

    if (rows <= 0 || cols <= 0) {
        printf("Linhas e colunas devem ser valores positivos.\n");
        return 1;
    }

    // Criar a semente para os números aleatórios
    //srand((unsigned int)time(NULL));

    // Alocar memória dinamicamente para a matriz
    int **matrix = (int **)malloc(rows * sizeof(int *));
    
    if (matrix == NULL) {
        printf("Não conseguiu alocar memoria!\n");
        return 1;
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)malloc(cols * sizeof(int));
        if (matrix[i] == NULL) {
            printf("Não conseguiu alocar memoria!\n");
            return 1;
        }
    }

    clock_t inicio, fim;
    double tempo_execucao;
    
    // Inicializa matriz
    //printf("Matrix (%dx%d):\n", rows, cols);

     for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100000;  // número randomico entre 0 e 999
            //printf("%3d ", matrix[i][j]);
        }
        //printf("\n");
     }

    inicio = clock();

    // Encontra o valor máximo e mínimo e suas posições na matriz
    int maxVal = matrix[0][0];
    int minVal = matrix[0][0];
    int maxrow, maxcol, minrow, mincol;
    

    #pragma omp parallel
    { 
      int maxValLocal = matrix[0][0];
      int minValLocal = matrix[0][0];
      int maxrowLocal,maxcolLocal,minrowLocal,mincolLocal;
      #pragma omp for nowait
       for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] > maxValLocal || matrix[i][j] < minValLocal)
                {
                    if (matrix[i][j] < minValLocal){
                        minValLocal = matrix[i][j];
                        minrowLocal = i;
                        mincolLocal = j;
                    }
                    else if (matrix[i][j] > maxVal){
                        maxValLocal = matrix[i][j];
                        maxrowLocal = i;
                        maxcolLocal = j;
                    }
                }
          }
        }
       #pragma omp critical
           if(maxValLocal > maxVal || minValLocal < minVal){
                if(maxValLocal > maxVal){
                    maxVal = maxValLocal;
                    maxrow = maxrowLocal;
                    maxcol = maxcolLocal;
                }
                if(minValLocal < minVal){
                    minVal = minValLocal;
                    minrow = minrowLocal;
                    mincol = mincolLocal;
                }
           }
    }

    
    // Finaliza a medição do tempo
    fim = clock();

    // Calcula o tempo de execução em segundos
    tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
   

    printf("\n O valor máximo é: %d em (%d,%d) e o mínimo é: %d em (%d, %d)\n", maxVal, maxrow, maxcol, minVal, minrow, mincol);
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);


    // Libera a memória alocada
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
