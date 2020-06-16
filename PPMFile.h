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
	static PPMFile CreatePPMFile(std::string filename);
	static RasterDisplay ReadPPMFile(std::string filename);
	void WriteFromRasterDisplay(RasterDisplay& rasterDisplay);
	
private:
	PPMFile(std::string filename);
	static std::filesystem::path GetAbsoluteFilePath(std::filesystem::path filePath);
	static std::filesystem::path GetDirectoryPath(std::filesystem::path filePath);
	static bool DoesDirectoryPathExist(std::filesystem::path directoryPath);
	static bool DoesFileHaveExtension(std::filesystem::path filePath);
	static bool IsPPMFile(std::filesystem::path filePath);
	static void MakeFileExtensionPPM(std::filesystem::path& filePath);
	static bool DoesFilePathExist(std::filesystem::path filePath);
	static void AppendCopyNumberToFilename(std::filesystem::path& filePath);
	static std::string BuildPPMData(RasterDisplay& rasterDisplay);
	static std::string CreatePPMHeader(RasterDisplay& rasterDisplay);
	static std::string GetPixelData(RasterDisplay& rasterDisplay);
	static void ThrowIfOutputFailed(std::ofstream& outputFile);
	static RasterDisplay CreateRasterDisplayFromFile(std::ifstream& inputFile);
};
#endif