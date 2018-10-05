#include "maths.h"

using namespace maths;

vec3::vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

vec3::vec3(vec3* vec)
{
	this->x = vec->x;
	this->y = vec->y;
	this->z = vec->z;
}

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void vec3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float vec3::magnitude()
{
	return (SQRT(this->x * this->x + this->y * this->y + this->z * this->z));
}

vec3 vec3::normalize()
{
	vec3 result;
	float m = magnitude();
	result.set(this->x / m, this->y / m, this->z / m);

	return (result);
}

vec3 vec3::cross(vec3 r)
{
	vec3 result;

	result.x = y * r.z - z * r.y;
	result.y = z * r.x - x * r.z;
	result.z = x * r.y - y * r.x;

	return (result);
}

vec3 vec3::check()
{
		float max = MAX(MAX(x, y), z);
		float min = MIN(MIN(x, y), z);

		float absMax = abs(max - 1.0F);
		float absMin = abs(min);

		float v = 0.0F;
		if (absMax > absMin)
		v = min;
		else
		v = max;
		int rv = 1;
		if (v < 0.5F)
		rv = -1;
		return vec3(v != x ? 0 : rv, v != y ? 0 : rv, v != z ? 0 : rv);
}

vec3 vec3::rotate(quat rot)
{
	quat w = rot.mul(this);
	w = w.mul(rot.conjugate());

	return (vec3(w.x, w.y, w.z));
}

float vec3::distance(vec3 a, vec3 b)
{
	return (vec3(a).sub(b).magnitude());
}

vec3 vec3::distanceVec(vec3 a, vec3 b)
{
		return (vec3(a).sub(b)).copy().negate();
}

float vec3::dot(vec3 r)
{
	return (x * r.x + y * r.y + z * r.z);
}

vec3 vec3::reflect(vec3 normal)
{
	return (sub(normal.copy().mul(dot(normal) * 2.0f)));
}

bool vec3::equals(vec3 *c)
{
		if(c->x == this->x && c->y == this->y && c->z == this->z)
				return true;
		return false;
}

int vec3::pack()
{
	 int result = (int) x << 16 | (int) y << 8 | (int) z;

	 return result;
}

vec3 vec3::unpack(int pack)
{
		int X = (pack & 0xff0000)>>16;
		int Y = (pack & 0xff00)>>8;
		int Z = (pack & 0xff);

		return vec3(X, Y, Z);
}
