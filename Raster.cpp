#include "Raster.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>

Raster::Raster(int width, int height) : width(width), height(height), pixels(new Color[width * height]){}

void Raster::SetPixel(Vector2Int coordinate, Color color)
{
	int x = coordinate.x;
	int y = coordinate.y;
	assert(x < width && y < height);
	pixels[width * x + y] = color;
}

Color Raster::GetPixel(Vector2Int coordinate)
{
	int x = coordinate.x;
	int y = coordinate.y;
	assert(x < width && y < height);

	return pixels[width * x + y];
}

void Raster::DrawLine(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)
{
	int x0 = startCoordinate.x;
	int y0 = startCoordinate.y;
	int x1 = endCoordinate.x;
	int y1 = endCoordinate.y;
	
	if(x0 == x1)
		DrawLineVertical(startCoordinate, endCoordinate, color);
	else if(y0 == y1)
		DrawLineHorizontal(startCoordinate, endCoordinate, color);
	else if(abs(x1 - x0) == abs(y1 - y0))
		DrawLineDiagonal(startCoordinate, endCoordinate, color);
	else
		DrawLineBresenham(startCoordinate, endCoordinate, color);
}

void Raster::DrawLineHorizontal(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)
{
	int x0 = startCoordinate.x;
	int y0 = startCoordinate.y;
	int x1 = endCoordinate.x;
	int y1 = endCoordinate.y;
	
	assert(y0 == y1);
	
	if(x0 > x1)
		std::swap(x0, x1);
	
	for(int x = x0; x <= x1; x++)
		SetPixel(Vector2Int(x, y0), color);
}

void Raster::DrawLineVertical(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)	
{
	int x0 = startCoordinate.x;
	int y0 = startCoordinate.y;
	int x1 = endCoordinate.x;
	int y1 = endCoordinate.y;

	assert(x0 == x1);
	
	if(y0 > y1)
		std::swap(y0, y1);
	
	for(int y = y0; y <= y1; y++)
		SetPixel(Vector2Int(x0, y), color);
}

void Raster::DrawLineDiagonal(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)
{
	int x0 = startCoordinate.x;
	int y0 = startCoordinate.y;
	int x1 = endCoordinate.x;
	int y1 = endCoordinate.y;
	
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	
	assert(dx == dy);
	
	for(int i = 0, x = x0, y = y0; i <= abs(dx); i++)
	{
		SetPixel(Vector2Int(x, y), color);
		if(x < x1)
			x++;
		else
			x--;
		
		if(y < y1)
			y++;
		else
			y--;
	}
}

void Raster::DrawLineBresenham(Vector2Int startCoordinate, Vector2Int endCoordinate, Color color)
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
	if(steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	// Swap coordinate pairs so that we will always increase
	// x when looping through the longest axis of the line.
	if(x0 > x1)
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

	for(int x=(int)x0; x<=maxX; x++)
	{
		// If it's steep, then we swap the x and y when setting,
		// the Color since we swapped it above. Otherwise, keep
		// it the same.
		if(steep)
		{
			SetPixel(Vector2Int(y,x), color);
		}
		else
		{
			SetPixel(Vector2Int(x,y), color);
		}
		
		error -= abs(dy);
		
		// If the error goes below 0, then add to y and the error.
		if(error < 0)
		{
			y += ystep;
			error += abs(dx);
		}
	}

}
