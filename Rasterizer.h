#ifndef RASTERIZER_H
#define RASTERIZER_H

#include "RasterDisplay.h"
#include <vector>

class Rasterizer 
{
public:
	Rasterizer() = delete;
	Rasterizer(RasterDisplay* rasterDisplay);
	void DrawLine(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color = { 255, 255, 255 });
	void DrawConnectingLine(std::vector<Vector2Int> coordinates, Color color = { 255, 255, 255 });
	void DrawPolygon(std::vector<Vector2Int> coordinates, Color color = { 255, 255, 255 });
	void DrawCircle(Vector2Int centerCoordinate, unsigned int radius, Color color = { 255, 255, 255 });
private:
	RasterDisplay* rasterDisplay;
	void DrawCircleOctantReflections(Vector2Int centerCoordinate, Vector2Int offset, Color color);
};
#endif