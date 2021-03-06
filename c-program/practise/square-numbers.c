#include <stdio.h>

//use void so the kernel does not return a value
//instead it will pass the data to the pointer
_global_ void square(float * d_out, float * d_in){
	int idx= threadIdx.x; //each thread knows it index
	float f=d_in[idx];
	d_out[idx]=f*f;


}

/*
	compute cubic
_global_ void cube(float *d_out, float *d_in){
		int dix=threadIdx.x;
		float f=d_in[idx];
		d_out[idx]=f*f*f;
	}
*/

int main(int argc, char ** argv){
	const int ARRAY_SIZE=64;
	const int ARRAY_BYTES=ARRAY_SIZE * sizeof(float);

	//generate the input array on the host, data on the CPU
	float h_in[ARRAY_SIZE];
	for(int i=0; i< ARRAY_SIZE; i++){
		h_in[i]=float(i);
	}
	float h_out[ARRAY_SIZE];

	//declare GPU memory pointers, data on the GPU
	float * d_in;
	float * d_out;

	//allocate GPU memory, tell CUDA the data is on the GPU
	cudaMalloc((void **) &d_in, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, ARRAY_BYTES);

	//transfer the array to GPU
	cudaMemcpy(d_in, h_in, ARRAY_BYTES, cudaMemcpyHostToDevice);

	//launch the kernel in one block with 64 bytes
	square<<<1, ARRAY_SIZE>>>(d_out, d_in);

	//copy back the result array to the CPU
	cudaMemcpy(h_out, d_out, ARRAY_BYTES, cudaMemcpyDviceToHost);

	//print out the resulting array
	for(int i=0; i<ARRAY_SIZE; i++){
		printf("%f", h_out[i]);
		printf(((i%4)!=3)? "\t": "\n");
	}

	//free GPU memory allocation
	cudaFree(d_in);
	cudaFree(d_out);

	return 0;
}