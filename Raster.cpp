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

	return p_pixels[m_width * y + x];
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
  // Bresenham's Line Algorithm
  const bool steep = (abs(y1 - y0) > abs(x1 - x0));
  if(steep)
  {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
 
  if(x0 > x1)
  {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
 
  const float dx = x1 - x0;
  const float dy = abs(y1 - y0);
 
  float error = dx / 2.0f;
  const int ystep = (y0 < y1) ? 1 : -1;
  int y = (int)y0;
 
  const int maxX = (int)x1;
 
  for(int x=(int)x0; x<maxX; x++)
  {
    if(steep)
    {
		SetPixel(y, x, 0, 255, 0);
    }
    else
    {
		SetPixel(x, y, 0, 255, 0);
    }
 
    error -= dy;
    if(error < 0)
    {
        y += ystep;
        error += dx;
    }
  }
}

