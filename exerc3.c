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
    int trocas = atoi(argv[2]);
    double times[2];

    if(argc != 3){
        printf("quantidade de argumentos invalida");
        return 1;
    }
  
    MPI_Init(&argc,&argv);

    double start_time = MPI_Wtime();

    MPI_Comm_size(MPI_COMM_WORLD,&size);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(size != 2){
        printf("programa feito para ser executado apenas por dois processos\n");

        exit(1);
    }else{
        if(rank == 0){
            double *vetor_procs1;
            vetor_procs1 = (double *)malloc(tam*sizeof(double));
            for(int i = 0;i<tam;i++){
                vetor_procs1[i] = -1.0;
            }
         
            MPI_Status status;

            iterarVetor(2.0,vetor_procs1,tam);

            MPI_Send(vetor_procs1,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);   
          
           // for(int i=0;i<trocas;i++){
           //     MPI_Recv(vetor_procs1,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD,&status);
           //     iterarVetor(2.0,vetor_procs1,tam);
           //     MPI_Send(vetor_procs1,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
           // }

            free(vetor_procs1);

        }else if(rank == 1){
            double *vetor_procs2;
            MPI_Status status;
            vetor_procs2 = (double*)malloc(tam*sizeof(double));
            for(int i = 0;i<tam;i++){
                vetor_procs2[i] = -1.0;
            }
  
            MPI_Recv(vetor_procs2,tam,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,&status);

            iterarVetor(4.0,vetor_procs2,tam);
 
           // MPI_Send(vetor_procs2,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
            
            //for(int i=0;i<trocas;i++){
                //MPI_Recv(vetor_procs2,tam,MPI_DOUBLE,0,tag,MPI_COMM_WORLD,&status);
               // iterarVetor(4.0,vetor_procs2,tam);
              //  if(i < trocas-1){
             //      MPI_Send(vetor_procs2,tam,MPI_DOUBLE,1,tag,MPI_COMM_WORLD);
            //    }
           // }
          //  free(vetor_procs2);
        }
    }

    double end_time = MPI_Wtime();

    double time = end_time - start_time;

    times[rank] = time;

    MPI_Finalize();

   if(rank == 1){
      printf("tempo total : %f segundos\n",times[0]+times[1]);
   }

    return 0;
}
