#pragma once
#include <Physics/Particle/cParticle.h>
namespace nProjectiles {
	class EnergyBall : public nPhysics::cParticle {

	public:
		virtual ~EnergyBall();
		EnergyBall(float mass, glm::vec3 position);


		void Integrate(float deltaTime);
	};
}