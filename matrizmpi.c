#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

    clock_t inicio, fim;
    double tempo_execucao;

    // Inicia a medição do tempo
    inicio = clock();
    
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
    
    if(rank == 0){
         int *vet_max;
         int *vet_min;
         int *vet_max_col;
         int *vet_max_row;
         int *vet_min_col;
         int *vet_min_row;
         vet_max = (int*)malloc(size*sizeof(int));
         vet_min = (int*)malloc(size*sizeof(int));
         vet_max_col = (int*)malloc(size*sizeof(int));
         vet_max_row = (int*)malloc(size*sizeof(int));
         vet_min_col = (int*)malloc(size*sizeof(int));
         vet_min_row = (int*)malloc(size*sizeof(int));

         for(int i = 1;i<size;i++){
             
         }
    }else{
         int maxValLocal = matrix[0][0];
         int minValLocal = matrix[0][0];
         int maxrowLocal,maxcolLocal,minrowLocal,mincolLocal;
         int inicio = rank*(row/size);
         int fim
        
         for(int i = inicio;i<fim;i++){
            for(int j = 0;j<col;j++){
            
            }
         }
    }
}
