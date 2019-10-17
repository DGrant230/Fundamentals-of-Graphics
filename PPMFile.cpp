#include "PPMFile.h"

PPMFile::PPMFile(std::string fileName) : fileName(fileName), ppmFile() 
{ 
	size_t dotPosition = this->fileName.find_first_of(".");
	std::string fileType = fileName.substr(dotPosition + 1);
	bool isPPMFile = fileType == "ppm";
	if (isPPMFile)
		printf("Is equal.");
	else
	{
		printf("Not equal.");
	}
}

void PPMFile::WriteFromRasterDisplay(const RasterDisplay* rasterDisplay)
{
	if (!ppmFile.is_open())
	{
		ppmFile.open(fileName);
		if (ppmFile.fail())
			printf("Failed to open file.\n");

		ppmFile.close();
	}
		
}
