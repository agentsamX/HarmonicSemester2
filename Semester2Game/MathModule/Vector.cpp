#include "Vector.h"

vec2::vec2()
{
}

vec2::vec2(float _x, float _y)
{
	//sets x and y
	x = _x;
	y = _y;

}

void vec2::Subtract(vec2 v2)
{
	//subtracts v2 from this
	this->x -= v2.x;
	this->y -= v2.y;
}

void vec2::MultScalar(float s)
{
	//multiplies s into this
	this->x *= s;
	this->y *= s;

}

void vec2::DivScalar(float s)
{
	//divides this by s
	this->x /= s;
	this->y /= s;
}

float vec2::Dot(vec2 v2)
{
	return float (x*v2.x+y*v2.y);
}

float vec2::GetMagnitude()
{
	return float(sqrt((x*x)+(y+y)));
}

float vec2::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();

	return magnitude * magnitude;
}

vec2 vec2::Normalize()
{
	vec2 normalized = *this / GetMagnitude();

	return normalized;
}

vec2 vec2::Project(vec2 b)
{
	vec2 a = *this;

	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();
	return (b*(numerator/denominator));
}

float vec2::operator[](int i)
{
	//indexes the variable at i
	//* 0 = x
	//* 1 = y
	return *hold[i];
}

vec2 vec2::operator-()
{
	return vec2(-x,-y);
}

vec2 vec2::operator+(vec2 v1)
{
	return vec2(this->x + v1.x, this->y+v1.y);
}

vec2 vec2::operator-(vec2 v1)
{
	return vec2(this->x - v1.x, this->y - v1.y);
}

vec2 vec2::operator*(float f)
{
	return vec2(this->x*f,this->y*f);
}

vec2 vec2::operator/(float s)
{
	return vec2(this->x/s,this->y/s);
}

vec3::vec3()
{
}

vec3::vec3(float _x, float _y, float _z)
{
	//sets x y z
	x = _x;
	y = _y;
	z = _z;
}

void vec3::Subtract(vec3 v3)
{
	this->x -= v3.x;
	this->y -= v3.y;
	this->z -= v3.z;
}

void vec3::MultScalar(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
}

void vec3::DivideScalar(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
}

float vec3::Dot(vec3 v3)
{
	return float(x * v3.x + y * v3.y+z*v3.z);
}

vec3 vec3::Normalize()
{
	vec3 normalized = *this / GetMagnitude();

	return normalized;
}

float vec3::GetMagnitude()
{
	return float(sqrt((x*x)+(y*y)+(z*z)));
}

float vec3::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();

	return magnitude * magnitude;
}

vec3 vec3::Project(vec3 b)
{
	vec3 a = *this;

	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();
	return (b * (numerator / denominator));
}

float vec3::operator[](int i)
{
	//* 0=x
	//* 1=y
	//* 2=z
	return *hold[i];
}

vec3 vec3::operator-()
{
	return vec3(-x,-y,-z);
}

vec3 vec3::operator+(vec3 v2)
{
	return vec3(this->x + v2.x, this->y + v2.y,this->z +v2.z);
}

vec3 vec3::operator-(vec3 v2)
{
	return vec3(this->x - v2.x, this->y - v2.y, this->z - v2.z);
}

vec3 vec3::operator*(float f)
{
	return vec3(this->x *f, this->y *f, this->z *f);
}

vec3 vec3::operator/(float f)
{
	return vec3(this->x /f, this->y /f,this->z /f);
}

vec4::vec4()
{
}

vec4::vec4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;

}

void vec4::Subtract(vec4 v4)
{
	this->x -= v4.x;
	this->y -= v4.y;
	this->z -= v4.z;
	this->w -= v4.w;
}

void vec4::MultScalar(float s)
{
	this->x *= s;
	this->y *= s;
	this->z *= s;
	this->w *= s;
}

void vec4::DivideScalar(float s)
{
	this->x /= s;
	this->y /= s;
	this->z /= s;
	this->w /= s;
}

float vec4::Dot(vec4 v4)
{
	return float(x * v4.x + y * v4.y + z * v4.z+w*v4.w);
}

vec4 vec4::Normalize()
{
	vec4 normalized = *this / GetMagnitude();

	return normalized;
}

float vec4::GetMagnitudeSquared()
{
	float magnitude = GetMagnitude();

	return magnitude * magnitude;
}

float vec4::GetMagnitude()
{
	return float (sqrt((x * x) + (y * y) + (z * z)+(w * w)));
}

vec4 vec4::Project(vec4 b)
{
	vec4 a = *this;

	float numerator = a.Dot(b);
	float denominator = b.GetMagnitudeSquared();
	return (b * (numerator / denominator));
}

float vec4::operator[](int i)
{
	//* 0=x
	//* 1=y
	//* 2=z
	//* 3=w
	return *hold[i];
}
vec4 vec4::operator+(vec4 v4)
{
	return vec4(this->x + v4.x, this->y + v4.y, this->z + v4.z, this->w + v4.w);
}
vec4 vec4::operator-(vec4 v4)
{
	return vec4(this->x - v4.x, this->y - v4.y, this->z - v4.z,this->w-v4.w);
}

vec4 vec4::operator*(float f)
{
	return vec4(this->x * f, this->y * f, this->z * f,this->w*f);
}

vec4 vec4::operator/(float f)
{
	return vec4(this->x / f, this->y / f, this->z / f, this->w / f);
}
