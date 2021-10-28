#pragma once
#include <GLCommon.h>
#include "iParticleForceGenerator.h"

namespace nPhysics
{
	class cParticleGravityGenerator : public iParticleForceGenerator
	{
	public:
		cParticleGravityGenerator(const glm::vec3& gravityAcceleration);

		cParticleGravityGenerator() = delete;
		cParticleGravityGenerator(cParticleGravityGenerator& other) = delete;
		cParticleGravityGenerator& operator=(cParticleGravityGenerator& other) = delete;

		virtual ~cParticleGravityGenerator();
		virtual void Update(cParticle* particle, float deltaTime);

	private:
		glm::vec3 mGravityAcceleration;
	};
}