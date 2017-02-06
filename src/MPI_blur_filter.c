#include "MPI_blur_filter.h"

simpleImage getNextSubImg(pixel* inputImg, int width, int height, int overlapSize, int refSize, int reset, pixel* pBuffer)
{
    static int x;
    static int y;

    if(reset)
    {
        x = 0;
        y = 0;
    }
    
    simpleImage result;
    result.width = 0;
    result.height = 0;
    result.p = NULL;

    if(x >= height || refSize <= 2*overlapSize)
        return result;
    
    // assume refSize > 2*overlapSize and x < height
    int h = refSize;
    int w = refSize;

    if(y + w >= width)
    {
        w = width - y;

        if(w <= 2*overlapSize)
        {
            y = 0;
            x += refSize - 2*overlapSize;

            return getNextSubImg(inputImg, width, height, overlapSize, refSize, 0, pBuffer);
        }
    }

    if(x + h >= height)
    {
        h = height - x;

        if(h <= 2*overlapSize)
        {
            return result;
        }
    }

    result.height = h;
    result.width = w;
    result.p = pBuffer;

    printf("DEBUG: (x,y) = (%d,%d) | (h,w) = (%d,%d)\n", x, y, h, w);

    int i, j;
    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j++)
        {
            pBuffer[CONV(i,j,w)].r = inputImg[CONV(x+i,y+j,width)].r;
            pBuffer[CONV(i,j,w)].g = inputImg[CONV(x+i,y+j,width)].g;
            pBuffer[CONV(i,j,w)].b = inputImg[CONV(x+i,y+j,width)].b;
        }
    }

    y += w - 2*overlapSize;

    return result;
}





int blurOneIter(simpleImage* inputImg, int size, int threshold) // TODO: to finish!
{
    int width = inputImg->width;
    int height = inputImg->height;

    pixel* p = inputImg->p;
    pixel* new = (pixel*)malloc(height * width * sizeof(pixel));

    int x,y,i,j;
    for(x = size; x < height - size; x++)
    {
	for(y = size; y < width - size; y++)
	{
	    int tR = 0;
	    int tG = 0;
	    int tB = 0;

	    for(i = -size; i <= size; i++)
	    {
		for(j = - size; j <= size; j++)
		{
		    tR += p[CONV(x+i,y+j,width)].r;
		    tG += p[CONV(x+i,y+j,width)].g;
		    tB += p[CONV(x+i,y+j,width)].b;
		}
	    }

	    new[CONV(x,y,width)].r = tR / ((2*size+1)*(2*size+1));
	    new[CONV(x,y,width)].g = tG / ((2*size+1)*(2*size+1));
	    new[CONV(x,y,width)].b = tB / ((2*size+1)*(2*size+1));
	}
    }


    free(new);
}
