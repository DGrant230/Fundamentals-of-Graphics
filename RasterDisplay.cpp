#include "RasterDisplay.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>
#include <stdexcept>
#include <string>

RasterDisplay::RasterDisplay(int width, int height) : width(width), height(height), pixels(new Color[width * height]) { }

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