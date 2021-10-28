#pragma once
#include <GLCommon.h>
#include <graphics/camera/cCamera.h>
#include <graphics/shader/SimpleShader.h>
#include <graphics/load/cVAOManager.h>
#include <graphics/load/cModelLoader.h>
#include <graphics/cGameObject.h>
#include <graphics/lights/cLightManager.h>
namespace nGraphics {

	extern GLFWwindow* gWindow;
	extern Camera* gCamera;
	extern cSimpleShader* gShader;
	extern cVAOManager* gVAOManager;
	extern cModelLoader* gModelLoader;
	extern cLightManager* gLightManager;
	extern std::map<std::string, cMesh*> gMeshes;

	bool Init();
	void DrawObject(cGameObject* pCurrentObject);
	void Render();
	bool WindowShouldClose();
	void Focus();
	void SetCamera(Camera* camera);
	void SetWindowTitle(const std::string& title);
	void Callback_WindowResize(GLFWwindow* window, int width, int height);
	void Shutdown();
}