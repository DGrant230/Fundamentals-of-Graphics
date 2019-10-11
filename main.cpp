#include "Raster.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

void PrintRowOrder(Raster raster)
{
	printf("#Printing Row Order\n\n");
	for(int i = 0; i < raster.GetWidth(); i++)
	{
		for(int j = 0; j < raster.GetHeight(); j++)
		{
			Pixel pixel;
			pixel = raster.GetPixel(i, j);
			printf("#%i, %i\n", i, j);
			printf("%i %i %i\n\n", pixel.red, pixel.blue, pixel.green);
		}
	}
}

void PrintColumnOrder(Raster raster)
{
	printf("#Printing Column Order\n\n");
	for(int i = 0; i < raster.GetHeight(); i++)
	{
		for(int j = 0; j < raster.GetWidth(); j++)
		{
			Pixel pixel;
			pixel = raster.GetPixel(j, i);
			printf("#%i, %i\n", j, i);
			printf("%i %i %i\n\n", pixel.red, pixel.blue, pixel.green);
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

	int x0 = 0, y0 = 0, 
		x1 = 0, y1 = 19, 
		x2 = 19, y2 = 0,
		x3 = 19, y3 = 19,
		x4 = 10, y4 = 7,
		x5 = 7, y5 = 10;
		
	Raster raster = { 20, 20 };
	
	raster.DrawLine(x0, y0, x1, y1, 255, 0, 0);		// Vertical line
	raster.DrawLine(x0, y0, x2, y2, 0, 255, 0);  	// Horizontal line
	raster.DrawLine(x0, y0, x3, y3, 0, 0, 255);  	// Diagonal line
	raster.DrawLine(x0, y0, x4, y4, 255, 255, 255);  // Flatter line+
	raster.DrawLine(x0, y0, x5, y5, 255, 255, 0);  	// Steeper line+
	raster.DrawLine(x1, y1, x4, y4, 255, 0, 255);  	// Steeper line-


	
	printf("P3 %i %i 255\n", raster.GetWidth(), raster.GetHeight());
	
	if(useRowOrder)
		PrintRowOrder(raster);
	else
		PrintColumnOrder(raster);
	
	return 0;
}
