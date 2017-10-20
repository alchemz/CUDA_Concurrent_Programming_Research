// practise the different
#include <stdio.h>

// declaring and initializing an external variable
extern int x = 9;

// declaring the initializing a global varaible
int z = 10;

// use typedef to give a new name to an already existing data type
typedef long long int LL;

void calSquare( int arg)
{
	printf("The square of %d is %d\n", arg, arg * arg);
}

int main(void)
{
	//const: value cannot be modified
	const int a = 32;
	
	//char: declare a char variable
	char b = 'G';
	
	//value of extern variable modified
	x = 2;
	//extern: declare an extern variable
	extern int z;
	
	LL c = 100000;
	
	printf("Morning!\n");

	while ( x > 0)
	{	//static: perserve value after being out of scope
		static int y =5;
		printf("%d ", y);
		x--;
	}
	
	//call a function
	calSquare(5);
	return 0;
}
