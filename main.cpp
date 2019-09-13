#include "Raster.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

int main(int argc, char* argv[])
{
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "ColOrder") == 0)
			{
#define COLUMN_ORDER
			}
		}
	}

	int x0 = 1, y0 = 1, x1 = 4, y1 = 16;
	Raster r = { 20, 20 };
	r.DrawLineDDA(x0, y0, x1, y1);
	r.DrawLineBresenham(x0 + 1, y0, x1 + 1, y1);
	r.SetPixel(x0, y0, 255, 0, 0);
	r.SetPixel(x1, y1, 255, 0, 0);
	r.SetPixel(x0 + 1, y0, 255, 0, 0);
	r.SetPixel(x1 + 1, y1, 255, 0, 0);



	
	printf("P3 %i %i 255\n", r.GetWidth(), r.GetHeight());
	
	for(int i = 0; i < r.GetWidth(); i++)
	{
		for(int j = 0; j < r.GetHeight(); j++)
		{
			Pixel p;
#ifndef COLUMN_ORDER
			p = r.GetPixel(i, j);
			printf("#%i, %i\n", i, j);
#else
			p = r.GetPixel(j, i);
			printf("#%i, %i\n", j, i);
#endif

			printf("%i %i %i\n\n", p.r, p.b, p.g);
		}
	}
	
	return 0;
}
