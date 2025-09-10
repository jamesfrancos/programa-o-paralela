#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

double a[500][500];
double b[500][500];
double c[500][500];

int main(int argc,char* argv[]){

    int N,i,j,k;
    double start,end;
    struct timeval tstart, tend;

    if (argc > 1) N = atoi(argv[1]);
    else N = 500;

    for (i=0 ;i<N; i++)  
       for (j=0 ;j<N; j++) {
            c[i][j] = 0;
            a[i][j] = 1; //drand48();
            b[i][j] = 1; //drand48();
        }

    gettimeofday(&tstart, NULL);

    #pragma omp parallel default(none) shared(a,b,c,N) private(i,j,k)
    {
        #pragma omp for
        for (i=0; i<N; i++) {
          for (j=0; j<N; j++) 
            for (k=0; k<N; k++) 
                c[i][j] = c[i][j] + a[i][k]*b[k][j];
        }
    }

    gettimeofday(&tend, NULL);
    
    //for (i=0; i<N; i++)
    //    for (j=0; j<N; j++)
    //        printf("C[%d][%d] = %f\n", i, j, c[i][j]);

    printf("%ld microseconds\n", ((tend.tv_sec * 1000000 + tend.tv_usec)
                                - (tstart.tv_sec * 1000000 + tstart.tv_usec)));
}
