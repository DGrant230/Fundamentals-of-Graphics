#include "PPMFile.h"
#include <filesystem>
#include <sys/stat.h>
#include <assert.h>

PPMFile::PPMFile(std::string filename) 
{ 

}

PPMFile PPMFile::CreatePPMFile(std::string filename)
{	
	std::filesystem::path absoluteFilepath = GetAbsoluteFilePath(std::filesystem::path(filename));
	printf("%s\n", absoluteFilepath.generic_string().c_str());
	std::filesystem::path directoryPath = GetDirectoryPath(absoluteFilepath);
	printf("%s\n", directoryPath.generic_string().c_str());
	bool directoryExists = DoesDirectoryPathExist(directoryPath);
	directoryExists ? printf("Directory Exist\n") : printf("Directory Does Not Exist\n");
	if(!directoryExists)
		return PPMFile("");

	bool hasExtension = DoesFileHaveExtension(absoluteFilepath);
	if(!hasExtension || (hasExtension && !IsPPMFile(absoluteFilepath)))
		absoluteFilepath.replace_extension(".ppm");

	bool fileExist = DoesFilePathExist(absoluteFilepath);
	if(fileExist)
		absoluteFilepath = CreateCopyWithNumberAppended(absoluteFilepath);

	printf("Final path: %s\n\n", absoluteFilepath.generic_string().c_str());
	return PPMFile(absoluteFilepath.generic_string());
}

void PPMFile::WriteFromRasterDisplay(RasterDisplay* rasterDisplay)
{
	std::ofstream outputFile(filename);
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

bool PPMFile::DoesFilePathExist(std::filesystem::path filePath)
{
	return std::filesystem::is_regular_file(filePath) && std::filesystem::exists(filePath);
}

std::filesystem::path PPMFile::CreateCopyWithNumberAppended(std::filesystem::path filePath)
{
	int appendage = 1;
	while(true)
	{
		std::string absFilepathWithAppendage = AppendCopyNumber(filePath, appendage);
		if(!DoesFilePathExist(absFilepathWithAppendage))
		{	
			return std::filesystem::path(absFilepathWithAppendage);
		}
		appendage++;
	}
}

std::string PPMFile::AppendCopyNumber(std::filesystem::path filePath, int copyNumber)
{
	std::string filePathName = filePath.generic_string();
	filePathName.insert(filePathName.find_last_of('.'), "-Copy(" + std::to_string(copyNumber) + ")");
	return filePathName;
}
