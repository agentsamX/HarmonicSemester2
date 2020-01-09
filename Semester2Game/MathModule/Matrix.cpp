#include "Matrix.h"

mat3::mat3(vec3 _row1, vec3 _row2, vec3 _row3)
{
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
}

mat3::mat3(mat4 m)
{
	this->row1 = vec3(m.row1.x, m.row1.y, m.row1.z);
	this->row2 = vec3(m.row2.x, m.row2.y, m.row2.z);
	this->row3 = vec3(m.row3.x, m.row3.y, m.row3.z);
}

void mat3::Add(mat3 m)
{
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
	this->row3 = this->row3 + m.row3;
}

void mat3::Subtract(mat3 m)
{
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
	this->row3 = this->row3 - m.row3;
}

void mat3::Print()
{
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << " ]\n";
	std::cout << "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << " ]\n";
}

mat3 mat3::Transpose()
{
	mat3 temp;
	temp.row1 = vec3(row1.x, row2.x, row3.x);
	temp.row2 = vec3(row1.y, row2.y, row3.y);
	temp.row3 = vec3(row1.z, row2.z, row3.z);
	return temp;
}

float mat3::Determinant()
{
	float temp = (row1.x * row2.y*row3.z)+(row1.y*row2.z*row3.x)+(row1.z*row2.x*row3.y) - (row1.z * row2.y*row3.x)-(row1.y*row2.x*row3.z)-(row1.x*row2.z*row3.y);
	return temp;
}

mat3 mat3::Inverse()
{
	float oneOverDet = 1.f / Determinant();

	mat3 temp = Adjugate();

	temp = temp * oneOverDet;

	return temp;
}

mat3 mat3::Adjugate()
{

	vec3 rowtem1 = (vec3(+mat2(vec2(row2.y, row2.z), vec2(row3.y, row3.z)).Determinant(), -mat2(vec2(row2.x, row2.z), vec2(row3.x, row3.z)).Determinant(), +mat2(vec2(row2.x, row2.y), vec2(row3.x, row3.y)).Determinant()));
	vec3 rowtem2 = (vec3(-mat2(vec2(row1.y, row1.z), vec2(row3.y, row3.z)).Determinant(), +mat2(vec2(row1.x, row1.z), vec2(row3.x, row3.z)).Determinant(), -mat2(vec2(row1.x, row1.y), vec2(row3.x, row3.y)).Determinant()));
	vec3 rowtem3 = (vec3(+mat2(vec2(row1.y, row1.z), vec2(row2.y, row2.z)).Determinant(), -mat2(vec2(row1.x, row1.z), vec2(row2.x, row2.z)).Determinant(), +mat2(vec2(row1.x, row1.y), vec2(row2.x, row2.y)).Determinant()));
	mat3 temp = mat3(rowtem1, rowtem2, rowtem3);
	return temp.Transpose();
}

mat3 mat3::Transpose(mat3 R)
{
	mat3 temp;
	temp.row1 = vec3(R.row1.x, R.row2.x, R.row3.x);
	temp.row2 = vec3(R.row1.y, R.row2.y, R.row3.y);
	temp.row3 = vec3(R.row1.z, R.row2.z, R.row3.z);
	return temp;
}

mat3 mat3::operator-()
{
	return mat3(-row1,-row2,-row3);
}

mat3 mat3::operator-(mat3 m)
{
	return mat3(this->row1 - m.row1, this->row2 - m.row2,this->row3-m.row3);
}

mat3 mat3::operator+(mat3 m)
{
	return mat3(this->row1 + m.row1, this->row2 +m.row2, this->row3 + m.row3);
}

mat3 mat3::operator*(float f)
{
	return mat3(this->row1 * f, this->row2 * f,this->row3*f);
}

mat3 mat3::operator*(mat3 m)
{
	vec3 mCol1 = vec3(m.row1.x, m.row2.x, m.row3.x);
	vec3 mCol2 = vec3(m.row1.y, m.row2.y, m.row3.y);
	vec3 mCol3 = vec3(m.row1.z, m.row2.z, m.row3.z);

	mat3 temp = mat3(
		vec3(row1.Dot(mCol1), row1.Dot(mCol2), row1.Dot(mCol3)),
		vec3(row2.Dot(mCol1), row2.Dot(mCol2), row2.Dot(mCol3)),
		vec3(row3.Dot(mCol1), row3.Dot(mCol2), row3.Dot(mCol3))

	);
	return temp;
}

vec3 mat3::operator[](int i)
{
	//indexes variable at i
	//* 0 = row1
	//* 1 = row2
	//* 2 = row3
	return *hold[i];
}

vec3 mat3::operator*(vec3 vec)
{
	vec3 temp;
	temp = vec3(
		row1.x * vec.x + row1.y + vec.y + row1.z * vec.z,
		row2.x * vec.x + row2.y + vec.y + row2.z * vec.z,
		row3.x * vec.x + row3.y + vec.y + row3.z * vec.z
	);
	return temp;
}

mat4::mat4(vec4 _row1, vec4 _row2, vec4 _row3, vec4 _row4)
{
	row1 = _row1;
	row2 = _row2;
	row3 = _row3;
	row4 = _row4;
}

mat4::mat4(mat3 rot, vec3 trans)
{
	row1 = vec4(rot.row1.x, rot.row1.y, rot.row1.z, trans.x);
	row2 = vec4(rot.row2.x, rot.row2.y, rot.row2.z, trans.y);
	row3 = vec4(rot.row3.x, rot.row3.y, rot.row3.z, trans.z);
	row4 = vec4(0.f, 0.f, 0.f, 1.f);

}

void mat4::Add(mat4 m)
{
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
	this->row3 = this->row3 + m.row3;
}

void mat4::Subtract(mat4 m)
{
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
	this->row3 = this->row3 - m.row3;
}

void mat4::Print()
{
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << ", " << this->row1.z << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << ", " << this->row2.z << " ]\n";
	std::cout << "[ " << this->row3.x << ", " << this->row3.y << ", " << this->row3.z << " ]\n";
	std::cout << "[ " << this->row4.x << ", " << this->row4.y << ", " << this->row4.z << " ]\n";
}

mat4 mat4::Transpose()
{
	mat4 temp;
	temp.row1 = vec4(row1.x, row2.x, row3.x,row4.x);
	temp.row2 = vec4(row1.y, row2.y, row3.y, row4.y);
	temp.row3 = vec4(row1.z, row2.z, row3.z, row4.z);
	temp.row3 = vec4(row1.w, row2.w, row3.w, row4.w);
	return temp;
}

float mat4::Determinant()
{
	vec4 row1 = Adjugate().Transpose().row1;
	vec4 rowOr = this->row1;
	return rowOr.x * row1.x + rowOr.y + row1.y + rowOr.z * row1.z + rowOr.w * row1.w;
}

mat4 mat4::Inverse()
{
	float oneOverDet = 1.f / Determinant();

	mat4 temp = Adjugate();

	temp = temp * oneOverDet;

	return temp;
}

mat4 mat4::Adjugate()
{
	vec4 rowtem1 = (vec4(+mat3(vec3(row2.y, row2.z,row2.w), vec3(row3.y, row3.z,row3.w), vec3(row4.y,row4.z,row4.w)).Determinant(),
		-mat3(vec3(row2.x, row2.z, row2.w), vec3(row3.x, row3.z, row3.w), vec3(row4.x, row4.z, row4.w)).Determinant(),
		+mat3(vec3(row2.x, row2.y, row2.w), vec3(row3.x, row3.y, row3.w), vec3(row4.x, row4.y, row4.w)).Determinant(),
		-mat3(vec3(row2.x, row2.y, row2.z), vec3(row3.x, row3.y, row3.z), vec3(row4.x, row4.y, row4.z)).Determinant()));
	vec4 rowtem2 = (vec4(-mat3(vec3(row1.y, row1.z, row1.w), vec3(row3.y, row3.z, row4.w), vec3(row4.y, row4.z, row4.w)).Determinant(),
		+mat3(vec3(row1.x, row1.z, row1.w), vec3(row3.x, row3.z, row4.w), vec3(row4.x, row4.z, row4.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.w), vec3(row3.x, row3.y, row4.w), vec3(row4.x, row4.y, row4.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.z), vec3(row3.x, row3.y, row4.z), vec3(row4.x, row4.y, row4.z)).Determinant()));
	vec4 rowtem3 = (vec4(-mat3(vec3(row1.y, row1.z, row1.w), vec3(row2.y, row2.z, row2.w), vec3(row4.y, row4.z, row4.w)).Determinant(),
		+mat3(vec3(row1.x, row1.z, row1.w), vec3(row2.x, row2.z, row2.w), vec3(row4.x, row4.z, row4.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.w), vec3(row2.x, row2.y, row2.w), vec3(row4.x, row4.y, row4.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.z), vec3(row2.x, row2.y, row2.z), vec3(row4.x, row4.y, row4.z)).Determinant()));
	vec4 rowtem4 = (vec4(-mat3(vec3(row1.y, row1.z, row1.w), vec3(row2.y, row2.z, row2.w), vec3(row3.y, row3.z, row3.w)).Determinant(),
		+mat3(vec3(row1.x, row1.z, row1.w), vec3(row2.x, row2.z, row2.w), vec3(row3.x, row3.z, row3.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.w), vec3(row2.x, row2.y, row2.w), vec3(row3.x, row3.y, row3.w)).Determinant(),
		-mat3(vec3(row1.x, row1.y, row1.z), vec3(row2.x, row2.y, row2.z), vec3(row3.x, row3.y, row3.z)).Determinant()));
	mat4 temp = (mat4(rowtem1, rowtem2, rowtem3, rowtem4));
	return temp.Transpose();

}

mat4 mat4::FastInverse(mat4 mat)
{
	mat3 rotation = mat3(mat);

	vec3 translation = Translation(mat);

	rotation = mat3::Transpose(rotation);

	translation = -rotation * translation;

	return mat4(rotation, translation);
}

vec3 mat4::Translation(mat4 mat)
{
	return vec3(mat.row1.z,mat.row2.z,mat.row3.z);
}

mat4 mat4::operator-(mat4 m)
{
	return mat4(this->row1 - m.row1, this->row2 - m.row2, this->row3 - m.row3, this->row4-m.row4);
}

mat4 mat4::operator+(mat4 m)
{
	return mat4(this->row1 + m.row1, this->row2 + m.row2, this->row3 + m.row3, this->row4 + m.row4);
}

mat4 mat4::operator*(float f)
{
	return mat4(this->row1 * f, this->row2 * f, this->row3 * f, this->row4 * f);
}

mat4 mat4::operator*(mat4 m)
{
	vec4 mCol1 = vec4(m.row1.x, m.row2.x, m.row3.x, m.row4.x);
	vec4 mCol2 = vec4(m.row1.y, m.row2.y, m.row3.y, m.row4.y);
	vec4 mCol3 = vec4(m.row1.z, m.row2.z, m.row3.z, m.row4.z);
	vec4 mCol4 = vec4(m.row1.w, m.row2.w, m.row3.w, m.row4.w);

	mat4 temp = mat4(
		vec4(row1.Dot(mCol1), row1.Dot(mCol2), row1.Dot(mCol3), row1.Dot(mCol4)),
		vec4(row2.Dot(mCol1), row2.Dot(mCol2), row2.Dot(mCol3), row2.Dot(mCol4)),
		vec4(row3.Dot(mCol1), row3.Dot(mCol2), row3.Dot(mCol3), row3.Dot(mCol4)),
		vec4(row4.Dot(mCol1), row4.Dot(mCol2), row4.Dot(mCol3), row4.Dot(mCol4))

	);
	return temp;
}

vec4 mat4::operator*(vec4 vec)
{
	vec4 temp;
	temp = vec4(
		row1.x * vec.x + row1.y + vec.y + row1.z * vec.z + row1.w * vec.w,
		row2.x * vec.x + row2.y + vec.y + row2.z * vec.z + row2.w * vec.w,
		row3.x * vec.x + row3.y + vec.y + row3.z * vec.z + row3.w * vec.w,
		row4.x * vec.x + row4.y + vec.y + row4.z * vec.z + row4.w * vec.w
	);
	return temp;
}

vec4 mat4::operator[](int i)
{
	//indexes variable at i
	//* 0 = row1
	//* 1 = row2
	//* 2 = row3
	//* 3 = row4
	return *hold[i];
}

mat2::mat2(vec2 _row1, vec2 _row2)
{
	//sets row1 and row2
	row1 = _row1;
	row2 = _row2;
}

void mat2::Add(mat2 m)
{
	this->row1 = this->row1 + m.row1;
	this->row2 = this->row2 + m.row2;
}

void mat2::Subtract(mat2 m)
{
	this->row1 = this->row1 - m.row1;
	this->row2 = this->row2 - m.row2;
}

void mat2::Print()
{
	std::cout << "[ " << this->row1.x << ", " << this->row1.y << " ]\n";
	std::cout << "[ " << this->row2.x << ", " << this->row2.y << " ]\n";
}

mat2 mat2::Transpose()
{
	mat2 temp;
	temp.row1 = vec2(row1.x, row2.x);
	temp.row2 = vec2(row1.y, row2.y);
	return temp;
}

float mat2::Determinant()
{
	float temp = (row1.x * row2.y) - (row1.y * row2.x);
	return temp;
}

mat2 mat2::Inverse()
{
	float oneOverDet = 1.f / Determinant();


	mat2 temp = mat2(
		vec2(row2.y, -row1.y),
		vec2(-row2.x, row2.x)
	);

	temp = temp * oneOverDet;

	return temp;
}

mat2 mat2::operator+(mat2 m)
{
	return mat2(this->row1+m.row1,this->row2+m.row2);
}

mat2 mat2::operator-(mat2 m)
{
	return mat2(this->row1 - m.row1, this->row2 - m.row2);
}

mat2 mat2::operator*(mat2 m)
{
	vec2 mCol1 = vec2(m.row1.x, m.row2.x);
	vec2 mCol2 = vec2(m.row1.y, m.row2.y);

	mat2 temp = mat2(
		vec2(row1.Dot(mCol1), row1.Dot(mCol2)),
		vec2(row2.Dot(mCol1), row2.Dot(mCol2))
	);
	return temp;
}

vec2 mat2::operator*(vec2 v)
{
	vec2 temp = vec2(
		row1.x * v.x + row1.y * v.y,
		row2.x * v.x + row2.y * v.y
	);
	return temp;
}

mat2 mat2::operator*(float f)
{
	return mat2(this->row1*f,this->row2 *f);
}

vec2 mat2::operator[](int i)
{
	//indexes variable at i
	//* 0 = row1
	//* 1 = row2
	return *hold[i];
}
