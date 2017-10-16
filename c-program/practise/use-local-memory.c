//using different memory spaces in CUDA
/****************************
* using local memory
*****************************/

//a __device__ or __global__ function runs on the GPU
//a kernel
__global__ void use_local_memory_GPU(float in)
{
	float f;	// variable "f" is in local memory and private to each thread
	f=in;		//parameter "in" is in local memory and private to each thread
	//... real code would presumably do other stuff here ... 
}

int main(int argc, char**argv){
	/*
	*	First, call a kernal that shows local memory
	*/
	use_local_memory_GPU<<<1, 128>>>(2.0f);//2.0f is the in parameter passed
}