#include "RasterDisplay.h"
#include "Rasterizer.h"
#include "PPMFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>

void PrintColumnOrder(RasterDisplay rasterDisplay)
{
	printf("#Printing Column Order\n\n");
	for(int i = 0; i < rasterDisplay.GetHeight(); i++)
	{
		for(int j = 0; j < rasterDisplay.GetWidth(); j++)
		{
			Color pixel;
			pixel = rasterDisplay.GetPixel({j, i});
			std::cout << std::to_string(pixel.GetRed()) << " " <<
				std::to_string(pixel.GetGreen()) << " " <<
				std::to_string(pixel.GetBlue()) << "\n";
		}
	}
}

int main(int argc, char* argv[])
{
	int x0 = 0, y0 = 0, 
		x1 = 0, y1 = 19, 
		x2 = 19, y2 = 0,
		x3 = 19, y3 = 19,
		x4 = 10, y4 = 7,
		x5 = 7, y5 = 10;
		
	RasterDisplay rasterDisplay = { 100, 100 };
	Rasterizer rasterizer = { &rasterDisplay };

	try{
		rasterizer.DrawEllipse({50, 50}, 8, 6);
	}
	catch(std::exception& e)
	{
		printf("%s", e.what());
	}
	PPMFile ppmFile = PPMFile::CreatePPMFile("_Test");
	ppmFile.WriteFromRasterDisplay(rasterDisplay);


	return 0;
}
