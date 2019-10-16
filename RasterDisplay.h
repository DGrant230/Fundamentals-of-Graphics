#ifndef RASTERDISPLAY_H
#define RASTERDISPLAY_H

#include "Vector2Int.h"
#include "Color.h"

class Rasterizer;

class RasterDisplay
{
	
private:
	int width;
	int height;
	Color* pixels;

public:
	RasterDisplay() = delete;
	RasterDisplay(int width, int height);
		
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetPixel(Vector2Int coordinate, Color color = { 255, 255, 255 });
	Color GetPixel(Vector2Int coordinate);
		
private:
	void ThrowIfCoordinateIsOff(Vector2Int coordinate);
	bool IsCoordinateOn(Vector2Int coordinate);
};
#endif