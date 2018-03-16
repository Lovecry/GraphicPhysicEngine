#include "Vector3.h"

Vector3::Vector3()
{
	v.x = 0.f;
	v.y = 0.f;
	v.z = 0.f;
}

Vector3::Vector3(float x, float y, float z)
{
	v.x = x;
	v.y = y;
	v.z = z;
}

Vector3::Vector3(const Vector3& other)
{
	v.x = other.getX();
	v.y = other.getY();
	v.z = other.getZ();
}

Vector3& Vector3::operator=(const Vector3& other)
{
	if (this != &other)
	{
		v.x = other.getX();
		v.y = other.getY();
		v.z = other.getZ();
	}
	return *this;
}
Vector3& Vector3::operator+=(const Vector3& other)
{
	v.x += other.getX();
	v.y += other.getY();
	v.z += other.getZ();
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	v.x -= other.getX();
	v.y -= other.getY();
	v.z -= other.getZ();
	return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
	v.x *= scalar;
	v.y *= scalar;
	v.z *= scalar;
	return *this;
}

Vector3& Vector3::operator/=(float scalar)
{
	v.x /= scalar;
	v.y /= scalar;
	v.z /= scalar;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3& other)
{
	v.x /= other.getX();
	v.y /= other.getY();
	v.z /= other.getZ();
	return *this;
}

Vector3 operator+(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result += second;
}

Vector3 operator*(const Vector3& vector, float scalar)
{
	return Vector3(vector.getX() * scalar, vector.getY()* scalar, vector.getZ() * scalar);
}

Vector3 operator/(const Vector3& vector, float scalar)
{
	return Vector3(vector.getX() / scalar, vector.getY() / scalar, vector.getZ() / scalar);
}

Vector3 operator-(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result -= second;
}

void Vector3::Set(float x, float y, float z)
{
	v.x = x;
	v.y = y;
	v.z = z;
}

void Vector3::Normalize()
{
	float mod = Modulus();
	if (mod > 0.000001f) {
		*this /= mod;
	}
}

float Vector3::Modulus() const
{
	return(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
};

float Vector3::SqrMagnitude() const
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
};

void VectorOp::VectorialProduct(const Vector3& first, const Vector3& second, Vector3& result)
{
	//float X = (p3[1] * s3[2]) - (p3[2] * s3[1]);
	//float Y = (p3[2] * s3[0]) - (p3[0] * s3[2]);
	//float Z = (p3[0] * s3[1]) - (p3[1] * s3[0]);
	float X = (first.getY() * second.getZ()) - (first.getZ() * second.getY());
	float Y = (first.getZ() * second.getX()) - (first.getX() * second.getZ());
	float Z = (first.getX() * second.getY()) - (first.getY() * second.getX());
	result.SetX(X);
	result.SetY(Y);
	result.SetZ(Z);
}

float VectorOp::DotProduct(const Vector3& first, const Vector3& second)
{
	return((first.getX() * second.getX()) + (first.getY() * second.getY()) + (first.getZ() * second.getZ()));
}

float VectorOp::DistanceBetween(const Vector3& first, const Vector3& second)
{
	return sqrt(pow(first.getX() + second.getX(), 2) + pow(first.getY() + second.getY(), 2) + pow(first.getZ() + second.getZ(), 2));
}