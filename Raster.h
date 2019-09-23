struct Pixel
{
	int r;
	int b;
	int g;
	
	Pixel()
	{
		r = 0;
		b = 0;
		g = 0;
	}
	
	Pixel(int r, int b, int g)
	{
		this->r = r;
		this->b = b;
		this->g = g;
	}
};

class Raster
{
public:
	Raster() = delete;
	Raster(int width, int height);
	int GetWidth() { return m_width; }
	int GetHeight() { return m_height; }
	void SetPixel(int x, int y, int r, int b, int g);
	Pixel GetPixel(int x, int y);
	void DrawLineDDA(int x0, int y0, int x1, int y1);
	void DrawLineBresenham(int x0, int y0, int x1, int y1);
	void DrawLineMidPoint(int x0, int y0, int x1, int y1);

private:
	int m_width;
	int m_height;
	Pixel* p_pixels;
};
