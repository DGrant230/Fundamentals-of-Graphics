#include "PPMFile.h"
#include <filesystem>
#include <sys/stat.h>
#include <assert.h>

PPMFile::PPMFile(std::string fileName) 
{ 

}

PPMFile PPMFile::CreatePPMFile(std::string filename)
{
	printf("Filename: %s\n", filename.c_str());
	std::filesystem::path filePath (filename);
	assert(filePath.extension().generic_string() == ".ppm");
	return PPMFile(filePath.generic_string());
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
