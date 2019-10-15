#ifndef RASTER_H
#define RASTER_H

#include "Vector2Int.h"
#include "Color.h"

class Raster
{
	
private:
	int width;
	int height;
	Color* pixels;

public:
	Raster() = delete;
	Raster(int width, int height) : width(width), height(height), pixels(new Color[width * height]){}
		
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetPixel(Vector2Int coordinate, Color color = { 255, 255, 255 });
	Color GetPixel(Vector2Int coordinate);
	void DrawLine(int x0, int y0, int x1, int y1, int red = 255, int blue = 255, int green = 255);
	void DrawLine(int x0, int y0, int x1, int y1, Color color);
	void DrawLine(Vector2Int coord1, Vector2Int coord2, int red = 255, int blue = 255, int green = 255);
	void DrawLine(Vector2Int coord1, Vector2Int coord2, Color color);
		
private:
	void DrawLineHorizontal(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineVertical(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineDiagonal(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineBresenham(int x0, int y0, int x1, int y1, int red, int blue, int green);
};
#endif