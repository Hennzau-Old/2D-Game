#ifndef MATH_H
# define MATH_H

# include <math.h>

# define PI 3.14159265358979323846264338327950288419716939937510582

# define TO_RADIANS(x) (float) (x * PI / 180.0f)
# define TO_DEGREES(x) (float) (x * 180.0f / PI)

# define SQRT(x) (float) (sqrt(x))
# define POW(x) (float) (pow(x))

# define COS(x) (float) (cos(x))
# define SIN(x) (float) (sin(x))
# define TAN(x) (float) (tan(x))

# define ACOS(x) (float) (acos(x))
# define ASIN(x) (float) (asin(x))
# define ATAN(x) (float) (atan(x))
# define ATAN2(x) (float) (atan2(x))

# define LERP(a, b, t) (float) (a + (b - a) * t)

# define MAX(a, b) (float) (a > b ? a : b)
# define MIN(a, b) (float) (a < b ? a : b)

static float CLERP(float s, float e, float t)
{
		float result = (1 - COS(t * PI)) / 2;

		return (s * (1 - result) + e * result);
}

namespace maths
{
	class vec2;
	class vec3;
	class vec4;
	class mat4;
	class quat;
	class color4f;

	class vec2
	{
	public:
		float x;
		float y;

		vec2();
		vec2(float x, float y);
		vec2(vec2 *v);
		void set(float x, float y);

		int pack();

		static vec2 unpack(int pack);

		float magnitude();
		vec2 normalize();

		//ADD
		inline vec2 add(float x, float y)
		{
			this->x += x;
			this->y += y;

			return (this);
		}
		inline vec2 add(float v) { return add(v, v); };
		inline vec2 add(vec2 v) { return add(v.x, v.y); };

		//SUB
		inline vec2 sub(float x, float y)
		{
			this->x -= x;
			this->y -= y;

			return (this);
		}
		inline vec2 sub(float v) { return sub(v, v); };
		inline vec2 sub(vec2 v) { return sub(v.x, v.y); };

		//MUL
		inline vec2 mul(float x, float y)
		{
			this->x *= x;
			this->y *= y;

			return (this);
		}
		inline vec2 mul(float v) { return mul(v, v); };
		inline vec2 mul(vec2 v) { return mul(v.x, v.y); };

		//DIV
		inline vec2 div(float x, float y)
		{
			this->x /= x;
			this->y /= y;

			return (this);
		}
		inline vec2 div(float v) { return div(v, v); };
		inline vec2 div(vec2 v) { return div(v.x, v.y); };

		inline vec2 copy() { return vec2(this->x, this->y); };
		inline vec2 negate() { this->x *= -1; this->y *= -1; return this;};

	};


	class vec3
	{
	public:
		float x;
		float y;
		float z;

		vec3();
		vec3(float x, float y, float z);
		vec3(vec3 *v);
		void set(float x, float y, float z);

		int pack();

		static vec3 unpack(int pack);

		float magnitude();
		vec3 normalize();
		vec3 cross(vec3 r);
		vec3 check();

		vec3 rotate(quat rot);
		float dot(vec3 r);
		vec3 reflect(vec3 normal);

		static float distance(vec3 a, vec3 b);
		static vec3 distanceVec(vec3 a, vec3 b);


		//ADD
		inline vec3 add(float x, float y, float z)
		{
			this->x += x;
			this->y += y;
			this->z += z;

			return (this);
		}
		inline vec3 add(float v) { return add(v, v, v); };
		inline vec3 add(vec3 v) { return add(v.x, v.y, v.z); };

		//SUB
		inline vec3 sub(float x, float y, float z)
		{
			this->x -= x;
			this->y -= y;
			this->z -= z;

			return (this);
		}
		inline vec3 sub(float v) { return sub(v, v, v); };
		inline vec3 sub(vec3 v) { return sub(v.x, v.y, v.z); };

		//MUL
		inline vec3 mul(float x, float y, float z)
		{
			this->x *= x;
			this->y *= y;
			this->z *= z;

			return (this);
		}
		inline vec3 mul(float v) { return mul(v, v, v); };
		inline vec3 mul(vec3 v) { return mul(v.x, v.y, v.z); };

		//DIV
		inline vec3 div(float x, float y, float z)
		{
			this->x /= x;
			this->y /= y;
			this->z /= z;

			return (this);
		}

		bool				equals(vec3 *c);

		inline vec3 div(float v) { return div(v, v, v); };
		inline vec3 div(vec3 v) { return div(v.x, v.y, v.z); };

		inline vec3 copy() { return vec3(this->x, this->y, this->z); };
		inline vec3 negate() { this->x *= -1; this->y *= -1; this->z *= -1; return this;};
	};

	class vec4
	{
	public:
		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(float x, float y, float z, float w);
		vec4(vec4 *v);
		void set(float x, float y, float z, float w);

		float magnitude();
		vec4 normalize();
	};

	class mat4
	{
	public:
		float m_matrix[4 * 4];

		mat4 mul(mat4 m);

		static mat4 identity();

		static mat4 translate(float x, float y, float z);
		static mat4 translate(vec3 pos);
		static mat4 rotate(float x, float y, float z);
		static mat4 rotate(vec3 forward, vec3 up, vec3 right);
		static mat4 scale(float x, float y, float z);

		static mat4 cameraView(vec3 forward, vec3 up);
		static mat4 perspective(float fov, float aspect, float near, float far);
		static mat4 orthographic(float right, float left, float top, float bottom, float near, float far);
		static mat4 inverse(mat4 m);
		static float determinant(mat4 m);
		static float determinant3x3(float t00, float t01, float t02,
				     float t10, float t11, float t12,
				     float t20, float t21, float t22);
		float mat(int x, int y);

		static vec3 transform(mat4 m, vec3 v);
		static vec4 transform(mat4 m, vec4 v);
	};

	class quat
	{
	public:
		float x;
		float y;
		float z;
		float w;

		quat();
		quat(quat* q);
		quat(float x, float y, float z, float w);
		quat(vec3 axis, float angle);
		void set(float x, float y, float z, float w);

		float magnitude();
		quat normalize();
		quat conjugate();
		quat mul(quat r);
		quat mul(vec3 r);
		float dot(quat r);

		mat4 to_matrix();

		vec3 getForward();
		vec3 getBack();
		vec3 getRight();
		vec3 getLeft();
		vec3 getUp();
		vec3 getDown();
	};

	class color4f
	{
	public:
			color4f();
			color4f(color4f *c);
			color4f(int rgb);
			color4f(int r, int g, int b);
			color4f(int r, int g, int b, int a);
			color4f(float r, float g, float b);
			color4f(float r, float g, float b, float a);

			static int getColor(int r, int g, int b, int a);
			static float getColor(float r, float g, float b, float a);
			static int getARGB(color4f c);

			vec3 rgb();
			int getARGB();
			static color4f getColorFromARGB(int argb);
			static color4f mix(color4f *ca, color4f *cb, float t);

			color4f copy() { return color4f(r, g, b, a); }

			float r, g, b, a;
	};
}


#endif
