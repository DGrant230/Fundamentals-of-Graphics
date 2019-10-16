#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "RasterDisplay.h"

class Rasterizer 
{
public:
	Rasterizer() = delete;
	Rasterizer(RasterDisplay* rasterDisplay);
	void DrawLine(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color = { 255, 255, 255 });

private:
	RasterDisplay* rasterDisplay;
};
#endif