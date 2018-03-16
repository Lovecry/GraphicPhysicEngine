#pragma once

#include <math.h>
#include <DirectXMath.h>

class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);

	inline float getX() const { return v.x; }
	inline float getY() const { return v.y; }
	inline float getZ() const { return v.z; }
	inline void SetX(float x) { v.x = x; }
	inline void SetY(float y) { v.y = y; }
	inline void SetZ(float z) { v.z = z; }

	void Set(float, float, float);

	Vector3& operator=(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);
	Vector3& operator/=(float scalar);
	Vector3& operator/=(const Vector3& other);

	//const float& operator[](int i)const { return v[i]; };
	const float& operator[](int i)const { 
		//assert(i>2);		
		switch (i){
		case 0:
			return v.x;
			break;
		case 1:
			return v.y;
			break;
		case 2:
			return v.z;
			break;
		}
	};
	float& operator[](int i){ 
		//assert(i > 2);
		switch (i){
		case 0:
			return v.x;
			break;
		case 1:
			return v.y;
			break;
		case 2:
			return v.z;
			break;
		}
	};

	float Modulus() const;
	float SqrMagnitude() const;
	void Normalize();

	DirectX::XMFLOAT3 convertToXMFloat3() const {	
		return v;
	};

private:
	DirectX::XMFLOAT3 v;
};

Vector3 operator+(const Vector3&, const Vector3&);
Vector3 operator-(const Vector3&, const Vector3&);
//Vector3 operator*(const Vector3&, const Vector3&);
Vector3 operator*(const Vector3&, float);
Vector3 operator/(const Vector3&, float);

namespace VectorOp
{
	float DistanceBetween(const Vector3& first, const Vector3& second);
	void VectorialProduct(const Vector3& first, const Vector3& second, Vector3& result);
	float DotProduct(const Vector3& first, const Vector3& second);

	static Vector3 Zero;
}