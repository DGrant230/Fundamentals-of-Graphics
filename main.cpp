#include "RasterDisplay.h"
#include "Rasterizer.h"
#include "PPMFile.h"

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#include <fstream>

void PrintRowOrder(RasterDisplay rasterDisplay, std::ofstream* file)
{
	printf("#Printing Row Order\n\n");
	for(int i = 0; i < rasterDisplay.GetWidth(); i++)
	{
		for(int j = 0; j < rasterDisplay.GetHeight(); j++)
		{
			Color pixel;
			pixel = rasterDisplay.GetPixel({i, j});
			*file << std::to_string(pixel.GetRed()) << " " << 
				std::to_string(pixel.GetBlue()) << " " << 
				std::to_string(pixel.GetGreen()) << "\n";
		}
	}
}

void PrintColumnOrder(RasterDisplay rasterDisplay, std::ofstream* file)
{
	printf("#Printing Column Order\n\n");
	for(int i = 0; i < rasterDisplay.GetHeight(); i++)
	{
		for(int j = 0; j < rasterDisplay.GetWidth(); j++)
		{
			Color pixel;
			pixel = rasterDisplay.GetPixel({j, i});
			*file << std::to_string(pixel.GetRed()) << " " <<
				std::to_string(pixel.GetBlue()) << " " <<
				std::to_string(pixel.GetGreen()) << "\n";
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
		
	RasterDisplay rasterDisplay = { 20, 20 };
	Rasterizer rasterizer = { &rasterDisplay };
	//rasterizer.DrawLine({x0, y0}, {x1, y1}, {255, 0, 0});		// Vertical line
	//rasterizer.DrawLine({x0, y0}, {x2, y2}, {0, 255, 0});  	// Horizontal line
	//rasterizer.DrawLine({x0, y0}, {x3, y3}, {0, 0, 255});  	// Diagonal line
	//rasterizer.DrawLine({x0, y0}, {x4, y4}, {255, 255, 255});  // Flatter line+
	//rasterizer.DrawLine({x0, y0}, {x5, y5}, {255, 255, 0});  	// Steeper line+
	rasterizer.DrawLine({x1, y1}, {x4, y4}, {255, 0, 255});  	// Steeper line-
	PPMFile ppmFile ("A.pPm");
	ppmFile.WriteFromRasterDisplay(&rasterDisplay);
	std::ofstream file("../TestPic.ppm", std::ios_base::out);
	if (file.is_open())
	{
		printf("File is open\n");
		file << "P3 " << std::to_string(rasterDisplay.GetWidth()) << " "
			<< std::to_string(rasterDisplay.GetHeight()) << " 255\n";
		if (useRowOrder)
			PrintRowOrder(rasterDisplay, &file);
		else
			PrintColumnOrder(rasterDisplay, &file);

		file.close();
	}
	
	return 0;
}
