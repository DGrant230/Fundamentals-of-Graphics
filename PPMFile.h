#ifndef PPMFILE_H
#define PPMFILE_H

#include <fstream>
#include <string>
#include "RasterDisplay.h"

class PPMFile
{
private:
	std::string filename;

public:
	PPMFile() = delete;
	PPMFile(std::string filename);
	static PPMFile CreatePPMFile(std::string filename);
	void WriteFromRasterDisplay(RasterDisplay* rasterDisplay);
	RasterDisplay ReadIntoRasterDisplay();

private:
	static std::filesystem::path GetAbsoluteFilePath(std::filesystem::path filePath);
	static std::filesystem::path GetDirectoryPath(std::filesystem::path filePath);
	static bool DoesDirectoryPathExist(std::filesystem::path directoryPath);
	static bool DoesFileHaveExtension(std::filesystem::path filePath);
	static bool IsPPMFile(std::filesystem::path filePath);
	static bool DoesFilePathExist(std::filesystem::path filePath);
	static std::filesystem::path CreateCopyWithNumberAppended(std::filesystem::path filePath);
	static std::string AppendCopyNumber(std::filesystem::path filePath, int copyNumber);

};
#endif