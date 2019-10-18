#ifndef PPMFILE_H
#define PPMFILE_H

#include <fstream>
#include <string>
#include "RasterDisplay.h"

class PPMFile
{
private:
	std::string fileName;

public:
	PPMFile() = delete;
	PPMFile(std::string fileName);
	void WriteFromRasterDisplay(RasterDisplay* rasterDisplay);
	RasterDisplay ReadIntoRasterDisplay();

private:
	
};
#endif