#include "maths.h"

using namespace maths;

color4f::color4f(color4f *c)
{
    r = c->r;
    g = c->g;
    b = c->b;
    a = c->a;
}

color4f::color4f(int rgb)
{
    int R = (rgb & 0xff0000) >> 16;
    int G = (rgb & 0xff00) >> 8;
    int B = (rgb & 0xff);

    this->r = (float) R / 255.0f;
    this->g = (float) G / 255.0f;
    this->b = (float) B / 255.0f;
    this->a = 1;
}

color4f::color4f(int r, int g, int b)
{
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = 1;
}

color4f::color4f(int r, int g, int b, int a)
{
    this->r = r / 255.0f;
    this->g = g / 255.0f;
    this->b = b / 255.0f;
    this->a = a / 255.0f;
}

color4f::color4f(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 1;
}

color4f::color4f(float r, float g, float b, float a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

int color4f::getColor(int r, int g, int b, int a)
{
    return a << 24 | r << 16 | g << 8 | b;
}

float color4f::getColor(float r, float g, float b, float a)
{
    int rr = (int) (r * 255);
    int gg = (int) (g * 255);
    int bb = (int) (b * 255);
    int aa = (int) (a * 255);

    return getColor(rr, gg, bb, aa);
}

vec3 color4f::rgb()
{
    return vec3(r, g, b);
}

int color4f::getARGB()
{
    int A = (int) (a*127.0f);
    int R = (int) (r*255.0f);
    int G = (int) (g*255.0f);
    int B = (int) (b*255.0f);
    int rgb = 0;

    rgb = A << 24 | R << 16 | G << 8 | B;
    return rgb;
}

color4f color4f::getColorFromARGB(int argb)
{
    color4f color = color4f(0, 0, 0, 0);
    int A = (argb & 0xff000000)>>24;
		int R = (argb & 0xff0000)>>16;
		int G = (argb & 0xff00)>>8;
		int B = (argb & 0xff);

    color.r = (float) R/255.0f;
    color.g = (float) G/255.0f;
    color.b = (float) B/255.0f;
    color.a = (float) A/127.0f;

    return color;
}

color4f color4f::mix(color4f *ca, color4f *cb, float t)
{
    float r = abs(ca->r + (cb->r - ca->r) * t);
    float g = abs(ca->g + (cb->g - ca->g) * t);
    float b = abs(ca->b + (cb->b - ca->b) * t);

    return color4f(r, g, b, ca->a);
}
