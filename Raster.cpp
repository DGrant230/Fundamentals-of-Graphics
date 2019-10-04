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
/* 	
	Slope 
	y = mx + b
	y = (dy / dx)x + b
	(dx)y = (dy)x + (dx)b
	0 = (dy)x - (dx)y + (dx)b
	
	f(x, y) = 0 = (dy)x - (dx)y + (dx)b
	Starting point: f(x, y) = 0 -> Is directly on the line (it's one of the end points)
	Next Point: f(x + 1, y + 0.5) = s
	The value of s determines if the line above or below (x + 1, y + 0.5)
	If positive, plot (x + 1, y + 1), else plot (x + 1, y)
	
	To avoid floating point arimetic, use a decision parameter instead of the value of s.
	To get the first decision parameter:
	D = f(x + 1, y + 1/2) - f(x, y)
	D = (dy)(x + 1) - (dx)(y + 1/2) + (dx)b - (dy)x - (dx)y + (dx)b
	D = (dy)x + dy - (dx)y + dx/2 + (dx)b - (dy)x - (dx)y + (dx)b
	Cancel out: (dy)x, (dx)y, and (dx)b
	Results in: dy - dx / 2 = 2 * dy - dx
	D = 2 * dy - dx
	
	For subsequent decision parameter values, accumulate the difference of error
	If D > 0 and abs(dx) > abs(dy), D = D - 2 * dx
	If D > 0 and abs(dy) > abs(dx), D = D - 2 * dy
	
	To cover all cases of how the line is formed in different octants, we need to check
	if to see if the line is longer than wider or vice versa to increment through. 
	I = abs(dy) < abs(dx)
	
	If I = true, increment through the x axis. Otherwise, increment through the y axis.
	
	After determining which axis to use, ensure that the starting coordinate is less than the ending coordinate
	on that axis.
	Ex: If I = true, start = (5, 3), and end = (0, 2), switch the values of start and end.
	
	Lastly, check if the value of the delta of whatever is lowest and see if it's negative.
	If so, that's the direction you'll be incrementing towards.
	Ex: If x axis > y axis, check value of dy. If dy < 0, then the line is going downwards.
 */	
	
	// Avoiding two extra calculations.
	SetPixel(x0, y0, 0, 255, 0);
	SetPixel(x1, y1, 0, 255, 0);
	
	// Get deltas.
	int dx = x1 - x0;
	int dy = y1 - y0;
	
	// Is the line wider than longer?
	bool isWider = false;
	
	if(abs(dx) > abs(dy))
		isWider = true;
	
	// If the line is wider and the starting coordinate x value is larger than the ending coordinate x value,
	// then swap the coordinates. Likewise if the line was longer than wider for the y values.
	if((isWider && x0 > x1) || (!isWider && y0 > y1))
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
		dx = x1 - x0;
		dy = y1 - y0;
	}
	
	// While incrementing through the longer axis of the line, do we go the negative direction (left or down)
	// for producing the next coordinate?
	bool goNegativeDirection = false;
	
	if((isWider && dx < 0) || (!isWider && dy < 0))
		goNegativeDirection = true;
	
	// The decision parameter.
	int dp = 2 * dy - dx;
	
	if(isWider)
	{
		// If wider, incrememt through the x axis
		for(int x = x0 + 1, y = y0; x < x1; x++)
		{
			if(dp > 0)
			{
				// 
				y += goNegativeDirection ? -1 : 1;
				dp -= 2 * dx;
			}
			
			dp += 2 * dy;
			SetPixel(x, y, 0, 255, 0);
		}
	}
	else
	{
		// If longer, increment through the y axis
		for(int y = y0 + 1, x = x0; y < y1; y++)
		{
			if(dp > 0)
			{
				x += goNegativeDirection ? -1 : 1;
				dp -= 2 * dy;
			}
			
			dp += 2 * dx;
			SetPixel(x, y, 0, 255, 0);
		}
	}
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