#include <algorithm>

class Color
{
public:
	int red;
	int green;
	int blue;
	
public:
	Color() : red(0), green(0), blue(0){}
	Color(int red, int green, int blue) : red(red), green(green), blue(blue){}
	void Add(Color color);
};