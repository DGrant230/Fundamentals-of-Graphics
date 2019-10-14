#include <algorithm>

class Color
{
public:
	
private:
	static int const minimumHue = 0;
	static int const maximumHue = 255;
	int red;
	int green;
	int blue;

	
public:
	Color() : red(minimumHue), green(minimumHue), blue(minimumHue){}
	Color(int red, int green, int blue) : red(red), green(green), blue(blue)
	{
		if(!AreHuesWithinBoundaries())
			ClampHuesWithinBoundaries();
	}
	
private:
	bool AreHuesWithinBoundaries()
	{
		return 	(red < minimumHue) 		|| 
				(red > maximumHue) 		|| 
				(green < minimumHue) 	|| 
				(green > maximumHue) 	|| 
				(blue < minimumHue) 	|| 
				(blue > maximumHue);
	}
	
	void ClampHuesWithinBoundaries()
	{
		ClampRedWithinBoundaries();
		ClampGreenWithinBoundaries();
		ClampRedWithinBoundaries();
	}
	
	void ClampRedWithinBoundaries()
	{
		red = std::clamp(red, minimumHue, maximumHue);
	}
	
	void ClampGreenWithinBoundaries()
	{
		green = std::clamp(green, minimumHue, maximumHue);
	}

	void ClampRedWithinBoundaries()
	{
		blue = std::clamp(blue, minimumHue, maximumHue);
	}

};