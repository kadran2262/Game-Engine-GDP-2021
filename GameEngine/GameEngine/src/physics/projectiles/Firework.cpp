#include <physics/projectiles/Firework.h>
#include <random_helpers.h>




nProjectiles::Firework::Firework(float mass, const glm::vec3& position) : cParticle(mass, position)
{
	
	mPosition = position;
	mVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
	mDamping = 0.995f;
	mAppliedForce = glm::vec3(0.0f, 0.0f, 0.0f);
	mDuration = 1000.f;
	
	if (mass <= 0.f)
	{
		mInverseMass = 0.f;
	}
	else
	{
		mInverseMass = 1.f / mass;
	}
	
}

float nProjectiles::Firework::getDuration()
{
	return mDuration;
}


void nProjectiles::Firework::Explode(nPhysics::cParticleWorld* world, nPhysics::cParticleGravityGenerator* gravityGenerator)
{
	mDuration = 0;
	glm::mat3 axes;
	for (int idx = 0; idx < 100; idx++)
	{
		nPhysics::cParticle* particle2 = new nPhysics::cParticle(1.0f, glm::vec3(0.f));

		if (world->AddParticle(particle2))
		{
			axes = nPhysics::orthonormalBasis(nPhysics::getRandomXVector(), nPhysics::getRandomZVector());
			// because our "sphere" has a radius of 1
			glm::vec3 position = world->getParticles()[0]->GetPosition();
			glm::vec3 velocity;
			if (this->mType == 0)
				velocity = nPhysics::getRandomVec3(50);
			else if (this->mType == 1)
				velocity = nPhysics::getRandomVec3Alpha(10000);
			else if(this->mType == 2)
				velocity = nPhysics::getRandomVec3Delta(100);
			
			
			velocity = glm::normalize(velocity);
			velocity *= 100.f;
			particle2->SetPosition(position);
			particle2->SetVelocity(velocity);
		}
		world->GetForceRegistry()->Register(particle2, gravityGenerator);
		world->getParticles().push_back(particle2);
		
	}
}
