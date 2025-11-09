#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <mpi.h>

int main(int argc,char **argv){
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
   
    // Inicializa matriz
    //printf("Matrix (%dx%d):\n", rows, cols);

    for (int i = 0; i < rows; i++) {
       for (int j = 0; j < cols; j++) {
           matrix[i][j] = rand() % 100000;  // número randomico entre 0 e 999
           //printf("%3d ", matrix[i][j]);
       }
       //printf("\n");
    }

    // Encontra o valor máximo e mínimo e suas posições na matriz
    int maxVal = matrix[0][0];
    int minVal = matrix[0][0];
    int maxrow, maxcol, minrow, mincol;

    int rank,size;
    int tag = 100; 
      
    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int *vetValoresLocais;
    vetValoresLocais = (int*)malloc(6*sizeof(int));
    for(int i=0;i<6;i++){
        vetValoresLocais[i] = 1;
    }
    vetValoresLocais[3] = INT_MAX;
    int inicio = rank*(rows/size);
    int fim = (rank+1)*(rows/size);
    
    if(rank == 0){
         MPI_Status status;

         double inicio = MPI_Wtime();

         for(int i = inicio;i<fim;i++){
            for(int j = 0;j<cols;j++){
                if (matrix[i][j] > maxVal || matrix[i][j] < minVal)
                {
                    if (matrix[i][j] < minVal){
                        minVal = matrix[i][j];
                        minrow = i;
                        mincol = j;
                    }
                    else if (matrix[i][j] > maxVal){
                        maxVal = matrix[i][j];
                        maxrow = i;
                        maxcol = j; 
                    }
                }
            }
           }

         for(int i = 1;i<size;i++){
             MPI_Recv(vetValoresLocais,6,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
             if(vetValoresLocais[0] > maxVal || vetValoresLocais[3] < minVal){
                    if(vetValoresLocais[0] > maxVal){
                        maxVal = vetValoresLocais[0];
                        maxrow = vetValoresLocais[1];
                        maxcol = vetValoresLocais[2];
                    }
                    else if(vetValoresLocais[3] < minVal){
                        minVal = vetValoresLocais[3];
                        minrow = vetValoresLocais[4];
                        mincol = vetValoresLocais[5];
                    }
             }
         }

         double fim = MPI_Wtime();

         double tempo_total = fim - inicio / CLOCKS_PER_SEC;

         printf("\n O valor máximo é: %d em (%d,%d) e o mínimo é: %d em (%d, %d)\n", maxVal, maxrow, maxcol, minVal, minrow, mincol);
         printf("Tempo de execucao: %f segundos\n", tempo_total); 
         
    }else{
         for(int i = inicio;i<fim;i++){
            for(int j = 0;j<cols;j++){
                if (matrix[i][j] > vetValoresLocais[0] || matrix[i][j] < vetValoresLocais[3])
                {
                    if (matrix[i][j] < vetValoresLocais[3]){
                        vetValoresLocais[3] = matrix[i][j];
                        vetValoresLocais[4] = i;
                        vetValoresLocais[5] = j;
                    }
                    else if (matrix[i][j] > vetValoresLocais[0]){
                        vetValoresLocais[0] = matrix[i][j];
                        vetValoresLocais[1] = i;
                        vetValoresLocais[2] = j;
                    }
                }
            }
         }

         MPI_Send(vetValoresLocais,6,MPI_INT,0,tag,MPI_COMM_WORLD);
    }
    free(vetValoresLocais);

    MPI_Finalize();

    // Libera a memória alocada
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
