#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	
private:
	static const int MinimumHue;
	static const int MaximumHue;
	int red;
	int green;
	int blue;

	
public:
	Color();
	Color(int red, int green, int blue);
	Color operator+(const Color& rhs) const;
	Color operator-(const Color& rhs) const;
	Color operator*(const int& scalar) const;
	Color& operator+=(const Color& rhs);
	Color& operator-=(const Color& rhs);
	Color& operator*=(const int& scalar);
	friend Color operator*(const int& scalar, const Color& rhs);
	
	int GetRed();
	int GetGreen();
	int GetBlue();
	void SetRed(int red);
	void SetGreen(int green);
	void SetBlue(int blue);

private:
	void ClampHuesIfOutOfBoundaries();
	bool AreHuesWithinBoundaries();
	void ClampHuesWithinBoundaries();
	void ClampRedWithinBoundaries();
	void ClampGreenWithinBoundaries();
	void ClampBlueWithinBoundaries();
};
#endif