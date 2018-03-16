#pragma once

#include "Collision.h"
#include "RigidBody.h"
#include "Vector3.h"
#include "Matrix.h"
#include <vector>

class RigidBody;
class Collision;
class CollisionDetector
{
public:
	CollisionDetector();

	//collision between rigidbody and plane
	bool CollisionDetectionSpherePlane(RigidBody& rigidbody0);
	int CollisionDetectionCubePlane(RigidBody& rigidbody0);
	void ResolveCollisionSpherePlane(RigidBody& rigidbody0, float k, float l);
	void ResolveCollisionCubePlane(RigidBody& rigidbody0, float k, float l, int nCollisions);

	bool CollisionDetectionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1);
	bool CollisionDetectionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1);
	bool CollisionDetectionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1);

	void ResolveCollisionSphereSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l);
	void ResolveCollisionBoxBox(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l);
	void ResolveCollisionBoxSphere(RigidBody& rigidbody0, RigidBody& rigidbody1, float k, float l);

private:
	~CollisionDetector();
	CollisionDetector(const CollisionDetector& other);
	CollisionDetector& operator=(const CollisionDetector& other);

	Collision* m_Collision;
	std::vector<Collision*> m_aCollision;
};