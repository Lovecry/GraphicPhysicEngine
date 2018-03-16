#pragma once

#include "Vector3.h"
#include "RigidBody.h"
#include "Physic.h"

class RigidBody;
class Collision
{
public:
	Collision();
	~Collision();
	
	void ApplyCollision(RigidBody* rigidbodyfirst, RigidBody* rigidbodysecond, float K, float L);

	void SetDeformation(float value){ m_fDeformation = value; };
	void SetInpactPoint(Vector3& v){ m_vInpactPoint = v; };
	void SetNormalVector(Vector3& v){ m_vNormalVector = v; };
	void SetInpactVelocity(Vector3& v){ m_vInpactVelocity = v; };

	float GetDeformation() const{ return m_fDeformation; };
	Vector3 GetInpactPoint() const{ return m_vInpactPoint; };
	Vector3 GetNormalVector() const{ return m_vNormalVector; };
	Vector3 GetInpactVelocity() const{ return m_vInpactVelocity; };

private:
	float m_fDeformation;
	Vector3 m_vInpactPoint;
	Vector3 m_vNormalVector;
	Vector3 m_vInpactVelocity;
};