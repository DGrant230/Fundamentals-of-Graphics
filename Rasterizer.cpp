#include "Rasterizer.h"
#include <math.h>
#include <algorithm>

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