#include "maths.h"

using namespace maths;

vec4::vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
  this->w = 0;
}

vec4::vec4(vec4* vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
  this->w = vec->w;
}

vec4::vec4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
  this->w = w;
}

void vec4::set(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
  this->w = w;
}

float vec4::magnitude()
{
	return (SQRT(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w));
}

vec4 vec4::normalize()
{
	vec4 result;
	float m = magnitude();
	result.set(this->x / m, this->y / m, this->z / m, this->w / m);

	return (result);
}
