
#include <physics/projectiles/EnergyBall.h>

namespace nProjectiles {


	EnergyBall::EnergyBall(float mass, glm::vec3 position): cParticle(mass, position) {

		

		if (mass <= 0.f)
		{
			mInverseMass = 0.f;
			
		}
		else
		{
			mInverseMass = 1.f / mass;
			
		}
	}


	EnergyBall::~EnergyBall()
	{

	}

	void EnergyBall::Integrate(float deltaTime)
	{
		if (mInverseMass == 0.f)
		{
			return; // static things don't move!
		}

		mPosition += mVelocity * deltaTime;
		// F*(1/m) = a
		mVelocity += (mAcceleration) * deltaTime;

		// apply damping
		mVelocity *= glm::pow(mDamping, deltaTime);

		// clear applied forces
		ClearAppliedForces();
	}
}
