#include "maths.h"

using namespace maths;

mat4 mat4::mul(mat4 m)
{
	mat4 result = identity();

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			result.m_matrix[x + y * 4] = m_matrix[x + 0 * 4] * m.m_matrix[0 + y * 4] +
				m_matrix[x + 1 * 4] * m.m_matrix[1 + y * 4] +
				m_matrix[x + 2 * 4] * m.m_matrix[2 + y * 4] +
				m_matrix[x + 3 * 4] * m.m_matrix[3 + y * 4];
		}
	}
	return (result);
}

mat4 mat4::identity()
{
	mat4 result;

	for (int i = 0; i < 4 * 4; i++)
		result.m_matrix[i] = 0.0f;

	result.m_matrix[0 + 0 * 4] = 1;
	result.m_matrix[1 + 1 * 4] = 1;
	result.m_matrix[2 + 2 * 4] = 1;
	result.m_matrix[3 + 3 * 4] = 1;

	return (result);
}

mat4 mat4::translate(float x, float y, float z)
{
	mat4 result = identity();

	result.m_matrix[0 + 3 * 4] = x;
	result.m_matrix[1 + 3 * 4] = y;
	result.m_matrix[2 + 3 * 4] = z;

	return (result);
}

mat4 mat4::translate(vec3 pos)
{
	return (translate(pos.x, pos.y, pos.z));
}

mat4 mat4::rotate(float x, float y, float z)
{
	mat4 result = identity();

	mat4 rx = identity();
	mat4 ry = identity();
	mat4 rz = identity();

	x = TO_RADIANS(x);
	y = TO_RADIANS(y);
	z = TO_RADIANS(z);

	rx.m_matrix[1 + 1 * 4] = COS(x);
	rx.m_matrix[1 + 2 * 4] = -SIN(x);
	rx.m_matrix[2 + 1 * 4] = SIN(x);
	rx.m_matrix[2 + 2 * 4] = COS(x);

	ry.m_matrix[0 + 0 * 4] = COS(y);
	ry.m_matrix[0 + 2 * 4] = -SIN(y);
	ry.m_matrix[2 + 0 * 4] = SIN(y);
	ry.m_matrix[2 + 2 * 4] = COS(y);

	rz.m_matrix[0 + 0 * 4] = COS(z);
	rz.m_matrix[0 + 1 * 4] = -SIN(z);
	rz.m_matrix[1 + 0 * 4] = SIN(z);
	rz.m_matrix[1 + 1 * 4] = COS(z);

	result = rz.mul(ry.mul(rx));

	return (result);
}

mat4 mat4::rotate(vec3 forward, vec3 up, vec3 right)
{
	mat4 result = identity();

	vec3 f(forward);
	vec3 r(right);
	vec3 u(up);

	f.normalize();
	r.normalize();
	u.normalize();

	result.m_matrix[0 + 0 * 4] = r.x;
	result.m_matrix[0 + 1 * 4] = r.y;
	result.m_matrix[0 + 2 * 4] = r.z;

	result.m_matrix[1 + 0 * 4] = u.x;
	result.m_matrix[1 + 1 * 4] = u.y;
	result.m_matrix[1 + 2 * 4] = u.z;

	result.m_matrix[2 + 0 * 4] = f.x;
	result.m_matrix[2 + 1 * 4] = f.y;
	result.m_matrix[2 + 2 * 4] = f.z;

	return (result);
}

mat4 mat4::scale(float x, float y, float z)
{
	mat4 result = identity();

	result.m_matrix[0 + 0 * 4] = x;
	result.m_matrix[1 + 1 * 4] = y;
	result.m_matrix[2 + 2 * 4] = z;

	return (result);
}

mat4 mat4::cameraView(vec3 forward, vec3 up)
{
	mat4 m = identity();

	vec3 f(forward);
	vec3 r(up);

	f = f.normalize();
	r = r.normalize();

	r = r.cross(f);
	vec3 u = f.cross(r);

	m.m_matrix[0 + 0 * 4] = r.x;
	m.m_matrix[0 + 1 * 4] = r.y;
	m.m_matrix[0 + 2 * 4] = r.z;

	m.m_matrix[1 + 0 * 4] = u.x;
	m.m_matrix[1 + 1 * 4] = u.y;
	m.m_matrix[1 + 2 * 4] = u.z;

	m.m_matrix[2 + 0 * 4] = f.x;
	m.m_matrix[2 + 1 * 4] = f.y;
	m.m_matrix[2 + 2 * 4] = f.z;

	return (m);
}

mat4 mat4::perspective(float fov, float aspect, float near, float far)
{
	mat4 result = identity();

	float FOV = TAN(TO_RADIANS(fov / 2));
	float r = near - far;

	result.m_matrix[0 + 0 * 4] = 1.0f / (FOV * aspect);
	result.m_matrix[1 + 1 * 4] = 1.0f / FOV;

	result.m_matrix[2 + 2 * 4] = (-near - far) / r;
	result.m_matrix[2 + 3 * 4] = 2 * far * near / r;

	result.m_matrix[3 + 2 * 4] = 1;
	result.m_matrix[3 + 3 * 4] = 0;

	return (result);
}

mat4 mat4::orthographic(float right, float left, float top, float bottom, float near, float far)
{
	mat4 m = identity();

	m.m_matrix[0 + 0 * 4] = 2 / (right - left);
	m.m_matrix[0 + 3 * 4] = -(right + left) / (right - left);

	m.m_matrix[1 + 1 * 4] = 2 / (top - bottom);
	m.m_matrix[1 + 3 * 4] = -(top + bottom) / (top - bottom);

	m.m_matrix[2 + 2 * 4] = -2 / (far - near);
	m.m_matrix[2 + 3 * 4] = -(far + near) / (far - near);

	return (m);
}

mat4 mat4::inverse(mat4 m)
{
		float determinant = m.determinant(m);

		if (determinant != 0) {

			float determinant_inv = 1.0f / determinant;
			mat4 dest;
			// first row
			float t00 =  determinant3x3(m.mat(1, 1), m.mat(1, 2), m.mat(1, 3), m.mat(2, 1), m.mat(2, 2), m.mat(2, 3), m.mat(3, 1), m.mat(3, 2), m.mat(3, 3));
			float t01 = -determinant3x3(m.mat(1, 0), m.mat(1, 2), m.mat(1, 3), m.mat(2, 0), m.mat(2, 2), m.mat(2, 3), m.mat(3, 0), m.mat(3, 2), m.mat(3, 3));
			float t02 =  determinant3x3(m.mat(1, 0), m.mat(1, 1), m.mat(1, 3), m.mat(2, 0), m.mat(2, 1), m.mat(2, 3), m.mat(3, 0), m.mat(3, 1), m.mat(3, 3));
			float t03 = -determinant3x3(m.mat(1, 0), m.mat(1, 1), m.mat(1, 2), m.mat(2, 0), m.mat(2, 1), m.mat(2, 2), m.mat(3, 0), m.mat(3, 1), m.mat(3, 2));
			// second row
			float t10 = -determinant3x3(m.mat(0, 1), m.mat(0, 2), m.mat(0, 3), m.mat(2, 1), m.mat(2, 2), m.mat(2, 3), m.mat(3, 1), m.mat(3, 2), m.mat(3, 3));
			float t11 =  determinant3x3(m.mat(0, 0), m.mat(0, 2), m.mat(0, 3), m.mat(2, 0), m.mat(2, 2), m.mat(2, 3), m.mat(3, 0), m.mat(3, 2), m.mat(3, 3));
			float t12 = -determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 3), m.mat(2, 0), m.mat(2, 1), m.mat(2, 3), m.mat(3, 0), m.mat(3, 1), m.mat(3, 3));
			float t13 =  determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 2), m.mat(2, 0), m.mat(2, 1), m.mat(2, 2), m.mat(3, 0), m.mat(3, 1), m.mat(3, 2));
			// third row
			float t20 =  determinant3x3(m.mat(0, 1), m.mat(0, 2), m.mat(0, 3), m.mat(1, 1), m.mat(1, 2), m.mat(1, 3), m.mat(3, 1), m.mat(3, 2), m.mat(3, 3));
			float t21 = -determinant3x3(m.mat(0, 0), m.mat(0, 2), m.mat(0, 3), m.mat(1, 0), m.mat(1, 2), m.mat(1, 3), m.mat(3, 0), m.mat(3, 2), m.mat(3, 3));
			float t22 =  determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 3), m.mat(1, 0), m.mat(1, 1), m.mat(1, 3), m.mat(3, 0), m.mat(3, 1), m.mat(3, 3));
			float t23 = -determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 2), m.mat(1, 0), m.mat(1, 1), m.mat(1, 2), m.mat(3, 0), m.mat(3, 1), m.mat(3, 2));
			// fourth row
			float t30 = -determinant3x3(m.mat(0, 1), m.mat(0, 2), m.mat(0, 3), m.mat(1, 1), m.mat(1, 2), m.mat(1, 3), m.mat(2, 1), m.mat(2, 2), m.mat(2, 3));
			float t31 =  determinant3x3(m.mat(0, 0), m.mat(0, 2), m.mat(0, 3), m.mat(1, 0), m.mat(1, 2), m.mat(1, 3), m.mat(2, 0), m.mat(2, 2), m.mat(2, 3));
			float t32 = -determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 3), m.mat(1, 0), m.mat(1, 1), m.mat(1, 3), m.mat(2, 0), m.mat(2, 1), m.mat(2, 3));
			float t33 =  determinant3x3(m.mat(0, 0), m.mat(0, 1), m.mat(0, 2), m.mat(1, 0), m.mat(1, 1), m.mat(1, 2), m.mat(2, 0), m.mat(2, 1), m.mat(2, 2));

			// transpose and divide by the determinant
			dest.m_matrix[0 + 0 * 4] = t00*determinant_inv;
			dest.m_matrix[1 + 1 * 4] = t11*determinant_inv;
			dest.m_matrix[2 + 2 * 4] = t22*determinant_inv;
			dest.m_matrix[3 + 3 * 4] = t33*determinant_inv;
			dest.m_matrix[0 + 1 * 4] = t10*determinant_inv;
			dest.m_matrix[1 + 0 * 4] = t01*determinant_inv;
			dest.m_matrix[2 + 0 * 4] = t02*determinant_inv;
			dest.m_matrix[0 + 2 * 4] = t20*determinant_inv;
			dest.m_matrix[1 + 2 * 4] = t21*determinant_inv;
			dest.m_matrix[2 + 1 * 4] = t12*determinant_inv;
			dest.m_matrix[0 + 3 * 4] = t30*determinant_inv;
			dest.m_matrix[3 + 0 * 4] = t03*determinant_inv;
			dest.m_matrix[1 + 3 * 4] = t31*determinant_inv;
			dest.m_matrix[3 + 1 * 4] = t13*determinant_inv;
			dest.m_matrix[3 + 2 * 4] = t23*determinant_inv;
			dest.m_matrix[2 + 3 * 4] = t32*determinant_inv;

			return dest;
		}
		return identity();
}

float mat4::determinant(mat4 m)
{
	float f =
	  m.mat(0, 0)
	    * ((m.mat(1, 1) * m.mat(2, 2) * m.mat(3, 3) + m.mat(1, 2) * m.mat(2, 3) * m.mat(3, 1) + m.mat(1, 3) * m.mat(2, 1) * m.mat(3, 2))
	      - m.mat(1, 3) * m.mat(2, 2) * m.mat(3, 1)
	      - m.mat(1, 1) * m.mat(2, 3) * m.mat(3, 2)
	      - m.mat(1, 2) * m.mat(2, 1) * m.mat(3, 3));
	f -= m.mat(0, 1)
	  * ((m.mat(1, 0) * m.mat(2, 2) * m.mat(3, 3) + m.mat(1, 2) * m.mat(2, 3) * m.mat(3, 0) + m.mat(1, 3) * m.mat(2, 0) * m.mat(3, 2))
	    - m.mat(1, 3) * m.mat(2, 2) * m.mat(3, 0)
	    - m.mat(1, 0) * m.mat(2, 3) * m.mat(3, 2)
	    - m.mat(1, 2) * m.mat(2, 0) * m.mat(3, 3));
	f += m.mat(0, 2)
	  * ((m.mat(1, 0) * m.mat(2, 1) * m.mat(3, 3) + m.mat(1, 1) * m.mat(2, 3) * m.mat(3, 0) + m.mat(1, 3) * m.mat(2, 0) * m.mat(3, 1))
	    - m.mat(1, 3) * m.mat(2, 1) * m.mat(3, 0)
	    - m.mat(1, 0) * m.mat(2, 3) * m.mat(3, 1)
	    - m.mat(1, 1) * m.mat(2, 0) * m.mat(3, 3));
	f -= m.mat(0, 3)
	  * ((m.mat(1, 0) * m.mat(2, 1) * m.mat(3, 2) + m.mat(1, 1) * m.mat(2, 2) * m.mat(3, 0) + m.mat(1, 2) * m.mat(2, 0) * m.mat(3, 1))
	    - m.mat(1, 2) * m.mat(2, 1) * m.mat(3, 0)
	    - m.mat(1, 0) * m.mat(2, 2) * m.mat(3, 1)
	    - m.mat(1, 1) * m.mat(2, 0) * m.mat(3, 2));
		return f;
}

float mat4::determinant3x3(float t00, float t01, float t02,
				     float t10, float t11, float t12,
				     float t20, float t21, float t22)
{
		return   t00 * (t11 * t22 - t12 * t21)
				       + t01 * (t12 * t20 - t10 * t22)
				       + t02 * (t10 * t21 - t11 * t20);
}

vec3 mat4::transform(mat4 m, vec3 v)
{
	vec3 result;

	result.set(
		m.m_matrix[0 + 0 * 4] * v.x + m.m_matrix[0 + 1 * 4] * v.y + m.m_matrix[0 + 2 * 4] * v.z + m.m_matrix[0 + 3 * 4],
		m.m_matrix[1 + 0 * 4] * v.x + m.m_matrix[1 + 1 * 4] * v.y + m.m_matrix[1 + 2 * 4] * v.z + m.m_matrix[1 + 3 * 4],
		m.m_matrix[2 + 0 * 4] * v.x + m.m_matrix[2 + 1 * 4] * v.y + m.m_matrix[2 + 2 * 4] * v.z + m.m_matrix[2 + 3 * 4]
	);

	return (result);
}

vec4 mat4::transform(mat4 m, vec4 v)
{
	vec4 result;

	result.set(
		m.m_matrix[0 + 0 * 4] * v.x + m.m_matrix[0 + 1 * 4] * v.y + m.m_matrix[0 + 2 * 4] * v.z + m.m_matrix[0 + 3 * 4] * v.w,
		m.m_matrix[1 + 0 * 4] * v.x + m.m_matrix[1 + 1 * 4] * v.y + m.m_matrix[1 + 2 * 4] * v.z + m.m_matrix[1 + 3 * 4] * v.w,
		m.m_matrix[2 + 0 * 4] * v.x + m.m_matrix[2 + 1 * 4] * v.y + m.m_matrix[2 + 2 * 4] * v.z + m.m_matrix[2 + 3 * 4] * v.w,
		m.m_matrix[3 + 0 * 4] * v.x + m.m_matrix[3 + 1 * 4] * v.y + m.m_matrix[3 + 2 * 4] * v.z + m.m_matrix[3 + 3 * 4] * v.w
	);

	return (result);
}

/*

vec4 transform(mat4 left, vec4 right)
{
    float x = left[0][0] * right.x + left[1][0] * right.y + left[2][0] * right.z + left[3][0] * right.w;
		float y = left[0][1] * right.x + left[1][1] * right.y + left[2][1] * right.z + left[3][1] * right.w;
		float z = left[0][2] * right.x + left[1][2] * right.y + left[2][2] * right.z + left[3][2] * right.w;
		float w = left[0][3] * right.x + left[1][3] * right.y + left[2][3] * right.z + left[3][3] * right.w;

    return vec4(x, y, z, w);
}
*/

float mat4::mat(int x, int y)
{
		return m_matrix[x + y * 4];
}
