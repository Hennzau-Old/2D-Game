#include "maths.h"

using namespace maths;

vec2::vec2()
{
	this->x = 0;
	this->y = 0;
}

vec2::vec2(vec2* vec)
{
	this->x = vec->x;
	this->y = vec->y;
}

vec2::vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

void vec2::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

float vec2::magnitude()
{
	return (SQRT(x * x + y * y));
}

vec2 vec2::normalize()
{
	vec2 result;
	float m = magnitude();
	result.set(x / m, y / m);

	return (result);
}

int vec2::pack()
{
	 int result = (int) x << 8 | (int) y;

	 return result;
}

vec2 vec2::unpack(int pack)
{
		int X = (pack & 0xff00)>>8;
		int Y = (pack & 0xff);

		return vec2(X, Y);
}
