#pragma once
#include <Physics/Particle/cParticle.h>
namespace nProjectiles {
	class Bullet : public nPhysics::cParticle {
		glm::vec4 m_ModelColour;
		glm::vec3 m_LaunchDirection;
		float m_Radius;
	public:
		virtual ~Bullet();
		Bullet(float mass, glm::vec3 position);

		inline void SetModelColour(const glm::vec4& colour) { m_ModelColour = colour; }
		inline glm::vec4 GetColour() { return m_ModelColour; }
		inline void SetLaunchDirection(const glm::vec3& direction) { m_LaunchDirection = direction; }
		inline glm::vec3 GetLaunchDirection() { return m_LaunchDirection; }
		inline float GetRadius() { return m_Radius; }
		inline void SetRadius(float radius) { m_Radius = radius; }

		void Integrate(float deltaTime);
	};
}