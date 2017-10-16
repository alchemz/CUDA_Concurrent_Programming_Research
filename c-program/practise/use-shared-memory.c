/************************
*****use shared memory***
************************/
#include <stdio.h>
__global__ void use_shared_memory_GPU(float *array)
{
	//local variables, private to each thread
	int i, index=threadIdx.x;
	float average, sum=0.0f;

	//__shared__ variables are visible to all threads in thread block
	//and have the same lifetime as the thread block
	__shared__ float sh_arr[128];

	//copy data from "array" in global memory to sh_arr in shared memory;
	//here, each thread is responsible for copying a single element.
	sh_arr[index]=array[index];

	__syncthreads(); //ensure all the writes to shared memory have completed, BARRIER

	//now, sh_arr is fully populated, let's find the average of all previous elements
	//share memory is much faster than global memory
	for(i=0; i<index; i++){sum+=sh_arr[i];}
	average=sum/(index+1.0f);

	// if array[index] is greater than the average of array[0..index-1], replace with average.
	// since array[] is in global memory, this change will be seen by the host(and potentially)
	// other thread blocks, if any)
	if(array[index] > average) { array[index] = average; }

	// the following code has NO EFFECT: it modifies share memory, but
	// the resulting modifed data is never copied back to global memory
	// and vanishes when the thread block completes
	sh_arr[index] = 3.14;
}

int main(int argc, char **argv)
{
	use_local_memory_GPU<<<1, 128>>>(2.0f);

	/*
	* Next, call a kernal that shows using global memory
	*/
	float h_arr[128]; //convention: h_ variables live on host
	float *d_arr; //convention: d_ variables live on device

	//allocate global memory on the device, place result in  "d_arr"
	cudaMalloc((void **) &d_arr, sizeof(float) * 128);
	//now copy data from host memory "h_arr" to device memory "d_arr"
	cudaMemcpy((void *)d_arr, (void *)h_arr, sizeof(float)* 128, cudaMemcpyHostToDevice);
	//launch the kernel (1 block with 128 threads)
	use_global_memory_GPU<<<1,128>>>(d_arr);//modifies the contents of the array at d_arr
	//copy the modified array back to host, overwriting contents of h_arr
	cudaMemcpy((void *)h_arr, (void *)d_arr, sizeof(float)* 128, cudaMemcpyDeviceToHost);
	//.. do other stuff
	/*
	* Next, call a kernel that shows using share memory
	*/

	//as before, pass in a pointer to data in global memory
	use_shared_memory_GPU<<<1, 128>>>(d_arr);
	//copy the modified array back to the host
	cudaMemcpy((void *)h_arr, (void *)d_arr, sizeof(float) *128, cudaMemcpyHostToDevice);
	//...do other stuff
	return 0;
}