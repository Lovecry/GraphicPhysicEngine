#include "Collision.h"

Collision::Collision(){
}

Collision::~Collision()
{
}

void Collision::ApplyCollision(RigidBody* rigidbodyfirst, RigidBody* rigidbodysecond, float K, float L)
{
	float force;
	float vn;
	float modVtang;
	Vector3 Vtang, Ftang, Fnorm;

	vn = VectorOp::DotProduct(m_vInpactVelocity, m_vNormalVector);
	Vtang = m_vNormalVector * vn;
	Vtang = m_vInpactVelocity - Vtang;

	force = (K * m_fDeformation) + (L * vn);
	if (force < 0)
	{
		force = 0;
	}
	Fnorm = m_vNormalVector * force;

	force *= Physic::m_fm;							// forza attrito (modulo)
	modVtang = Vtang.Modulus();
	Ftang = Vtang * force;

	if (modVtang > 9.8f * Physic::mk_fDeltaTime)
	{
		Ftang /= modVtang;
	}
	else
	{
		Ftang /= (9.8f * Physic::mk_fDeltaTime);
	}

	Fnorm += Ftang;	// ora Fnorm e' la F totale

	if (rigidbodyfirst != NULL)
	{
		rigidbodyfirst->ApplyForce(Fnorm, m_vInpactPoint);
	}
	if (rigidbodysecond != NULL)
	{
		rigidbodysecond->ApplyForce(Fnorm * -1.0f, m_vInpactPoint);
	}
}