#ifndef PPMFILE_H
#define PPMFILE_H

#include <fstream>
#include <string>
#include "RasterDisplay.h"

class PPMFile
{
private:
	std::string fileName;
	std::ofstream ppmFile;

public:
	PPMFile() = delete;
	PPMFile(std::string fileName);
	void WriteFromRasterDisplay(const RasterDisplay* rasterDisplay);
	RasterDisplay ReadIntoRasterDisplay();
};
#endif