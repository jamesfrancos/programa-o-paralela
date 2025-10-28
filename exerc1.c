#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char **argv){

    int rank, size;
    int valor_inicial = atoi(argv[1]);
    int tag = 100;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0){
        FILE *arquivo;
        int recvs[size];
        int dest_send = rank+1;
        int valor_recebido;
        MPI_Status status;

        MPI_Send(&valor_inicial,1,MPI_INT,dest_send,tag,MPI_COMM_WORLD);
        arquivo = fopen("arquivo.txt","w");
        fprintf(arquivo,"Identificação = %d valor = %d\n",rank,valor_inicial);
        for(int i = 1;i<size;i++){
            MPI_Recv(&valor_recebido,1,MPI_INT,i,tag,MPI_COMM_WORLD,&status);
            recvs[i] = valor_recebido;
        }

        for(int i = 1;i<size;i++){
            fprintf(arquivo,"Identificação = %d valor = %d\n",i,recvs[i]);
        }
    }else{
        int valor_recebido;
        int dest_recv = rank-1;
        int dest_send = rank+1;
        MPI_Status status;

        MPI_Recv(&valor_recebido,1,MPI_INT,dest_recv,tag,MPI_COMM_WORLD,&status);

        int valor_enviado = valor_recebido+rank; 

        MPI_Send(&valor_enviado,1,MPI_INT,0,tag,MPI_COMM_WORLD);

        if(rank < size-1){
            MPI_Send(&valor_enviado,1,MPI_INT,dest_send,tag,MPI_COMM_WORLD);
        }
    }
  
    MPI_Finalize();
    
    return 0;
}