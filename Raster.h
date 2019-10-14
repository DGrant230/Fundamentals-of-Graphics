#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

struct Pixel
{
	int red;
	int blue;
	int green;
	
	Pixel() : red(0), blue(0), green(0){}
	Pixel(int red, int blue, int green) : red(red), blue(blue), green(green){}
};

class Raster
{
public:
	Raster() = delete;
	Raster(int width, int height) : width(width), height(height), p_pixels(new Pixel[width * height]){}
		
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetPixel(int x, int y, int red = 255, int blue = 255, int green = 255);
	Pixel GetPixel(int x, int y);
	void DrawLine(int x0, int y0, int x1, int y1, int red = 255, int blue = 255, int green = 255);
	void DrawLine(int x0, int y0, int x1, int y1, Vector3 color);
	void DrawLine(Vector2 coord1, Vector2 coord2, int red = 255, int blue = 255, int green = 255);
	void DrawLine(Vector2 coord1, Vector2 coord2, Vector3 color);
	
private:
	int width;
	int height;
	Pixel* p_pixels;
	
private:
	void DrawLineHorizontal(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineVertical(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineDiagonal(int x0, int y0, int x1, int y1, int red, int blue, int green);
	void DrawLineBresenham(int x0, int y0, int x1, int y1, int red, int blue, int green);
};
