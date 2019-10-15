#include "Color.h"
#include <algorithm>

const Color Color::Red = { 255, 0, 0 };
const Color Color::Green = { 0, 255, 0 };
const Color Color::Blue = { 0, 0, 255 };
const int Color::MinimumHue = 0;
const int Color::MaximumHue = 255;

Color::Color() : red(MinimumHue), green(MinimumHue), blue(MinimumHue) { }

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue)
{
	ClampHuesIfOutOfBoundaries();
}

Color Color::operator+(const Color& rhs) const
{
	Color color;
	color.SetRed(red + rhs.red);
	color.SetGreen(green + rhs.green);
	color.SetBlue(blue + rhs.blue);
	return color;
}

Color Color::operator-(const Color& rhs) const
{
	Color color;
	color.SetRed(red - rhs.red);
	color.SetGreen(green - rhs.green);
	color.SetBlue(blue - rhs.blue);
	return color;
}

Color Color::operator*(const int& scalar) const
{
	Color color;
	color.SetRed(red * scalar);
	color.SetGreen(green * scalar);
	color.SetBlue(blue * scalar);
	return color;
}

Color& Color::operator+=(const Color& rhs)
{
	SetRed(red + rhs.red);
	SetGreen(green + rhs.green);
	SetBlue(blue + rhs.blue);
	return *this;
}

Color& Color::operator-=(const Color& rhs)
{
	SetRed(red - rhs.red);
	SetGreen(green - rhs.green);
	SetBlue(blue - rhs.blue);
	return *this;
}

Color& Color::operator*=(const int& scalar)
{
	SetRed(red * scalar);
	SetGreen(green * scalar);
	SetBlue(blue * scalar);
	return *this;
}

Color operator*(const int& scalar, const Color& rhs)
{
	Color color;
	color = rhs * scalar;
	return color;
}

int Color::GetRed()
{
	return red;
}

int Color::GetGreen()
{
	return green;
}

int Color::GetBlue()
{
	return blue;
}

void Color::SetRed(int red)
{
	this->red = red;
	ClampRedWithinBoundaries();
}

void Color::SetGreen(int green)
{
	this->green = green;
	ClampGreenWithinBoundaries();
}

void Color::SetBlue(int blue)
{
	this->blue = blue;
	ClampBlueWithinBoundaries();
}


void Color::ClampHuesIfOutOfBoundaries()
{
	if(!AreHuesWithinBoundaries())
		ClampHuesWithinBoundaries();
}

bool Color::AreHuesWithinBoundaries()
{
		return 	(red < MinimumHue) 		|| 
				(red > MaximumHue) 		|| 
				(green < MinimumHue) 	|| 
				(green > MaximumHue) 	|| 
				(blue < MinimumHue) 	|| 
				(blue > MaximumHue);
}

void Color::ClampHuesWithinBoundaries()
{
	ClampRedWithinBoundaries();
	ClampGreenWithinBoundaries();
	ClampRedWithinBoundaries();
}

void Color::ClampRedWithinBoundaries()
{
	red = std::clamp(red, MinimumHue, MaximumHue);
}

void Color::ClampGreenWithinBoundaries()
{
	green = std::clamp(green, MinimumHue, MaximumHue);
}


void Color::ClampBlueWithinBoundaries()
{
	blue = std::clamp(blue, MinimumHue, MaximumHue);
}