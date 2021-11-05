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
extern std::vector<cGameObject*> gameObjects;
extern std::vector<cGameObject*>::iterator selectedGameObject;
extern bool bLightDebugSheresOn;
//TODO: move this to a more permanent set up. 
//TODO: perhaps make a method in a future class that will handle movement
bool keyUp = false;
bool keyDown = false;
bool keyRight = false;
bool keyLeft = false;


cGameObject* GetCurrentGameObject()
{
	return *selectedGameObject;
}

float rotationSpeed = glm::pi<float>();

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_ESCAPE: {
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	}
	case GLFW_KEY_TAB: {
		if (isShiftKeyDown(mods))
			if (action == GLFW_PRESS)
				nGraphics::gLightManager->GetNextLight();
		if (action == GLFW_PRESS) {
			if (GetCurrentGameObject()->GetUniqueID() == gameObjects[gameObjects.size() - 1]->GetUniqueID()) {
				selectedGameObject = gameObjects.begin();
			}
			else
				selectedGameObject++;
		}
		break;
	}
	case GLFW_KEY_L: {
		if (action == GLFW_PRESS) {
			break;
		}
	}
	case GLFW_KEY_K: {
		if (action == GLFW_PRESS)
		break;
	}


	//handles campera and model movement
	case GLFW_KEY_A: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_LEFT, deltaTime);
		}
		else if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(0.0, 0.0, -0.1));
		}
		break;
	}
	case GLFW_KEY_D: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_RIGHT, deltaTime);	// Move the camera -0.01f units
		}
		else if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(0.0, 0.0, 0.1));
		}
		break;
	}
	case GLFW_KEY_W: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_FORWARD, deltaTime);	// Move the camera -0.01f units
		}
		else if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(0.1, 0.0, 0.0));
		}
		break;
	}
	case GLFW_KEY_S: {
		if (!isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			nGraphics::gCamera->ProcessKeyboard(CAMERA_BACKWARD, deltaTime);	// Move the camera -0.01f units
		}
		else if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(-0.1, 0.0, 0.0));
		}
		break;

	}
	case GLFW_KEY_Q: {
	
		if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(0.0, 0.1, 0.0));
		}
		break;

	}
	case GLFW_KEY_E: {

		if (isShiftKeyDown(mods) && !isCtrlKeyDown(mods)) {
			GetCurrentGameObject()->MoveObject(glm::vec3(0.0, -0.1, 0.0));
		}
		break;

	}

	
	

	//handles object rotations
	case GLFW_KEY_LEFT: {
		GetCurrentGameObject()->RotateObject(glm::vec3(0.0, rotationSpeed * deltaTime, 0.0));
		break;
	}
	case GLFW_KEY_RIGHT: {
		GetCurrentGameObject()->RotateObject(glm::vec3(0.0, -(rotationSpeed * deltaTime), 0.0));
		break;
	}
	case GLFW_KEY_UP: {
		GetCurrentGameObject()->RotateObject(glm::vec3(0.0, 0.0, (rotationSpeed * deltaTime)));
		break;
	}
	case GLFW_KEY_DOWN: {
		GetCurrentGameObject()->RotateObject(glm::vec3(0.0, 0.0, -(rotationSpeed * deltaTime)));
		break;
	}





	case GLFW_KEY_1: {
		bLightDebugSheresOn = true;
			break;
		

	}
	case GLFW_KEY_2: {
		
			break;
		
	}
	

	}
	
	

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