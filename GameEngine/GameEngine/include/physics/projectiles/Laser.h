#pragma once
#include <Physics/Particle/cParticle.h>

namespace nProjectiles {
	class Laser : public nPhysics::cParticle {

	public:
		virtual ~Laser();
		Laser(float mass, glm::vec3 position);


		void Integrate(float deltaTime);
	};
}