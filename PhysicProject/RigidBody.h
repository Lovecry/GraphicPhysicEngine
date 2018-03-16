#pragma once

#include "Physic.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"

template<int row, int col>
class Matrix;

class RigidBody
{

public:
	RigidBody(const Vector3& pos, int id, float mass, const Vector3& inertia);
	RigidBody(const RigidBody& other);
	~RigidBody();

	void UpdateMovement(float DeltaTime);
	void ApplyForce(const Vector3& force, const Vector3& pointOfApplication);

	void SetForceSum(Vector3& v){ m_vForceSum = v; };
	void SetMomentumSum(Vector3& v){ m_vMomentumSum = v; };
	void SetPosition(const Vector3& v){ m_vPosition = v; };
	void SetVelocity(const Vector3& v){ m_vVelocity = v; };	
	const Matrix<3, 3>& GetRotationMatrix() const{ return m_mRotationMatrix; };
	const Quaternion& GetRotationQuaternion() const{ return m_qRotation; };
	const Vector3& GetPosition() const{ return m_vPosition; };
	Vector3 GetVelocity() const{ return m_vVelocity; };
	Vector3 GetAngularVelocity() const{ return m_vAngularVelocity; }

	void SetColliderType(int collidertype){ m_iColliderType = collidertype; };
	int GetColliderType() const{ return m_iColliderType; };
	int GetID() const{ return m_iID; };

	void SetK(float value) { m_fK = value; };
	float GetK() const { return m_fK; };
	void SetL(float value) { m_fL = value; };
	float GetL() const { return m_fL; };
	float GetMass() const{ return m_fMass; };

	void SetRadius(float value){ radius = value; };
	float GetRadius() const{ return radius; };

	void SetSemiX(float value) { m_fSemiX = value; };
	float GetSemiX() const { return m_fSemiX; };
	void SetSemiY(float value) { m_fSemiY = value; };
	float GetSemiY() const { return m_fSemiY; };
	void SetSemiZ(float value) { m_fSemiZ = value; };
	float GetSemiZ() const { return m_fSemiZ; };
	void SetVerteces();
	
	//values of a cube
	Vector3 m_vVerteces[8];

private:
	float m_fK;			//costante elastica
	float m_fL;			//costante viscosa
	float m_fMass;
	Vector3 m_vPosition;
	Vector3 m_vVelocity;
	Vector3 m_vInitialVelocity;
	Vector3 m_vInertia;
	Vector3 m_vAngularVelocity;
	Vector3 m_vQuantityOfMotion;
	Vector3 m_vAngularMomentum;
	Vector3 m_vForceSum;
	Vector3 m_vMomentumSum;
	Quaternion m_qRotation;
	Matrix<3, 3> m_mRotationMatrix;
	int m_iColliderType;
	int m_iID;

	//element of a type of shape
	//set radius if it is a sphere
	float radius;
	//other values if it is a cube
	float m_fSemiX;
	float m_fSemiY;
	float m_fSemiZ;
};