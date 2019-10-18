#include "PPMFile.h"

PPMFile::PPMFile(std::string fileName) 
{ 
	// Dot = -1, Slash = -1 -> "" | " " | "x"
	// Dot = x, Slash = -1 -> "." | ".x" | "x."
	// Dot = -1, Slash = x -> "/" | "/x" | "x/"
	// Dot = x, Slash = y -> "./" | "./x" | "x/." | "x/y."
	size_t dotPosition = fileName.find_last_of(".");
	size_t slashPosition = fileName.find_last_of('//');
	printf("Dot Pos: %i\n", dotPosition);
	printf("Slash Pos: %i\n", slashPosition);
	std::string fileNameWithoutType = fileName.substr(0, dotPosition);
	std::string fileNameWithType = fileNameWithoutType + ".ppm";
	this->fileName = fileNameWithType;
	printf("%s\n", this->fileName.c_str());
}

void PPMFile::WriteFromRasterDisplay(RasterDisplay* rasterDisplay)
{
	std::ofstream outputFile(fileName);
	if(outputFile.is_open())
	{
		std::string rasterWidth = std::to_string(rasterDisplay->GetWidth());
		std::string rasterHeight = std::to_string(rasterDisplay->GetHeight());
		std::string ppmHeader = "P3 " + rasterWidth + " " + rasterHeight + " 255";
		outputFile << ppmHeader << std::endl;

		std::string ppmData;
		int totalPixels = rasterDisplay->GetWidth() * rasterDisplay->GetHeight();
		int maxCharacterPerLine = 12;	// Ex->255 255 255\n
		ppmData.reserve(totalPixels * maxCharacterPerLine);

		for(int i = 0; i < rasterDisplay->GetHeight(); i++)
		{
			for(int j = 0; j < rasterDisplay->GetWidth(); j++)
			{
				Color pixel;
				pixel = rasterDisplay->GetPixel({j, i});
				ppmData += std::to_string(pixel.GetRed()) + " " +
					std::to_string(pixel.GetBlue()) + " " +
					std::to_string(pixel.GetGreen()) + "\n";
			}
		}

		outputFile << ppmData;
		outputFile.flush();
		outputFile.close();
	}
}
