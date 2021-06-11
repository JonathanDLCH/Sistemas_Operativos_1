#include <stdio.h>

#define max 10

int i_array[max]={0,1,2,3,4,5,6,7,8,9};
int *i_p;

float f_array[max]={.0,.1,.2,.3,.4,.5,.6,.7,.8,.9};
float *f_p;

int main(int argc, char const *argv[])
{
	i_p=i_array;
	f_p=f_array;

	for (int i = 0; i < max; ++i)
	{
		printf("\n%d \t %f\n",*i_p++,*f_p++);
	}
	return 0;
}