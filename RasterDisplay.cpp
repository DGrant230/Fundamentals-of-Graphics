#include "RasterDisplay.h"
#include <stdexcept>
#include <string>
#include <iostream>

RasterDisplay::RasterDisplay(int width, int height) : width(width), height(height), pixels(new Color[width * height]) { }

int RasterDisplay::GetWidth()
{
	return width;
}

int RasterDisplay::GetHeight()
{
	return height;
}

void RasterDisplay::SetPixel(Vector2Int coordinate, Color color)
{
	ThrowIfCoordinateIsOff(coordinate);
	int x = coordinate.x;
	int y = coordinate.y;
	pixels[width * x + y] = color;
}

Color RasterDisplay::GetPixel (Vector2Int coordinate)
{
	ThrowIfCoordinateIsOff(coordinate);
	int x = coordinate.x;
	int y = coordinate.y;
	return pixels[width * x + y];
}

void RasterDisplay::Print()
{
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			std::string coordinate("(" + std::to_string(x) + ", " + std::to_string(y) +"): ");
			Color pixel = GetPixel({x, y});
			std::string red = std::to_string(pixel.GetRed());
			std::string green = std::to_string(pixel.GetGreen());
			std::string blue = std::to_string(pixel.GetBlue());
			std::string color(red + " " + green + " " + blue);
			std::cout << coordinate << color << std::endl; 
		}
}

void RasterDisplay::ThrowIfCoordinateIsOff(Vector2Int coordinate)
{
	if (!IsCoordinateOn(coordinate))
	{
		int x = coordinate.x;
		int y = coordinate.y;
		throw std::out_of_range("The coordinate (" + std::to_string(x) + ", " + std::to_string(y) + ") is outside the size of the RasterDisplay.");
	}
}

bool RasterDisplay::IsCoordinateOn(Vector2Int coordinate)
{
	int x = coordinate.x;
	int y = coordinate.y;

	return x < width && y < height;
}