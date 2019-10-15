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
	Raster(int width, int height);
		
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetPixel(Vector2Int coordinate, Color color = { 255, 255, 255 });
	Color GetPixel(Vector2Int coordinate);
	void DrawLine(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color = { 255, 255, 255 });
		
private:
	void DrawLineHorizontal(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color);
	void DrawLineVertical(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color);
	void DrawLineDiagonal(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color);
	void DrawLineBresenham(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color);
};
#endif