
#include <physics/projectiles/Bullet.h>

namespace nProjectiles {
	

	Bullet::Bullet(float mass, glm::vec3 position) : cParticle(mass, position)
	{
		mSpeed = 40;
		m_Radius = .25f;
		m_ModelColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		if (mass <= 0.f)
		{
			mInverseMass = 0.f;
		}
		else
		{
			mInverseMass = 1.f / mass;
		}
	}

	Bullet::~Bullet()
	{

	}

	void Bullet::Integrate(float deltaTime)
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
