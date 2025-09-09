#include <stdio.h>
#include <math.h>
#include <sys/time.h> 
#define N 1000000

int main(){
    struct timeval start_time, end_time;
    long elapsed_milliseconds;

    float a[N],b[N];
    int i,n;
    n = N;
    float temp,csum;
    csum = 0.0;

    gettimeofday(&start_time, NULL);

    for(i = 0 ; i < n ; i++){
        temp = a[i]/b[i];
        csum += cos(temp);
    }

    gettimeofday(&end_time, NULL);

    elapsed_milliseconds = (double)((end_time.tv_sec - start_time.tv_sec) * 1000000 +
                                   (end_time.tv_usec - start_time.tv_usec)) / 1000.0;


    printf("Tempo de execucao: %f milisegundos\n", elapsed_milliseconds);

    return 0;
}
