#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void iterarVetor(double valor,double *vetor,int tam){
    for(int i = 0;i<tam;i++){
        vetor[i] = valor;
    }
}

int main(int argc,char **argv){

    if(argc != 3){
        printf("falta de argumentos para a execucao\n");

        exit(1);
    }

    int size,rank;
    int tag = 100;
    int tam = atoi(argv[1]);
    int trocas = atoi(argv[2]);
  
    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(size != 2){
        printf("programa feito para ser executado apenas por dois processos\n");

        exit(1);
    }else{
        MPI_Status status;
        double *vetor;
        vetor = (double *)malloc(tam*sizeof(double));
        iterarVetor(-1.0,vetor,tam);

        if(rank == 0){
            iterarVetor(2.0,vetor,tam);

            double inicio = MPI_Wtime();

            for(int i=0;i<trocas;i++){
                MPI_Send(vetor,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
                MPI_Recv(vetor,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD,&status);
            }

            double fim = MPI_Wtime();

            double tempo_total = fim - inicio;

            printf("tempo total: %f segundos\n",tempo_total);

        }else if(rank == 1){
            for(int i=0;i<trocas;i++){
                MPI_Recv(vetor,tam,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,&status);
                iterarVetor(4.0,vetor,tam);
                MPI_Send(vetor,tam,MPI_DOUBLE,0,tag,MPI_COMM_WORLD);
            }
        }

        free(vetor);
    }
    MPI_Finalize();

    return 0;
}

