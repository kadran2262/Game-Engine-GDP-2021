#pragma once
#include <Physics/Particle/cParticleWorld.h>
#include <Physics/Particle/particle_force_generators.h>
namespace nProjectiles {
	struct FireWorkType{
		int type;
	};
	class Firework : public nPhysics::cParticle {
		

	private:
		float mDuration;
		int mType;
	public:
		Firework(float mass, const glm::vec3& position);
		float getDuration();

		inline void SetFireWorkType(int type) { mType = type; }
		

		inline void setDuration(float duration) { mDuration = duration; }
		void Explode(nPhysics::cParticleWorld* world, nPhysics::cParticleGravityGenerator* gravityGenerator);
	};

}