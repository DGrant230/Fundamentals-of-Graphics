#include "PPMFile.h"
#include <filesystem>
#include <chrono>
#include <iostream>

PPMFile::PPMFile(std::string filename) : filename(filename) { }

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
		AppendCopyNumberToFile(absoluteFilepath);

	return PPMFile(absoluteFilepath.generic_string());
}

void PPMFile::WriteFromRasterDisplay(RasterDisplay* rasterDisplay)
{
	std::string ppmData;
	ppmData += CreatePPMHeader(rasterDisplay);

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

	std::ofstream outputFile(filename);
	if(outputFile.is_open())
		outputFile << ppmData;
	outputFile.flush();
	outputFile.close();

}

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

void PPMFile::AppendCopyNumberToFile(std::filesystem::path& filePath)
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

std::string PPMFile::CreatePPMHeader(RasterDisplay* rasterDisplay)
{
	std::string rasterWidth = std::to_string(rasterDisplay->GetWidth());
	std::string rasterHeight = std::to_string(rasterDisplay->GetHeight());
	return "P3 " + rasterWidth + " " + rasterHeight + " 255\n";
}