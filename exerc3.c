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

    int size,rank;
    int tag = 100;
    int tam = atoi(argv[1]);
    double times[2];
  
    MPI_Init(&argc,&argv);

    double start_time = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(size != 2){
        printf("programa feito para ser executado apenas por dois processos\n");

        exit(1);
    }else{
        if(rank == 0){
            double *vetor_enviado;
            vetor_enviado = (double *)malloc(tam*sizeof(double));
            for(int i = 0;i<tam;i++){
                vetor_enviado[i] = -1.0;
            }

            iterarVetor(2.0,vetor_enviado,tam);

            MPI_Send(vetor_enviado,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);

        }else if(rank == 1){
            double *vetor_recebido;
            MPI_Status status;
            vetor_recebido = (double*)malloc(tam*sizeof(double));
            for(int i = 0;i<tam;i++){
                vetor_recebido[i] = -1.0;
            }
            MPI_Recv(vetor_recebido,tam,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,&status);

            iterarVetor(4.0,vetor_recebido,tam);

            free(vetor_recebido);
        }
    }

    double end_time = MPI_Wtime();

    double time = end_time - start_time;

    times[rank] = time;

    MPI_Finalize();

   if(rank == 1){
      printf("tempo total : %f segundos",times[0]+times[1]);
   }

    return 0;
}