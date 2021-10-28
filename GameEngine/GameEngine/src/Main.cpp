#include <graphics/OpenGL.h>
#include <physics/projectiles/Bullet.h>
#include <physics/particle/cParticleWorld.h>
#include <iostream>



bool firstMouse = true;
int windowWidth = 1024;
int windowHeight = 768;
float lastX = windowWidth / 2;
float lastY = windowHeight / 2;
float deltaTime;
Camera* camera = 0;
cGameObject* terrainObject;
cGameObject* sphereObject;
cGameObject* cannonObject;

nPhysics::cParticleWorld* particleWorld;



sCannonDef cannonDef;

int main() {

	camera = new Camera(glm::vec3(-10.0f, 2.5f, 0.0f));
	nGraphics::SetCamera(camera);
	
	//initilize OpenGL calls/set up window
	if (!nGraphics::Init())
	{
		std::cout << "Graphics didn't start up right" << std::endl;
		system("pause");
		return -1;
	}

	particleWorld = new nPhysics::cParticleWorld();

// TODO: Load these from a file
#pragma region Load Models/Meshes

	cMesh* terrainMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/BigFlatTerrain_XYZ_n.ply", *terrainMesh);
	nGraphics::gMeshes["terrain"] = terrainMesh;

	cMesh* sphereMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/Sphere_Radius_1_XYZ_n.ply", *sphereMesh);
	nGraphics::gMeshes["sphere"] = sphereMesh;

	cMesh* cannonMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/Railgun_Prototype-Polygon_File_Format_NoText.ply", *cannonMesh);
	nGraphics::gMeshes["cannon"] = cannonMesh;

	sModelDrawInfo drawInfoTerrain;
	nGraphics::gVAOManager->LoadModelIntoVAO("terrain",
		*terrainMesh,
		drawInfoTerrain,
		nGraphics::gShader->GetProgramId());


	sModelDrawInfo sphereMeshInfo;
	nGraphics::gVAOManager->LoadModelIntoVAO("sphere",
		*sphereMesh,		// Sphere mesh info
		sphereMeshInfo,
		nGraphics::gShader->GetProgramId());

	sModelDrawInfo cannonMeshInfo;
	nGraphics::gVAOManager->LoadModelIntoVAO("cannon",
		*cannonMesh,		// Sphere mesh info
		cannonMeshInfo,
		nGraphics::gShader->GetProgramId());
#pragma endregion

#pragma region Create GameObjects

	sGameObjectDef terrainObjectDef;
	terrainObjectDef.Mesh = "terrain";
	glm::set(terrainObjectDef.ModelColor, 0.5f, 0.5f, 0.0f, 1.0f);
	glm::set(terrainObjectDef.Position, 0.0f, 0.0f, 0.0f);
	glm::set(terrainObjectDef.Scale, 1.0f, 1.0f, 1.0f);
	terrainObject = new cGameObject(terrainObjectDef);

	sGameObjectDef cannonObjectDef;
	cannonObjectDef.Mesh = "cannon";
	glm::set(cannonObjectDef.ModelColor, 1.0f, 1.0f, 1.0f, 1.0f);
	glm::set(cannonObjectDef.Position, 0.0f, 0.0f, 0.0f);
	glm::set(cannonObjectDef.Scale, 5.0f, 5.0f, 5.0f);
	cannonObject = new cGameObject(cannonObjectDef);


	sGameObjectDef sphereObjectDef;
	sphereObjectDef.Mesh = "sphere";
	glm::set(sphereObjectDef.ModelColor, 1.0f, 0.0f, 0.0f, 1.0f);
	glm::set(sphereObjectDef.Position, 0.0f, 0.0f, 0.0f);
	glm::set(sphereObjectDef.Scale, 1.0f, 1.0f, 1.0f);
	sphereObject = new cGameObject(sphereObjectDef);
#pragma endregion

#pragma region Set up Lights
	sLight* myLight = new sLight();
		glm::set(myLight->atten, 0.00000003f, .000003f, 0.000001f);
		glm::set(myLight->diffuse, 1.0f, 1.1f, 1.0f, 1.0f);
		glm::set(myLight->specular, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(myLight->position, -10.0f, 1000.0f, 0.0f);
		glm::set(myLight->param1, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(myLight->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(myLight);
#pragma endregion

	nGraphics::Focus();

	bool continueMainLoop = true;

	float previousTime = static_cast<float>(glfwGetTime());

	float fpsFrameCount = 0.f;
	float fpsTimeElapsed = 0.f;


	while (!nGraphics::WindowShouldClose()) {

		float currentTime = static_cast<float>(glfwGetTime());
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;

		// FPS TITLE STUFF
		{
			fpsTimeElapsed += deltaTime;
			fpsFrameCount += 1.0f;
			if (fpsTimeElapsed >= 0.03f)
			{
				std::string fps = std::to_string(fpsFrameCount / fpsTimeElapsed);
				std::string ms = std::to_string(1000.f * fpsTimeElapsed / fpsFrameCount);
				std::string newTitle = "FPS: " + fps + "   MS: " + ms;
				nGraphics::SetWindowTitle(newTitle);
				// reset times and counts
				fpsTimeElapsed = 0.f;
				fpsFrameCount = 0.f;
			}
		}


		glfwGetFramebufferSize(nGraphics::gWindow, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		particleWorld->TimeStep(deltaTime);

#pragma region Bind Shader and Set Uniforms
		nGraphics::gShader->Bind();
		nGraphics::gShader->SetUniform_ViewMatrix(glm::value_ptr(camera->GetViewMatrix()));
		nGraphics::gShader->SetUniform_EyePosition(glm::value_ptr(camera->GetEyePosition()));
		nGraphics::gShader->SetUniform_ProjectionMatrix(glm::value_ptr(camera->GetProjectionMatrix()));
#pragma endregion

		nGraphics::gLightManager->LoadUniformLocations(nGraphics::gShader->GetProgramId());
		nGraphics::gLightManager->CopyLightValuesToShader();

#pragma region DrawObjects
		//draw terraint
		nGraphics::DrawObject(terrainObject);
		

		//modify and draw cannon object
		glm::mat4 cannonMatrix = glm::eulerAngleXYZ(0.0f, cannonDef.Yaw, -cannonDef.Pitch);
		cannonMatrix = glm::translate(cannonMatrix, glm::vec3(0.0f, 1.0, 0.0f));
		cannonMatrix = glm::scale(cannonMatrix, cannonObjectDef.Scale);
		cannonObject->SetModelMatrix(cannonMatrix);
		nGraphics::DrawObject(cannonObject);

		for (nPhysics::cParticle* particle : particleWorld->getParticles()) {
			glm::mat4 projectileMatrix(1.0f);
			projectileMatrix = glm::translate(projectileMatrix, particle->GetPosition());
			projectileMatrix = glm::scale(projectileMatrix, glm::vec3(particle->GetRadius()));
			sphereObject->SetModelMatrix(projectileMatrix);
			sphereObject->SetModelColour(particle->GetColour());
			nGraphics::DrawObject(sphereObject);
			
		}

#pragma endregion

		for (nPhysics::cParticle* particle : particleWorld->getParticles())
		{
			if (particle->GetPosition().y<0)
			{
				particleWorld->RemoveParticle(particle);
				delete particle;
			}

		}

		// Swap buffers
		glfwSwapBuffers(nGraphics::gWindow);
		glfwPollEvents();
	}

	delete camera;
	delete terrainObject;
	delete cannonObject;
	delete sphereObject;
	delete particleWorld;
	nGraphics::Shutdown();

	// all done!
	return 0;
}