#pragma once
#include <random_helpers.h>
#include <GLCommon.h>
#include <graphics/cGameObject.h>
namespace nPhysics
{
	class cParticle
	{
	protected:
		// Linear position of the particle in world space
		glm::vec3 mPosition;
		// Linear velocity of the particle in world space
		glm::vec3 mVelocity;
		// Linear acceleration of the particle in world space
		glm::vec3 mAcceleration;
		// Inverse mass
		float mInverseMass;
		// Externally applied forces accumulated during a time step
		glm::vec3 mAppliedForce;
		// Damping is applied to linear motion
		// Required to remove energy added through numerical instability of integration
		// Also generally used as an overall "friction" for the particle
		float mDamping;

		float mSpeed;

		float mDuration;


	public:
		cParticle(float mass, const glm::vec3& position);
		virtual ~cParticle();
		cParticle() = delete;
		cParticle(cParticle& other) = delete;
		cParticle& operator=(cParticle& other) = delete;

		virtual float GetRadius();
		virtual glm::vec4 GetColour();
		virtual void SetDefaultVars();

		void SetDamping(float damping);
		float GetDamping() const;

		float GetMass() const;
		float GetInverseMass() const;

		bool IsStaticObject() const;

		glm::vec3 GetPosition() const;
		void GetPosition(glm::vec3& position);
		void SetPosition(const glm::vec3& position);

		glm::vec3 GetVelocity() const;
		void GetVelocity(glm::vec3& velocity);
		void SetVelocity(const glm::vec3& velocity);

		glm::vec3 GetAcceleration() const;
		void GetAcceleration(glm::vec3& acceleration);
		void SetAcceleration(const glm::vec3& acceleration);

		void SetLifeLine(float time); //subtracts the value sent from the lifeline
		float GetLifeLine() const;

		void ApplyForce(const glm::vec3& force);
		void ClearAppliedForces();

		virtual void Integrate(float deltaTime);
		virtual cGameObject* pGetGameObject();
	};
}