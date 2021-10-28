#include <graphics/OpenGL.h>
#include <physics/particle/cParticleWorld.h>
#include <physics/projectiles/Bullet.h>
#include <physics/projectiles/CannonBall.h>
#include <physics/projectiles/EnergyBall.h>
#include <physics/projectiles/Laser.h>

#include <iostream>

bool isShiftKeyDown(int mods);
bool isCtrlKeyDown(int mods);

extern float lastX;
extern float lastY;
extern bool firstMouse;
extern float deltaTime;
extern sCannonDef cannonDef;
extern nPhysics::cParticleWorld* particleWorld;
//TODO: move this to a more permanent set up. 
//TODO: perhaps make a method in a future class that will handle movement
bool keyUp = false;
bool keyDown = false;
bool keyRight = false;
bool keyLeft = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_ESCAPE: {
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	//handles camera movement
	case GLFW_KEY_A: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_LEFT, deltaTime);
		}
		break;
	}
	case GLFW_KEY_D: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_RIGHT, deltaTime);	// Move the camera -0.01f units
		}
		break;
	}
	case GLFW_KEY_W: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_FORWARD, deltaTime);	// Move the camera -0.01f units
		}
		break;
	}
	case GLFW_KEY_S: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_BACKWARD, deltaTime);	// Move the camera -0.01f units
		}
		break;
	}

	//handles cannon movement
	case GLFW_KEY_LEFT: {
		float yawSpeed = cannonDef.YawSpeed;
		yawSpeed = cannonDef.YawSpeed;
		cannonDef.Yaw += yawSpeed * deltaTime;
		cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		
		break;
	}
	case GLFW_KEY_RIGHT: {
		float yawSpeed = cannonDef.YawSpeed;
		yawSpeed = -cannonDef.YawSpeed;
		cannonDef.Yaw += yawSpeed * deltaTime;
		cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		break;
	}

	case GLFW_KEY_1: {
		if (action == GLFW_PRESS) {
			glm::mat4 launchMatrix = glm::mat4(1.0);
			launchMatrix = glm::eulerAngleXYZ(0.0f, cannonDef.Yaw, -cannonDef.Pitch);
			glm::vec4 launchDirection(1.f, 0.0f, 0.0f, 0.0f);
			launchDirection = launchMatrix * launchDirection;
			glm::vec3 launchPosition = launchDirection * 4.0f;

			nProjectiles::Bullet* bullet = new nProjectiles::Bullet(20.0f, launchPosition);
			bullet->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
			bullet->SetDamping(0.95f);
			bullet->SetLaunchDirection(launchDirection);
			bullet->SetVelocity(glm::normalize(launchDirection));


			particleWorld->AddParticle(bullet);
			break;
		}

	}
	case GLFW_KEY_2: {
		if (action == GLFW_PRESS) {
			glm::mat4 launchMatrix = glm::mat4(1.0);
			launchMatrix = glm::eulerAngleXYZ(0.0f, cannonDef.Yaw, -cannonDef.Pitch);
			glm::vec4 launchDirection(1.f, 0.0f, 0.0f, 0.0f);
			launchDirection = launchMatrix * launchDirection;
			glm::vec3 launchPosition = launchDirection * 4.0f;
			
			nProjectiles::CannonBall* cannonBall = new nProjectiles::CannonBall(50.0f, launchPosition);
			cannonBall->SetAcceleration(glm::vec3(0.0f, -9.8f, 0.0f));
			cannonBall->SetDamping(0.95f);
			cannonBall->SetLaunchDirection(launchDirection);
			cannonBall->SetVelocity(glm::normalize(launchDirection));
			
			particleWorld->AddParticle(cannonBall);
			break;
		}
	}
	

	}
	
	if (key == GLFW_KEY_UP) keyUp = action;
	if (key == GLFW_KEY_LEFT) keyLeft = action;
	if (key == GLFW_KEY_DOWN) keyDown = action;
	if (key == GLFW_KEY_RIGHT) keyRight = action;

	//if user is pressing up and down do nothing
	if (keyUp && !keyDown)
	{
		if (keyLeft) {
			float yawSpeed = cannonDef.YawSpeed;
			yawSpeed = cannonDef.YawSpeed;
			cannonDef.Yaw += yawSpeed * deltaTime;
			cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		}
		else if(keyRight) {
			float yawSpeed = cannonDef.YawSpeed;
			yawSpeed = -cannonDef.YawSpeed;
			cannonDef.Yaw += yawSpeed * deltaTime;
			cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		}
		float pitchSpeed = cannonDef.PitchSpeed;
		pitchSpeed = -cannonDef.PitchSpeed;
		cannonDef.Pitch += pitchSpeed * deltaTime;
		cannonDef.Pitch = glm::clamp(cannonDef.Pitch, cannonDef.PitchMinimum, cannonDef.PitchMaximum);	
	}
	if (!keyUp && keyDown)
	{
		if (keyLeft) {
			float yawSpeed = cannonDef.YawSpeed;
			yawSpeed = cannonDef.YawSpeed;
			cannonDef.Yaw += yawSpeed * deltaTime;
			cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		}
		else if (keyRight) {
			float yawSpeed = cannonDef.YawSpeed;
			yawSpeed = -cannonDef.YawSpeed;
			cannonDef.Yaw += yawSpeed * deltaTime;
			cannonDef.Yaw = glm::clamp(cannonDef.Yaw, cannonDef.YawMinimum, cannonDef.YawMaximum);
		}
		float pitchSpeed = cannonDef.PitchSpeed;
		pitchSpeed = cannonDef.PitchSpeed;
		cannonDef.Pitch += pitchSpeed * deltaTime;
		cannonDef.Pitch = glm::clamp(cannonDef.Pitch, cannonDef.PitchMinimum, cannonDef.PitchMaximum);
	}
	
	std::cout << nGraphics::gCamera->GetEyePosition().x << ", " <<
		nGraphics::gCamera->GetEyePosition().y << ", " <<
		nGraphics::gCamera->GetEyePosition().z << std::endl;

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = nGraphics::gCamera->GetMouseSens();
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	nGraphics::gCamera->ProcessMouseMovement(xoffset, yoffset);
}

bool isShiftKeyDown(int mods)
{
	if (mods == GLFW_MOD_SHIFT)
	{
		return true;
	}
	return false;
}

bool isCtrlKeyDown(int mods)
{
	if (mods == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}