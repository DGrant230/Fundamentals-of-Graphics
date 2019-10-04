#include "Raster.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

void PrintRowOrder(Raster r)
{
	printf("#Printing Row Order\n\n");
	for(int i = 0; i < r.GetWidth(); i++)
	{
		for(int j = 0; j < r.GetHeight(); j++)
		{
			Pixel p;
			p = r.GetPixel(i, j);
			printf("#%i, %i\n", i, j);
			printf("%i %i %i\n\n", p.r, p.b, p.g);
		}
	}
}

void PrintColumnOrder(Raster r)
{
	printf("#Printing Column Order\n\n");
	for(int i = 0; i < r.GetHeight(); i++)
	{
		for(int j = 0; j < r.GetWidth(); j++)
		{
			Pixel p;
			p = r.GetPixel(j, i);
			printf("#%i, %i\n", j, i);
			printf("%i %i %i\n\n", p.r, p.b, p.g);
		}
	}
}

int main(int argc, char* argv[])
{
	bool useRowOrder = false;
	
	if(argc > 1)
	{
		for(int i = 1; i < argc; i++)
		{
			if(strcmp(argv[i], "ro") == 0)
			{
				useRowOrder = true;
			}
		}
	}

	int x0 = 6, y0 = 4, x1 = 0, y1 = 1;
	Raster r = { 20, 20 };
	//r.DrawLineDDA(x0, y0 + 3, x1, y1 + 3);
	r.DrawLineBresenham(x0, y0, x1, y1);
	// r.SetPixel(x0, y0, 255, 0, 0);
	// r.SetPixel(x1, y1, 255, 0, 0);
	// r.SetPixel(x0 + 1, y0, 255, 0, 0);
	// r.SetPixel(x1 + 1, y1, 255, 0, 0);



	
	printf("P3 %i %i 255\n", r.GetWidth(), r.GetHeight());
	
	if(useRowOrder)
		PrintRowOrder(r);
	else
		PrintColumnOrder(r);
	
	return 0;
}
