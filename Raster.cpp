#include "Raster.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>

void Raster::SetPixel(int x, int y, int red, int blue, int green)
{
	assert(x < width && y < height);
	p_pixels[width * x + y] = Pixel{ red, blue, green };
}

Pixel Raster::GetPixel(int x, int y)
{
	assert(x < width && y < height);

	return p_pixels[width * x + y];
}

void Raster::DrawLine(int x0, int y0, int x1, int y1, int red, int blue, int green)
{
	if(x0 == x1)
		DrawLineVertical(x0, y0, x1, y1, red, blue, green);
	else if(y0 == y1)
		DrawLineHorizontal(x0, y0, x1, y1, red, blue, green);
	else if(abs(x1 - x0) == abs(y1 - y0))
		DrawLineDiagonal(x0, y0, x1, y1, red, blue, green);
	else
		DrawLineBresenham(x0, y0, x1, y1, red, blue, green);
}

void Raster::DrawLine(int x0, int y0, int x1, int y1, Vector3 color)
{
	DrawLine(x0, y0, x1, y1, color.x, color.y, color.z);
}

void Raster::DrawLine(Vector2 coord1, Vector2 coord2, int red, int blue, int green)
{
	DrawLine(coord1.x, coord1.y, coord2.x, coord2.y, red, blue, green);
}
void Raster::DrawLine(Vector2 coord1, Vector2 coord2, Vector3 color)
{
	DrawLine(coord1.x, coord1.y, coord2.x, coord2.y, color.x, color.y, color.z);
}


void Raster::DrawLineHorizontal(int x0, int y0, int x1, int y1, int red, int blue, int green)
{
	assert(y0 == y1);
	
	if(x0 > x1)
		std::swap(x0, x1);
	
	for(int x = x0; x <= x1; x++)
		SetPixel(x, y0, red, blue, green);
}

void Raster::DrawLineVertical(int x0, int y0, int x1, int y1, int red, int blue, int green)	
{
	assert(x0 == x1);
	
	if(y0 > y1)
		std::swap(y0, y1);
	
	for(int y = y0; y <= y1; y++)
		SetPixel(x0, y, red, blue, green);
}

void Raster::DrawLineDiagonal(int x0, int y0, int x1, int y1, int red, int blue, int green)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	
	assert(dx == dy);
	
	for(int i = 0, x = x0, y = y0; i <= abs(dx); i++)
	{
		SetPixel(x, y, red, blue, green);
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

void Raster::DrawLineBresenham(int x0, int y0, int x1, int y1, int red, int blue, int green)
{	
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
		// the pixel since we swapped it above. Otherwise, keep
		// it the same.
		if(steep)
		{
			SetPixel(y,x, red, blue, green);
		}
		else
		{
			SetPixel(x,y, red, blue, green);
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
