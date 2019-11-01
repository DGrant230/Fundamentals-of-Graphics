#include "PPMFile.h"
#include <filesystem>
#include <chrono>
#include <iostream>
#include <exception>

PPMFile PPMFile::CreatePPMFile(std::string filename)
{	
	std::filesystem::path absoluteFilepath = GetAbsoluteFilePath(std::filesystem::path(filename));
	std::filesystem::path directoryPath = GetDirectoryPath(absoluteFilepath);

	if(!DoesDirectoryPathExist(directoryPath))
		return PPMFile("");

	bool hasExtension = DoesFileHaveExtension(absoluteFilepath);
	if(!hasExtension || (hasExtension && !IsPPMFile(absoluteFilepath)))
		MakeFileExtensionPPM(absoluteFilepath);

	if(DoesFilePathExist(absoluteFilepath))
		AppendCopyNumberToFilename(absoluteFilepath);

	return PPMFile(absoluteFilepath.generic_string());
}

RasterDisplay PPMFile::ReadPPMFile(std::string filename)
{
	std::filesystem::path absoluteFilepath = GetAbsoluteFilePath(std::filesystem::path(filename));
	std::filesystem::path directoryPath = GetDirectoryPath(absoluteFilepath);

	if(!DoesDirectoryPathExist(directoryPath))
		throw std::runtime_error("Directory does not exist: " + directoryPath.generic_string() + "\n");

	bool hasExtension = DoesFileHaveExtension(absoluteFilepath);
	if(!hasExtension || (hasExtension && !IsPPMFile(absoluteFilepath)))
		MakeFileExtensionPPM(absoluteFilepath);

	if(!DoesFilePathExist(absoluteFilepath))
		throw std::runtime_error("Filepath does not exist: " + absoluteFilepath.generic_string());
	
	std::ifstream inputFile(absoluteFilepath);
	if(!inputFile.is_open())
		throw std::runtime_error("There was an error reading the input file.\n");

	RasterDisplay rasterDisplay = CreateRasterDisplayFromFile(inputFile);

	inputFile.close();

	return rasterDisplay;
}

void PPMFile::WriteFromRasterDisplay(RasterDisplay& rasterDisplay)
{
	std::string ppmData = BuildPPMData(rasterDisplay);
	
	std::ofstream outputFile(filename);
	if(outputFile.is_open())
		outputFile << ppmData;
	outputFile.flush();
	outputFile.close();

	ThrowIfOutputFailed(outputFile);
}

PPMFile::PPMFile(std::string filename) : filename(filename) { }

std::filesystem::path PPMFile::GetAbsoluteFilePath(std::filesystem::path filePath)
{
	return std::filesystem::absolute(filePath);
}

std::filesystem::path PPMFile::GetDirectoryPath(std::filesystem::path filePath)
{
	return filePath.parent_path();
}

bool PPMFile::DoesDirectoryPathExist(std::filesystem::path directoryPath)
{
	return std::filesystem::is_directory(directoryPath) && std::filesystem::exists(directoryPath);
}

bool PPMFile::DoesFileHaveExtension(std::filesystem::path filePath)
{
	return filePath.has_extension();
}

bool PPMFile::IsPPMFile(std::filesystem::path filePath)
{
	return filePath.extension().generic_string() == ".ppm";
}

void PPMFile::MakeFileExtensionPPM(std::filesystem::path& filePath)
{
	filePath.replace_extension(".ppm");
}

bool PPMFile::DoesFilePathExist(std::filesystem::path filePath)
{
	return std::filesystem::is_regular_file(filePath) && std::filesystem::exists(filePath);
}

void PPMFile::AppendCopyNumberToFilename(std::filesystem::path& filePath)
{
	int copyNumber = 1;
	while(true)
	{
		std::string fileCopy = filePath.generic_string();
		fileCopy.insert(fileCopy.find_last_of('.'), "-Copy(" + std::to_string(copyNumber) + ")");

		if(!DoesFilePathExist(fileCopy))
		{	
			filePath = std::filesystem::path(fileCopy);
			return;
		}
		copyNumber++;
	}
}

std::string PPMFile::BuildPPMData(RasterDisplay& rasterDisplay)
{
	std::string ppmData = CreatePPMHeader(rasterDisplay) + GetPixelData(rasterDisplay);

	return ppmData;
}

std::string PPMFile::CreatePPMHeader(RasterDisplay& rasterDisplay)
{
	std::string rasterWidth = std::to_string(rasterDisplay.GetWidth());
	std::string rasterHeight = std::to_string(rasterDisplay.GetHeight());
	return "P3 " + rasterWidth + " " + rasterHeight + " 255\n";
}

std::string PPMFile::GetPixelData(RasterDisplay& rasterDisplay)
{
	std::string pixelData;
	for(int i = 0; i < rasterDisplay.GetHeight(); i++)
	{
		for(int j = 0; j < rasterDisplay.GetWidth(); j++)
		{
			Color pixel;
			pixel = rasterDisplay.GetPixel({j, i});
			pixelData += std::to_string(pixel.GetRed()) + " " +
				std::to_string(pixel.GetGreen()) + " " +
				std::to_string(pixel.GetBlue()) + "\n";
		}
	}

	return pixelData;
}

void PPMFile::ThrowIfOutputFailed(std::ofstream& outputFile)
{
	if(!outputFile)
		throw std::runtime_error("There was an error writing to the output file.");
}

RasterDisplay PPMFile::CreateRasterDisplayFromFile(std::ifstream& inputFile)
{
	std::string format;
	int width, height, intensity;
	inputFile >> format >> width >> height >> intensity;

	RasterDisplay rasterDisplay(width, height);
	for(int y = 0; y < height; y++)
	{	for(int x = 0; x < width; x++)
		{
			int red, green, blue;
			inputFile >> red >> green >> blue;
			rasterDisplay.SetPixel({ x, y }, { red, green, blue });
		}
	}	

	return rasterDisplay;
}