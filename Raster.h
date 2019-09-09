struct Pixel
{
	int r;
	int b;
	int g;
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

private:
	int m_width;
	int m_height;
	Pixel* p_pixels;
};
