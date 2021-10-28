
#include <physics/projectiles/CannonBall.h>

namespace nProjectiles {


	CannonBall::CannonBall(float mass, glm::vec3 position): cParticle(mass, position) {
		mSpeed = 20;
		m_Radius = 1.f;
		m_ModelColour = glm::vec4(.5f, .5f, .5f, 1.f);
		if (mass <= 0.f)
		{
			mInverseMass = 0.f;
			
		}
		else
		{
			mInverseMass = 1.f / mass;
			
		}
	}


	CannonBall::~CannonBall()
	{

	}

	void CannonBall::Integrate(float deltaTime)
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
