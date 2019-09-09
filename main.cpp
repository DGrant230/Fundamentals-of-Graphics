#include "Raster.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Raster r = { 3000, 2000 };
	for(int i = 0; i < r.GetWidth(); i++)
	{
		for(int j = 0; j < r.GetHeight(); j++)
		{
			r.SetPixel(i, j, rand() % 255, rand() % 255, rand() % 255);
		}	
	}

	printf("P3 %i %i 255\n", r.GetWidth(), r.GetHeight());
	for(int i = 0; i < r.GetWidth(); i++)
	{
		for(int j = 0; j < r.GetHeight(); j++)
		{
			Pixel p = r.GetPixel(i, j);
			printf("%i %i %i\n", p.r, p.b, p.g);
		}
	}
	return 0;
}
