#include "Physic.h"

const float Physic::mk_fDeltaTime = 0.025f;
const Vector3 Physic::mk_vGravity = Vector3(0.0f, -9.8f, 0.0f);
const float Physic::m_fm = 0.2f;

Physic::Physic()
{
	m_CollisionDetector = new CollisionDetector();
}

Physic::~Physic()
{
	unsigned int i;

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		delete m_RigidBodyList[i];
	}
	m_RigidBodyList.clear();
	m_RigidBodyID.clear();
}

void Physic::ComputePhysic()
{
	unsigned int i, j;

	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		m_RigidBodyList[i]->SetForceSum(Physic::mk_vGravity * m_RigidBodyList[i]->GetMass());
	}


	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		if (m_RigidBodyList.at(i)->GetColliderType() == 0)
		{
			//if collision was between SPHERE-PLANE
			if (m_CollisionDetector->CollisionDetectionSpherePlane(*m_RigidBodyList.at(i)))
			{
				m_CollisionDetector->ResolveCollisionSpherePlane(
					*m_RigidBodyList.at(i),
					m_RigidBodyList.at(i)->GetK(),
					m_RigidBodyList.at(i)->GetL()
					);
			}
		}
		else
		{
			//if collision was between CUBE-PLANE
			int numCollisions = m_CollisionDetector->CollisionDetectionCubePlane(*m_RigidBodyList.at(i));
			if (numCollisions > 0)
			{
				m_CollisionDetector->ResolveCollisionCubePlane(
					*m_RigidBodyList.at(i),
					m_RigidBodyList.at(i)->GetK(),
					m_RigidBodyList.at(i)->GetL(),
					numCollisions);
			}
		}
		

		//second loop not check a rigidbody with itself and previous rigidbody (double check)
		for (j = i + 1; j < m_RigidBodyList.size(); ++j)
		{
			//if collision was between SPHERE-SPHERE
			if ((m_RigidBodyList.at(i)->GetColliderType() == 0) && (m_RigidBodyList.at(j)->GetColliderType() == 0))
			{
				if (m_CollisionDetector->CollisionDetectionSphereSphere(*m_RigidBodyList.at(i), *m_RigidBodyList.at(j)))
				{
					m_CollisionDetector->ResolveCollisionSphereSphere(
						*m_RigidBodyList.at(i),
						*m_RigidBodyList.at(j),
						m_RigidBodyList.at(i)->GetK(),
						m_RigidBodyList.at(i)->GetL());
				}
			}
			//if collision was between BOX-BOX
			if ((m_RigidBodyList.at(i)->GetColliderType() == 1) && (m_RigidBodyList.at(j)->GetColliderType() == 1))
			{
				if (m_CollisionDetector->CollisionDetectionBoxBox(*m_RigidBodyList.at(i), *m_RigidBodyList.at(j)))
				{
					m_CollisionDetector->ResolveCollisionBoxBox(
						*m_RigidBodyList.at(i),
						*m_RigidBodyList.at(j),
						m_RigidBodyList.at(j)->GetK(),
						m_RigidBodyList.at(j)->GetL());
				}
			}
			//if collision was between BOX-SPHERE
			if ((m_RigidBodyList.at(i)->GetColliderType() == 1) && (m_RigidBodyList.at(j)->GetColliderType() == 0))
			{
				if (m_CollisionDetector->CollisionDetectionBoxSphere(*m_RigidBodyList.at(i), *m_RigidBodyList.at(j)))
				{
					m_CollisionDetector->ResolveCollisionBoxSphere(
						*m_RigidBodyList.at(i),
						*m_RigidBodyList.at(j),
						m_RigidBodyList.at(j)->GetK(),
						m_RigidBodyList.at(j)->GetL());
				}
			}
			//if collision was between SPHERE-BOX
			if ((m_RigidBodyList.at(i)->GetColliderType() == 0) && (m_RigidBodyList.at(j)->GetColliderType() == 1))
			{
				if (m_CollisionDetector->CollisionDetectionBoxSphere(*m_RigidBodyList.at(j), *m_RigidBodyList.at(i)))
				{
					m_CollisionDetector->ResolveCollisionBoxSphere(
						*m_RigidBodyList.at(j),
						*m_RigidBodyList.at(i),
						m_RigidBodyList.at(i)->GetK(),
						m_RigidBodyList.at(i)->GetL());
				}
			}
		}
	}
	for (i = 0; i < m_RigidBodyList.size(); ++i)
	{
		m_RigidBodyList[i]->UpdateMovement(Physic::mk_fDeltaTime);
		m_RigidBodyList[i]->SetForceSum(VectorOp::Zero);
		m_RigidBodyList[i]->SetMomentumSum(VectorOp::Zero);
	}
}

void Physic::AddRigidBody(RigidBody& rigidbody, int id)
{
	m_RigidBodyID.push_back(id);
	m_RigidBodyList.push_back(&rigidbody);
}

void Physic::ApplyForce(int id, const Vector3& force, const Vector3& pointOfApplication)
{
	bool found = false;
	unsigned int i = 0;

	for (; i < m_RigidBodyID.size() && !found; ++i)
	{
		found = m_RigidBodyID[i] == id;
	}
	if (found)
	{
		m_RigidBodyList[i]->ApplyForce(force, pointOfApplication);
	}
}

//MAYBE NON SENSE
void Physic::DeleteRigidBody(int id)
{
	bool found = false;
	unsigned int i = 0;

	for (; i < m_RigidBodyID.size() && !found; ++i)
	{
		found = m_RigidBodyID[i] == id;
	}

	if (found)
	{
		//TO DO
	}
}