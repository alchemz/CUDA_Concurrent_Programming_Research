/*
How to:
Method 1: I=(R+G+B)/3
I=0.299f*R+0.587f*G+0.114f*B because red color is more sensitive
*/

__global__
void rgba_to_greyscale(const uchar4* const rgbImage,
						unsigned char* const greyImage,
						int numRows, int numCols)

{}

void your_rgba_to_greyscale(const uchar4 * const h_rgbaImage, uchar4 * const d_rgbaImage,
							unsigned char* const d_greyImage, size_t numRows, size_t numCols){

	const dim3 blockSize(1, 1, 1);
	const dim3 gridSize(1, 1,1 );
	rgbs_to_greyscale<<<gridSize, blockSize>>>(d_rgbaImage, d_greyImage, numRows, numCols);

	cudaDevieSynchronize();
	checkCudaErrors(cudaGetLastError());
}