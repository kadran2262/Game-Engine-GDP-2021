#pragma once
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/constants.hpp>

namespace nPhysics {
	float getRandom();
	float getRandom(float high);
	float getRandom(float low, float high);
	glm::vec3 getRandomVec3(float length);
	glm::vec3 getRandomXVector();
	glm::vec3 getRandomZVector();
	glm::vec3 getRandomVec3Alpha(float length);
	glm::vec3 getRandomVec3Delta(float length);
	glm::mat3 orthonormalBasis(const glm::vec3& xVec, const glm::vec3& zVec);
}