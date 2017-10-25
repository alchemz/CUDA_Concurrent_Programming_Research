#include <stdio.h>
#include "gputimer.h"

const int N = 1024;

void transpose_CPU(float in[], float out[]){
  for(int j=0; j<N; j++){
    for(int i=0; i<N; i++){
      out[j + i*N] = in[i + j*N]; //out(j, i)=in(i, j)
      }
     }
 }
 
 int main(int argc, char** argv){
    int numbytes = N*N*sizeof(float);
    float *in = (float *) malloc(numbytes);
    float *out = (float *) malloc(numbytes);
    float *gold = (float *) malloc(numbytes);
    
    fill_matrix(in);
    transpose_CPU(in, gold);
    
    printf("input matrix:\n");
    print_matrix(in);
    
    printf("reference or 'gold' transposed matrix:\n");
    print_matrix(gold);
 }
