#include <physics/particle/cParticle.h>

namespace nPhysics
{

	cParticle::cParticle(float mass, const glm::vec3& position)
		: mPosition(position)
		, mVelocity(0.f)
		, mAcceleration(0.f)
		, mDamping(0.995f)
		, mAppliedForce(0.f)
		, mDuration(getRandom(1, 3))
		, mSpeed(0.f)
	{
		if (mass <= 0.f)
		{
			mInverseMass = 0.f;
		}
		else
		{
			mInverseMass = 1.f / mass;
		}
	}
	cParticle::~cParticle()
	{

	}
	float cParticle::GetRadius()
	{
		return 0.0f;
	}
	glm::vec4 cParticle::GetColour()
	{
		return glm::vec4();
	}
	void cParticle::SetDefaultVars()
	{
		glm::mat3 axes;
		axes = orthonormalBasis(getRandomXVector(), getRandomZVector());
		// because our "sphere" has a radius of 1
		glm::vec3 position(0.0, 1.1f, 0.0);
		glm::vec3 velocity = (axes[0] * getRandom(-2.f, 2.f)) + (axes[1] * 5.f) + (axes[2] * getRandom(-2.f, 2.f));
		velocity = glm::normalize(velocity);
		velocity *= 50.f;
		mPosition = position;
		mVelocity = velocity;
	}

	void cParticle::SetDamping(float damping)
	{
		mDamping = glm::clamp(damping, 0.f, 1.f);
	}
	float cParticle::GetDamping() const
	{
		return mDamping;
	}

	float cParticle::GetMass() const
	{
		if (mInverseMass == 0.f)
		{
			return mInverseMass;
		}
		return 1.0f / mInverseMass;
	}

	float cParticle::GetInverseMass() const
	{
		return mInverseMass;
	}

	bool cParticle::IsStaticObject() const
	{
		return mInverseMass == 0.f;
	}

	glm::vec3 cParticle::GetPosition() const
	{
		return mPosition;
	}
	void cParticle::GetPosition(glm::vec3& position)
	{
		position = mPosition;
	}
	void cParticle::SetPosition(const glm::vec3& position)
	{
		mPosition = position;
	}

	glm::vec3 cParticle::GetVelocity() const
	{
		return mVelocity;
	}

	void cParticle::SetVelocity(const glm::vec3& velocity)
	{
		mVelocity = velocity * mSpeed;
	}

	glm::vec3 cParticle::GetAcceleration() const
	{
		return mAcceleration;
	}
	void cParticle::GetAcceleration(glm::vec3& acceleration)
	{
		acceleration = mAcceleration;
	}
	void cParticle::SetAcceleration(const glm::vec3& acceleration)
	{
		mAcceleration = acceleration;
	}

	void cParticle::SetLifeLine(float time)
	{
		mDuration -= time;
	}

	float cParticle::GetLifeLine() const
	{
		 return mDuration; 
	}

	void cParticle::ApplyForce(const glm::vec3& force)
	{
		mAppliedForce += force;
	}
	void cParticle::ClearAppliedForces()
	{
		glm::set(mAppliedForce, 0.f, 0.f, 0.f);
	}

	void cParticle::Integrate(float deltaTime)
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
	cGameObject* cParticle::pGetGameObject()
	{
		return nullptr;
	}
}