#pragma once
#include <GLCommon.h>
#include "cParticle.h"

namespace nPhysics
{
	class iParticleForceGenerator
	{
	public:
		virtual ~iParticleForceGenerator() {}
		// Overload, calculate an applied force for the particle,
		// then apply the force to the particle
		virtual void Update(cParticle* particle, float deltaTime) = 0;
	};
}