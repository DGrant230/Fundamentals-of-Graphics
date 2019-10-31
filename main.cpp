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
		
	RasterDisplay rasterDisplay = { 20, 20 };
	Rasterizer rasterizer = { &rasterDisplay };
	rasterizer.DrawLine({x0, y0}, {x1, y1}, {255, 0, 0});		// Vertical line
	rasterizer.DrawLine({x0, y0}, {x2, y2}, {0, 255, 0});  	// Horizontal line
	rasterizer.DrawLine({x0, y0}, {x3, y3}, {0, 0, 255});  	// Diagonal line
	rasterizer.DrawLine({x0, y0}, {x4, y4}, {255, 255, 255});  // Flatter line+
	rasterizer.DrawLine({x0, y0}, {x5, y5}, {255, 255, 0});  	// Steeper line+
	rasterizer.DrawLine({x1, y1}, {x4, y4}, {255, 0, 255});  	// Steeper line-
	
	// PPMFile ppmFile = PPMFile::CreatePPMFile("_TestPPMFile");
	// ppmFile.WriteFromRasterDisplay(rasterDisplay);

	try{
		RasterDisplay inDisplay = PPMFile::ReadPPMFile("");
	}
	catch(const std::runtime_error& e)
	{
		std::cout << e.what();
	}

	try{
		RasterDisplay inDisplay = PPMFile::ReadPPMFile("_TestPPMFile");
		PrintColumnOrder(inDisplay);
	}
	catch(const std::runtime_error& e)
	{
		std::cout << e.what();
	}

	return 0;
}
