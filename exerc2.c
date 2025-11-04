#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc,char **argv){

    int rank,size;
    int tag = 100;

    MPI_Init(&argc,&argv);

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank == 0){
        FILE *justa;
        MPI_Status status;
        int valor_recebido;
        int total_mensagens = (size-1)*25;

        justa = fopen("justa.txt","w");

        for(int i = 0;i<total_mensagens;i++){
            MPI_Recv(&valor_recebido,1,MPI_INT,MPI_ANY_SOURCE,tag,MPI_COMM_WORLD,&status);
            int mensageiro = status.MPI_SOURCE;
            fprintf(justa,"valor enviado = %d, do processo %d\n",valor_recebido,mensageiro);
        }

        fclose(justa);
    }else{
        for(int i = 0;i<25;i++){
            int mensagem = rank+i;
            MPI_Send(&mensagem,1,MPI_INT,0,tag,MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

    return 0;

}
