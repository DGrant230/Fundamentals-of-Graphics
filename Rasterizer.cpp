#include "Rasterizer.h"
#include <math.h>
#include <algorithm>
#include <stdexcept>

Rasterizer::Rasterizer(RasterDisplay* rasterDisplay) : rasterDisplay(rasterDisplay) { }

void Rasterizer::DrawLine(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)
{
	int x0 = startCoordinate.x;
	int y0 = startCoordinate.y;
	int x1 = endCoordinate.x;
	int y1 = endCoordinate.y;

	// Is the line steeper or flatter?
	const bool steep = abs(y1 - y0) > abs(x1 - x0);

	// If it's steep, flip the coordinates so that we can loop
	// through the y axis. Otherwise, we'll loop through the x
	// axis.
	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	// Swap coordinate pairs so that we will always increase
	// x when looping through the longest axis of the line.
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	// Get deltas.
	const float dx = x1 - x0;
	const float dy = y1 - y0;

	// The initial error offset.
	float error = dx / 2.0f;

	// Based on the direction of the line and where we start,
	// we need to move either left/right or up/down.
	const int ystep = (y0 < y1) ? 1 : -1;

	int y = (int)y0;

	const int maxX = (int)x1;

	for (int x = (int)x0; x <= maxX; x++)
	{
		// If it's steep, then we swap the x and y when setting,
		// the Color since we swapped it above. Otherwise, keep
		// it the same.
		if (steep)
		{
			rasterDisplay->SetPixel(Vector2Int(y, x), color);
		}
		else
		{
			rasterDisplay->SetPixel(Vector2Int(x, y), color);
		}

		error -= abs(dy);

		// If the error goes below 0, then add to y and the error.
		if (error < 0)
		{
			y += ystep;
			error += abs(dx);
		}
	}
}

void Rasterizer::DrawConnectingLine(std::vector<Vector2Int> coordinates, Color color)
{
	if(coordinates.size() < 2)
		throw std::runtime_error("Cannot draw line(s): Less than 2 coordinate points.");

	for(int i = 0; i < coordinates.size() - 1; i++)
		DrawLine(coordinates[i], coordinates[i + 1]);
}

void Rasterizer::DrawPolygon(std::vector<Vector2Int> coordinates, Color color)
{
	if(coordinates.size() < 3)
		throw std::runtime_error("Cannot draw polygon: Less than 3 coordinate points.");

	DrawConnectingLine(coordinates, color);

	DrawLine(coordinates.front(), coordinates.back());
}

void Rasterizer::DrawCircle(Vector2Int centerCoordinate, int radius, Color color)
{	
	radius = abs(radius);
	int x = 0;
	int y = radius;
	int p = 1 - radius;

	auto DrawCircleOctantReflections = [&]()
	{
		int xCenter = centerCoordinate.x;
		int yCenter = centerCoordinate.y;
		rasterDisplay->SetPixel({xCenter + x, yCenter + y}, color);
		rasterDisplay->SetPixel({xCenter + x, yCenter - y}, color);
		rasterDisplay->SetPixel({xCenter - x, yCenter + y}, color);
		rasterDisplay->SetPixel({xCenter - x, yCenter - y}, color);
		rasterDisplay->SetPixel({xCenter + y, yCenter + x}, color);
		rasterDisplay->SetPixel({xCenter + y, yCenter - x}, color);
		rasterDisplay->SetPixel({xCenter - y, yCenter + x}, color);
		rasterDisplay->SetPixel({xCenter - y, yCenter - x}, color);
	};

	while(x <= y)
	{
		DrawCircleOctantReflections();
		x++;
		if(p < 0)
			p+= 2 * x + 1;
		else
		{
			y--;
			p += 2 * (x - y) + 1;
		}
	}
}

void Rasterizer::DrawEllipse(Vector2Int centerCoordinate, int widthRadius, int heightRadius, Color color)
{
	if(widthRadius == heightRadius)
	{
		DrawCircle(centerCoordinate, widthRadius, color);
		return;
	}

	widthRadius = abs(widthRadius);
	heightRadius = abs(heightRadius);
	int widthRadiusSquared = widthRadius * widthRadius;
	int heightRadiusSquared = heightRadius * heightRadius;	
	int px = round(heightRadiusSquared - widthRadiusSquared * heightRadius + 0.25f * widthRadiusSquared);
	int py = round(widthRadiusSquared - heightRadiusSquared * widthRadius + 0.25f * heightRadiusSquared);
	int x0 = 0;
	int y0 = heightRadius;
	int x1 = widthRadius;
	int y1 = 0;

	auto IsWithinRegion1 = [&](int x, int y)
	{	
		return 2 * heightRadiusSquared * x <  2 * widthRadiusSquared * y;
	};

	auto IsInsideEllipseBoundary = [&](int p)
	{
		return p < 0;
	};

	auto DrawEllipseOctantReflections = [&](int x, int y)
	{
		int xCenter = centerCoordinate.x;
		int yCenter = centerCoordinate.y;
		rasterDisplay->SetPixel({xCenter + x, yCenter + y}, color);
		rasterDisplay->SetPixel({xCenter + x, yCenter - y}, color);
		rasterDisplay->SetPixel({xCenter - x, yCenter + y}, color);
		rasterDisplay->SetPixel({xCenter - x, yCenter - y}, color);
	};

	while(IsWithinRegion1(x0, y0))
	{
		DrawEllipseOctantReflections(x0, y0);
		if(IsInsideEllipseBoundary(px))
			px += 2 * heightRadiusSquared * x0 + 3 * heightRadiusSquared;
		else
		{
			px += 2 * heightRadiusSquared * x0 + 3 * heightRadiusSquared - 2 * widthRadiusSquared * y0 + 2 * widthRadiusSquared;
			y0--;
		}
		x0++;
	}

	while(!IsWithinRegion1(x1, y1))
	{
		DrawEllipseOctantReflections(x1, y1);
		if(IsInsideEllipseBoundary(py))
			py += 2 * widthRadiusSquared * y1 + 3 * widthRadiusSquared;
		else
		{
			py += 2 * widthRadiusSquared * y1 + 3 * widthRadiusSquared - 2 * heightRadiusSquared * x1 + 2 * heightRadiusSquared;
			x1--;	
		}
		y1++;
	}
}