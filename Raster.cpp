#include "Raster.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <algorithm>

Raster::Raster(int width, int height)
{
	m_width = width;
	m_height = height;
	p_pixels = new Pixel[width * height];
}

void Raster::SetPixel(int x, int y, int r, int b, int g)
{
	assert(x < m_width && y < m_height);
	p_pixels[m_width * x + y] = Pixel{ r, b, g };
}

Pixel Raster::GetPixel(int x, int y)
{
	assert(x < m_width && y < m_height);

	return p_pixels[m_width * x + y];
}

void Raster::DrawLineDDA(int x0, int y0, int x1, int y1)
{
	// Digital Differential Analyzer Algorithm	
	float x = x0;
	float y = y0;

	int dx = x1 - x0;
	int dy = y1 - y0;

	int steps = std::max(abs(dx), abs(dy));

	float xinc = (float)dx / steps;
	float yinc = (float)dy / steps;

	for(int i = 0; i <= steps; i++)
	{
		SetPixel(round(x), round(y), 255, 255, 255);
		x += xinc;
		y += yinc;
	}
}

void Raster::DrawLineBresenham(int x0, int y0, int x1, int y1)
{
	// if m < 1
	int dx = x1 - x0;
	int dy = y1 - y0;
	int b = y0;
	
	float m = dy / dx;	
	printf("dx = %i\n", dx);
	printf("dy = %i\n", dy);

	printf("m = %f\n", m);
	
	for(int x = x0; x <= x1; x++)
	{
		float y = m * x + b;
		printf("y = %f\n", y);
		int dLower = (int)y;
		int dUpper = dLower + 1;
		
		float dLowerDist = y - dLower;
		float dUpperDist = dUpper - y;
		
		if(dLowerDist < dUpperDist)
		{
			SetPixel(x, dLower, 0, 255, 0);
		}
		else
		{
			SetPixel(x, dUpper, 0, 255, 0);
		}
	}
	
  // Bresenham's Line Algorithm
  // const bool steep = (abs(y1 - y0) > abs(x1 - x0));
  // if(steep)
  // {
    // std::swap(x0, y0);
    // std::swap(x1, y1);
  // }
 
  // if(x0 > x1)
  // {
    // std::swap(x0, x1);
    // std::swap(y0, y1);
  // }
 
  // const float dx = x1 - x0;
  // const float dy = abs(y1 - y0);
 
  // float error = dx / 2.0f;
  // const int ystep = (y0 < y1) ? 1 : -1;
  // int y = (int)y0;
 
  // const int maxX = (int)x1;
 
  // for(int x=(int)x0; x<maxX; x++)
  // {
    // if(steep)
    // {
		// SetPixel(y, x, 0, 255, 0);
    // }
    // else
    // {
		// SetPixel(x, y, 0, 255, 0);
    // }
 
    // error -= dy;
    // if(error < 0)
    // {
        // y += ystep;
        // error += dx;
    // }
  // }
}

void DrawLineMidPoint(int x0, int y0, int x1, int y1)
{
	// MidPoint Algorithm
	// Slope-Intercept: y = mx + b => 0 = mx + b - y
	// Slope: m = dy / dx => m = (y1 - y0)/(x1 - x0) : x1 > x0
	// Implicit Equation: 0 = (dy / dx)x + b - y => 0 = (dy)x + b(dx) - y(dx)
	// If F(x, y) = 0, point is on line; if < 0, point is above line; if > 0, point is below line
	
	// int dx = x1 - x0;
	// int dy = y1 - y0;
	
	// Set initial point
	// int x = x0;
	// int y = y0;
	
	// while(x <= x1)
	// {
		// int d = (dy * x) - (dy * y) + (dx + b);
	// }
}