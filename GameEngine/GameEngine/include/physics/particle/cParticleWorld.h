#pragma once
#include "cParticle.h"
#include "cParticleForceRegistry.h"
#include <vector>

namespace nPhysics
{
	class cParticleWorld
	{
	private:
		std::vector<cParticle*> mParticles;
		cParticleForceRegistry* mForceRegistry;
	public:
		cParticleWorld();
		virtual ~cParticleWorld();

		bool AddParticle(cParticle* particle);
		bool RemoveParticle(cParticle* particle);
		inline std::vector<cParticle*> getParticles() {return mParticles;}

		void TimeStep(float deltaTime);

		void IntegrateParticles(float deltaTime);

		void InitInitialVariables(glm::mat3& axes, nPhysics::cParticle* particle);// These are defined in theMain.cpp


		cParticleForceRegistry* GetForceRegistry() const;
		
	};
}

