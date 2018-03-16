#include "Quaternion.h"

Quaternion::Quaternion()
{
	q[0] = 1;
	q[1] = 0;
	q[2] = 0;
	q[3] = 0;
}

Quaternion::Quaternion(float a, float i, float j, float k)
{
	q[0] = a;
	q[1] = i;
	q[2] = j;
	q[3] = k;
};

Quaternion::Quaternion(const Quaternion& other)
{
	q[0] = other.GetValue(0);
	q[1] = other.GetValue(1);
	q[2] = other.GetValue(2);
	q[3] = other.GetValue(3);

};
Quaternion& Quaternion::operator=(const Quaternion& other)
{
	if (this != &other)
	{	
		q[0] = other.GetValue(0);
		q[1] = other.GetValue(1);
		q[2] = other.GetValue(2);
		q[3] = other.GetValue(3);
	}
	return *this;
};

Quaternion operator+(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result += second;
	return result;
};

Quaternion operator-(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result -= second;
	return result;
};

Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	q[0] += other.GetValue(0);
	q[1] += other.GetValue(1);
	q[2] += other.GetValue(2);
	q[3] += other.GetValue(3);
	return *this;
};

Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	q[0] -= other.GetValue(0);
	q[1] -= other.GetValue(1);
	q[2] -= other.GetValue(2);
	q[3] -= other.GetValue(3);
	return *this;
};

Quaternion& Quaternion::operator/=(float scalar)
{
	q[0] /= scalar;
	q[1] /= scalar;
	q[2] /= scalar;
	q[3] /= scalar;
	return *this;
};

float Quaternion::GetValue(int i) const
{
	return q[i];
};

Quaternion operator*(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result *= second;
	return result;
};

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	//	float S = p4[0] * s4[0] - p4[1] * s4[1] - p4[2] * s4[2] - p4[3] * s4[3];
	q[0] = GetValue(0) * other.GetValue(0) - GetValue(1) * other.GetValue(1) - GetValue(2) * other.GetValue(2) - GetValue(3) * other.GetValue(3);
	//	float X = p4[0] * s4[1] + p4[1] * s4[0] + p4[2] * s4[3] - p4[3] * s4[2]
	q[1] = GetValue(0) * other.GetValue(1) + GetValue(1) * other.GetValue(0) + GetValue(2) * other.GetValue(3) - GetValue(3) * other.GetValue(2);
	//	float Y = p4[0] * s4[2] - p4[1] * s4[3] + p4[2] * s4[0] + p4[3] * s4[1];
	q[2] = GetValue(0) * other.GetValue(2) - GetValue(1) * other.GetValue(3) + GetValue(2) * other.GetValue(0) + GetValue(3) * other.GetValue(1);
	//	float Z = p4[0] * s4[3] + p4[1] * s4[2] - p4[2] * s4[1] + p4[3] * s4[0];
	q[3] = GetValue(0) * other.GetValue(3) + GetValue(1) * other.GetValue(2) - GetValue(2) * other.GetValue(1) + GetValue(3) * other.GetValue(0);
	return *this;
};

float Quaternion::Modulus() const
{
	return(sqrt((GetValue(0) * GetValue(0)) + (GetValue(1) * GetValue(1)) + (GetValue(2) * GetValue(2)) + (GetValue(3) * GetValue(3))));
};

void Quaternion::Normalize()
{
	float a = Modulus();
	if (a > 0.000001f) {
		*this /= a;
	}
};

Matrix<3, 3> Quaternion::ToMatrix() const
{
	float X2 = GetValue(1) * GetValue(1);
	float Y2 = GetValue(2) * GetValue(2);
	float Z2 = GetValue(3) * GetValue(3);
	float XY = GetValue(1) * GetValue(2);
	float XZ = GetValue(1) * GetValue(3);
	float YZ = GetValue(2) * GetValue(3);
	float SX = GetValue(0) * GetValue(1);
	float SY = GetValue(0) * GetValue(2);
	float SZ = GetValue(0) * GetValue(3);
	Matrix<3, 3> result;

	result.SetElementAt(0, 1.0f - 2.0f * (Y2 + Z2));
	result.SetElementAt(1, 2.0f * (XY - SZ));
	result.SetElementAt(2, 2.0f * (XZ + SY));
	result.SetElementAt(3, 2.0f * (XY + SZ));
	result.SetElementAt(4, 1.0f - 2.0f * (Z2 + X2));
	result.SetElementAt(5, 2.0f * (YZ - SX));
	result.SetElementAt(6, 2.0f * (XZ - SY));
	result.SetElementAt(7, 2.0f * (YZ + SX));
	result.SetElementAt(8, 1.0f - 2.0f * (X2 + Y2));
	return result;
};