#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char **argv){

    int rank,size;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        FILE *justa;
        MPI_Status status;
        int valor_recebido;

        justa = fopen("justa.txt","w");

        for(int i = 0;i<size*100;i++){
            MPI_Recv(&valor_recebido,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
            int mensageiro = status.MPI_SOURCE;
            fprintf(justa,"valor enviado = %d, do processo %d\n",valor_recebido,mensageiro);
        }
    }else{
        for(int i = 0;i<100;i++){
            int mensagem = rank+i;
            MPI_Send(&mensagem,1,MPI_INT,0,MPI_ANY_TAG,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;

}
