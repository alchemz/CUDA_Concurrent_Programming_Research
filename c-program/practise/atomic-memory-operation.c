#include <stdio.h>
#include "gputime.h"

#define NUM_THREADS 1000000
#define ARRAY_SIZE 10

#define BLOCK_WIDTH 1000

void print_array(int *array, int size)
{

}

__global__ void increment_atomic(int *g)
{
	//which thread is this?
	int i= blockIdx.x * blockDim.x + threadIdx.x;

	//each thread to increment consecutive elements, wrapping at ARRAY_SIZE
	i = i % ARRAY_SIZE;
	atomicAdd(& g[i], 1);
}



int main( int argc, char **argv){
	GpuTimer timer;
	printf("%d total threads in %d blocks writing into %d array elements\n",
			NUM_THREADS, NUM_THREADS / BLOCK_WIDTH, ARRAY_SIZE);

	//declare and allocate host memory
	int h_array[ARRAY_SIZE];
	const int ARRAY_SIZE = ARRAY_SIZE * sizeof(int);

	//declare, allocate, and zero out GPU memory
	int * d_array;
	cudaMalloc((void **) &d_array, ARRAY_BYTES);
	cudaMemset((void *) d_array, 0, ARRAY_BYTES);

	//launch the kernel
	timer.Start();
	increment_atomic<<<NUM_THREADS/BLOCK_WIDTH, BLOCK_WIDTH>>>(d_array);
	timer.stop();

	//copy back the array of sums from GPU and print
	cudaMemcpy(h_array, d_array, ARRAY_BYTES, cudaMemcpyDeviceToHost);
	//print_array(h_array, ARRAY_SIZE);
	printf("Time elapsed =%g ms\n", timer.Elapsed());

	//free GPU memory allocated and exit
	cudaFree(d_array);
	return 0;

}