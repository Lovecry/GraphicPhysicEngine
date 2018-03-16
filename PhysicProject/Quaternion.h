#pragma once

#include <math.h>
#include "Matrix.h"

class Quaternion
{

public:
	Quaternion();
	Quaternion(float, float, float, float);
	Quaternion(const Quaternion&);
	Quaternion& operator=(const Quaternion&);

	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator/=(float scalar);

	void Normalize();
	float Modulus() const;
	float GetValue(int i) const;

	Matrix<3, 3> ToMatrix() const;

private:
	float q[4];
};

Quaternion operator*(const Quaternion& first, const Quaternion& second);
Quaternion operator+(const Quaternion& first, const Quaternion& second);
Quaternion operator-(const Quaternion& first, const Quaternion& second);