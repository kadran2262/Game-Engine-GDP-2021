
#include <physics/projectiles/Laser.h>
namespace nProjectiles {


	Laser::Laser(float mass, glm::vec3 position): cParticle(mass, position) {

		if (mass <= 0.f)
		{
			mInverseMass = 0.f;
			
		}
		else
		{
			mInverseMass = 1.f / mass;
			
		}
	}


	Laser::~Laser()
	{

	}

	void Laser::Integrate(float deltaTime)
	{
		if (mInverseMass == 0.f)
		{
			return; // static things don't move!
		}

		mPosition += mVelocity * deltaTime;
		// F*(1/m) = a
		mVelocity += (mAcceleration + mAppliedForce * mInverseMass) * deltaTime;

		// apply damping
		mVelocity *= glm::pow(mDamping, deltaTime);

		// clear applied forces
		ClearAppliedForces();
	}
}
