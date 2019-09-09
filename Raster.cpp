#include "Raster.h"
#include <assert.h>

Raster::Raster(int width, int height)
{
	m_width = width;
	m_height = height;
	p_pixels = new Pixel[width * height];
}

void Raster::SetPixel(int x, int y, int r, int b, int g)
{
	assert(x < m_width && y < m_height);
	p_pixels[m_width * y + x] = Pixel{ r, b, g };
}

Pixel Raster::GetPixel(int x, int y)
{
	assert(x < m_width && y < m_height);

	return p_pixels[m_width * y + x];
}
