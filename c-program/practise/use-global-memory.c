/***************************
* using global memory*
****************************/
#include <stdio.h>
//a __global__ function runs on the GPU & can be called from host
__global__ void use_global_memory_GPU(float *array)
{
	//"array" is a pointer into global memory on the device
	array[threadIdx.x]=2.0f*(float)threadIdx.x;
}

int main(int argc, char **argv){
	/*
	* First, call a kernal that shows using local memory
	*/
	use_local_memory_GPU<<<1,128>>>(2.0f);

	/*
	* Next, call a kernal that shows using global memory
	*/
	float h_arr[128]; //convention: h_ variables live on host
	float *d_arr;	//convention: d_ variables live on device(GPU global mem)

	//allocate global memory on the device, place result in "d_arr"
	//pass a pointer to itself
	cudaMalloc((void **) &d_arr, sizeof(float) *128);
	//now copy data from host memory "h_arr" to device memory "d_arr" 
	cudaMemcopy((void *)d_arr, (void *)h_arr, sizeof(float) *128, cudaMemcpyHostToDevice);
	//launch the kernel (1 block of 128 thread)
	use_global_memory_GPU<<<1, 128>>>(d_arr);//modifies the contents of array at d_arr
	cudaMemcopy((void *)h_arr, (void *)d_arr, sizeof(float) *128, cudaMemcopyHostToDevice);
	//...do other stuff
	return 0;

}