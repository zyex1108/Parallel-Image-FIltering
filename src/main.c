#include <stdio.h>

#include "MPI_blur_filter.h"


int main( int argc, char ** argv )
{
    int height = 10;
    int width = 10;
    int overlapSize = 1;
    int size = 5;

    pixel* input = malloc(height * width * sizeof(pixel));
    pixel* pBuf = malloc(height * width * sizeof(pixel));
    

    // init input
    printf("Init input...\n");
    int i,j;
    for(i = 0; i < height; i++)
    {
	for(j = 0; j < width; j++)
	{
	    input[CONV(i,j,width)].r = 0;
	    input[CONV(i,j,width)].g = 0;
	    input[CONV(i,j,width)].b = 0;
	}
    }
    printf("Init input: done.\n");

    printf("Test getNextSubImg...\n");
    int count = 0;
    simpleImage r;
    do
    {
	r = getNextSubImg(input, width, height, overlapSize, size, (count == 0), pBuf);

	if(r.p == NULL)
	    break;

	count++;
    }while(1);

    printf("Test: done. Count = %d\n", count);

    free(input);
    free(pBuf);

    return 0;
}
