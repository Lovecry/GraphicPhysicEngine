#pragma once

#include "Vector3.h"

namespace Pns
{

	class Forces
	{
	public:
		static Vector3 SphereInertia(float mass, float radius);
		static Vector3 CubeInertia(float mass, float width, float height, float depth);
	};
}