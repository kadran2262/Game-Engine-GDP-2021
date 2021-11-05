#include <graphics/OpenGL.h>
#include <physics/projectiles/Bullet.h>
#include <physics/particle/cParticleWorld.h>
#include <iostream>
#include <FileLoader/cFileLoader.h>
#include <graphics/lights/cLightHelper.h>


bool firstMouse = true;
int windowWidth = 1024;
int windowHeight = 768;
float lastX = windowWidth / 2;
float lastY = windowHeight / 2;
float deltaTime;
Camera* camera = 0;
std::vector<cGameObject*> gameObjects;
std::vector<cGameObject*>::iterator selectedGameObject;
nPhysics::cParticleWorld* particleWorld;
bool bLightDebugSheresOn = false;
cLightHelper* pLightHelper = new cLightHelper();

sCannonDef cannonDef;

int main() {
	cGameObject* pDebugSphere;
	sGameObjectDef objectDef;
	objectDef.Mesh = "Sphere";
	objectDef.FriendlyName = "debug_sphere";
	objectDef.Position = glm::vec3(0.0f, 0.0f, 0.0f);
	objectDef.Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	objectDef.Scale = glm::vec3(0.1f);
	objectDef.ModelColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	objectDef.Wireframe = true;
	pDebugSphere = new cGameObject(objectDef);



	camera = new Camera(glm::vec3(-15.0,2.5,2.5));
	nGraphics::SetCamera(camera);
	
	//initilize OpenGL calls/set up window
	if (!nGraphics::Init())
	{
		std::cout << "Graphics didn't start up right" << std::endl;
		system("pause");
		return -1;
	}

	
	particleWorld = new nPhysics::cParticleWorld();

#pragma region LoadMeshes
	cMesh* ceilingLightMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Ceiling_Light_02_xyz_n.ply", *ceilingLightMesh);
	nGraphics::gMeshes["CeilingLight"] = ceilingLightMesh;

	cMesh* doorMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Door_01_xyz_n.ply", *doorMesh);
	nGraphics::gMeshes["Door"] = doorMesh;

	cMesh* sphereMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/Sphere_Radius_1_XYZ_n.ply", *sphereMesh);
	nGraphics::gMeshes["Sphere"] = sphereMesh;

	cMesh* floorFourMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Floor_04_xyz_n.ply", *floorFourMesh);
	nGraphics::gMeshes["Floor"] = floorFourMesh;

	cMesh* HangerFloorMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Floor_01_xyz_n.ply", *HangerFloorMesh);
	nGraphics::gMeshes["HangerFloor"] = HangerFloorMesh;

	cMesh* mainWallMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Construction_Wall_01_xyz_n.ply", *mainWallMesh);
	nGraphics::gMeshes["MainWall"] = mainWallMesh;

	cMesh* curvedDoorOneMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Transition_Door_Curved_01_xyz_n.ply", *curvedDoorOneMesh);
	nGraphics::gMeshes["CurvedDoor"] = curvedDoorOneMesh;

	cMesh* curvedWallOneMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Wall_Curved_01_xyz_n.ply", *curvedWallOneMesh);
	nGraphics::gMeshes["CurvedWallOne"] = curvedWallOneMesh;

	cMesh* curvedWallTwoMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Wall_Curved_02_xyz_n.ply", *curvedWallTwoMesh);
	nGraphics::gMeshes["CurvedWallTwo"] = curvedWallTwoMesh;

	cMesh* curvedWallThreeMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Wall_Curved_03_xyz_n.ply", *curvedWallThreeMesh);
	nGraphics::gMeshes["CurvedWallThree"] = curvedWallThreeMesh;

	cMesh* curvedWallFourMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Wall_Curved_04_xyz.ply", *curvedWallFourMesh);
	nGraphics::gMeshes["CurvedWallFour"] = curvedWallFourMesh;

	cMesh* curvedWallFiveMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Env_Wall_Curved_05_xyz_n.ply", *curvedWallFiveMesh);
	nGraphics::gMeshes["CurvedWallFive"] = curvedWallFiveMesh;

	cMesh* monitorMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Monitor_02_xyz_n.ply", *monitorMesh);
	nGraphics::gMeshes["Monitor"] = monitorMesh;

	cMesh* plantOneMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Plants_01_xyz_n.ply", *plantOneMesh);
	nGraphics::gMeshes["PlantsOne"] = plantOneMesh;

	cMesh* plantTwoMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Plants_03_xyz_n.ply", *plantTwoMesh);
	nGraphics::gMeshes["PlantsTwo"] = plantTwoMesh;

	cMesh* plantThreeMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Plants_04_xyz_n.ply", *plantThreeMesh);
	nGraphics::gMeshes["PlantsThree"] = plantThreeMesh;

	cMesh* severMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Server_03_xyz_n.ply", *severMesh);
	nGraphics::gMeshes["ServerThree"] = severMesh;

	cMesh* serverRackMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_ServerRack_01_xyz_n.ply", *serverRackMesh);
	nGraphics::gMeshes["ServerRackOne"] = serverRackMesh;

	cMesh* chairMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_SwivelChair_03_xyz_n.ply", *chairMesh);
	nGraphics::gMeshes["SwivelChair"] = chairMesh;

	cMesh* trolleyMesh = new cMesh;
	nGraphics::gModelLoader->LoadPlyModel("assets/models/SM_Prop_Trolley_01_xyz_n.ply", *trolleyMesh);
	nGraphics::gMeshes["Trolley"] = trolleyMesh;
#pragma endregion



	for (std::pair<std::string, cMesh*> myPair : nGraphics::gMeshes) {
		sModelDrawInfo meshDrawInfo;
		nGraphics::gVAOManager->LoadModelIntoVAO(myPair.first.c_str(),
			*myPair.second,
			meshDrawInfo,
			nGraphics::gShader->GetProgramId());
	}



#pragma region Set up Lights
		sLight* myLight = new sLight();
		glm::set(myLight->atten, 0.0000003f, .00003f, 0.000003f);
		glm::set(myLight->diffuse, 1.0f, 1.1f, 1.0f, 1.0f);
		glm::set(myLight->specular, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(myLight->position, -10.0f, 1000.0f, 0.0f);
		glm::set(myLight->param1, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(myLight->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(myLight);

		//{"FriendlyName":"HangerLight1", "atten" : [9.999999974752428e-7, 9.999999974752428e-7, 1.0000000116860974e-7, 1000000.0] , "atten_UniLoc" : 63, "position" : [5.0, 25.0, 32.0] , "position_UniLoc" : 3, "diffuse" : [1.0, 1.0, 1.0, 1.0] , "diffuse_UniLoc" : 23, "direction" : [0.0, -1.0, 0.0, 1.0] , "direction_UniLoc" : 83, "param1" : [1.0, 5.0, 10.0, 0.0] , "param1_UniLoc" : 103, "param2" : [1.0, 0.0, 0.0, 0.0] , "param2_UniLoc" : 123, "specular" : [0.0, 0.0, 0.0, 0.0] , "specular_UniLoc" : 43}
		sLight* spotLight = new sLight();
		spotLight->FriendlyName = "spotlight";
		glm::set(spotLight->atten, 0.003f, .003f, 0.003f);
		glm::set(spotLight->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight->specular, 1.0f,1.0f, 1.0f, 10.0f);
		glm::set(spotLight->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight->position, 5.0f, 23.0f, 32.0f);
		glm::set(spotLight->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight);

		sLight* spotLight2 = new sLight();
		spotLight2->FriendlyName = "spotlight";
		glm::set(spotLight2->atten, 0.003f, .003f, 0.001f);
		glm::set(spotLight2->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight2->specular, 1.0f, 1.0f, 1.0f, 10.0f);
		glm::set(spotLight2->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight2->position, 25.0f, 23.0f, 32.0f);
		glm::set(spotLight2->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight2->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight2);

		sLight* spotLight3 = new sLight();
		spotLight3->FriendlyName = "spotlight";
		glm::set(spotLight3->atten, 0.003f, .003f, 0.003f);
		glm::set(spotLight3->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight3->specular, 1.0f, 1.0f, 1.0f, 10.0f);
		glm::set(spotLight3->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight3->position, 45.0f, 23.0f, 32.0f);
		glm::set(spotLight3->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight3->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight3);

		sLight* spotLight4 = new sLight();
		spotLight4->FriendlyName = "spotlight";
		glm::set(spotLight4->atten, 0.003f, .003f, 0.003f);
		glm::set(spotLight4->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight4->specular, 1.0f, 1.0f, 1.0f, 10.0f);
		glm::set(spotLight4->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight4->position, 5.0f, 23.0f, 10.0f);
		glm::set(spotLight4->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight4->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight4);

		sLight* spotLight5 = new sLight();
		spotLight5->FriendlyName = "spotlight";
		glm::set(spotLight5->atten, 0.003f, .003f, 0.003f);
		glm::set(spotLight5->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight5->specular, 1.0f, 1.0f, 1.0f, 10.0f);
		glm::set(spotLight5->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight5->position, 25.0f, 23.0f, 10.0f);
		glm::set(spotLight5->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight5->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight5);

		sLight* spotLight6 = new sLight();
		spotLight6->FriendlyName = "spotlight";
		glm::set(spotLight6->atten, 0.003f, .003f, 0.003f);
		glm::set(spotLight6->diffuse, 1.0f, 1.0f, 1.0f, 1.0f);
		glm::set(spotLight6->specular, 1.0f, 1.0f, 1.0f, 10.0f);
		glm::set(spotLight6->direction, 0.0f, -1.0, 0.0f);
		glm::set(spotLight6->position, 45.0f, 23.0f, 10.0f);
		glm::set(spotLight6->param1, 1.0, 2.0, 35.0, 0.0);
		glm::set(spotLight6->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(spotLight6);


		sLight* corridorLight1 = new sLight();
		corridorLight1->FriendlyName = "CorridorLight";
		glm::set(corridorLight1->atten, 0.1f, .1f, 0.1f);
		glm::set(corridorLight1->diffuse, .5f, .5f, .0f, 1.0f);
		glm::set(corridorLight1->specular, 0.5f, 0.5f, 0.0f, 0.0f);
		glm::set(corridorLight1->position, -5.0, 4.0, 2.5);
		glm::set(corridorLight1->param1, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(corridorLight1->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(corridorLight1);


		sLight* corridorLight2 = new sLight();
		corridorLight2->FriendlyName = "CorridorLight";
		glm::set(corridorLight2->atten, 0.1f, .1f, 0.1f);
		glm::set(corridorLight2->diffuse, .5f, .5f, .0f, 1.0f);
		glm::set(corridorLight2->specular, 0.5f, 0.5f, 0.0f, 0.0f);
		glm::set(corridorLight2->position, -10.0, 4.0, 2.5);
		glm::set(corridorLight2->param1, 0.0f, 0.0f, 0.0f, 0.0f);
		glm::set(corridorLight2->param2, 1.0f, 0.0f, 0.0f, 0.0f);
		nGraphics::gLightManager->m_vecLights.push_back(corridorLight2);

		nGraphics::gLightManager->m_pCurrentLight = nGraphics::gLightManager->m_vecLights.begin();
#pragma endregion


#pragma region Create GameObjects
		//set up the hanger room
		for (int z = 0; z < 12; z++) {
			for (int x = 0; x < 8; x++) {
				sGameObjectDef objectDef;
				objectDef.Mesh = "HangerFloor";
				objectDef.FriendlyName = "HangerFloor";
				glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
				glm::set(objectDef.ModelColor, 1.5, 0.5, 0.5, 1.0);
				glm::set(objectDef.Position, (5.0 * z), (0.0), 5.0 * x);
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));
			}
		}
		for (int z = 0; z < 12; z++) {
			for (int x = 0; x < 8; x++) {
				sGameObjectDef objectDef;
				objectDef.Mesh = "HangerFloor";
				objectDef.FriendlyName = "HangerFloor";
				glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
				glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
				glm::set(objectDef.Position, (5.0 * z), (25.0), 5.0 * x);
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));
			}
		}


		for (int z = 0; z < 5; z++) {
			for (int x = 0; x < 4; x++) {
				if (x == 0 && z == 0) {
				}
				else {
					sGameObjectDef objectDef;
					objectDef.Mesh = "MainWall";
					objectDef.FriendlyName = "MainWall";
					glm::set(objectDef.Rotation, 0.0, glm::half_pi<float>(), 0.0);
					glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
					glm::set(objectDef.Position, -10.0 * x - 10, 5.0 * z, -5.0);
					glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
					gameObjects.push_back(new cGameObject(objectDef));
				}
			}
		}
		for (int z = 0; z < 5; z++) {
			for (int x = 0; x < 4; x++) {


				sGameObjectDef objectDef;
				objectDef.Mesh = "MainWall";
				objectDef.FriendlyName = "MainWall";
				glm::set(objectDef.Rotation, 0.0, -glm::half_pi<float>(), 0.0);
				glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
				glm::set(objectDef.Position, 10.0 * x, 5.0 * z, -55.0);
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));

			}
		}
		for (int z = 0; z < 5; z++) {
			for (int x = 0; x < 6; x++) {
				sGameObjectDef objectDef;
				objectDef.Mesh = "MainWall";
				objectDef.FriendlyName = "MainWall";
				glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
				glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
				glm::set(objectDef.Position, (10.0 * x) - 5, 5 * z, (0.0));
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));
			}
		}
		for (int z = 0; z < 5; z++) {
			for (int x = 0; x < 6; x++) {
				sGameObjectDef objectDef;
				objectDef.Mesh = "MainWall";
				objectDef.FriendlyName = "MainWall";

				glm::set(objectDef.Rotation, 0.0f, glm::pi<float>(), 0.0f);
				glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
				glm::set(objectDef.Position, (-10.0 * x) - 5, 5 * z, -40.0f);
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));
			}
		}

		//set up models for lights
		for (sLight* light : nGraphics::gLightManager->m_vecLights) {
			if (light->FriendlyName == "spotlight" || light->FriendlyName=="CorridorLight") {
				sGameObjectDef objectDef;
				objectDef.Mesh = "CeilingLight";
				objectDef.FriendlyName = "CeilingLight";
				glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
				glm::set(objectDef.ModelColor, 1.0, 1.0, 0.0, 1.0);
				objectDef.Position = light->position + glm::vec4(0.0,1.0,0.0,0.0);
				glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
				gameObjects.push_back(new cGameObject(objectDef));
			}
		}

		
		objectDef.Mesh = "CurvedDoor";
		objectDef.FriendlyName = "CurvedDoor";
		glm::set(objectDef.Rotation, 0.0, -glm::half_pi<float>(), 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, 0.0,0.0,2.5);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "Door";
		objectDef.FriendlyName = "Door";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -2.5, 0.0, 1.50);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));
		
		objectDef.Mesh = "CurvedWallOne";
		objectDef.FriendlyName = "CurvedWallOne";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -5.0, 0.0, 0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "CurvedWallOne";
		objectDef.FriendlyName = "CurvedWallOne";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -10.0, 0.0, 0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "CurvedWallOne";
		objectDef.FriendlyName = "CurvedWallOne";
		glm::set(objectDef.Rotation, 0.0, glm::pi<float>(), 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, 10.0, 0.0, -5.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "CurvedWallFive";
		objectDef.FriendlyName = "CurvedWallFive";
		glm::set(objectDef.Rotation, 0.0, glm::pi<float>(), 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, 15.0, 0.0, -5.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "Floor";
		objectDef.FriendlyName = "Floor";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -5.0,0.0,0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "Floor";
		objectDef.FriendlyName = "Floor";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -10.0, 0.0, 0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "Floor";
		objectDef.FriendlyName = "Floor";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -5.0, 5.0, 0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

		objectDef.Mesh = "Floor";
		objectDef.FriendlyName = "Floor";
		glm::set(objectDef.Rotation, 0.0, 0.0, 0.0);
		glm::set(objectDef.ModelColor, 0.5, 0.5, 0.5, 1.0);
		glm::set(objectDef.Position, -10.0, 5.0, 0.0);
		glm::set(objectDef.Scale, 1.0, 1.0, 1.0);
		gameObjects.push_back(new cGameObject(objectDef));

#pragma endregion
		selectedGameObject = gameObjects.begin();

	nGraphics::Focus();

	bool continueMainLoop = true;

	float previousTime = static_cast<float>(glfwGetTime());

	float fpsFrameCount = 0.f;
	float fpsTimeElapsed = 0.f;
	
	//glm::vec4 clear_color = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);

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

		

#pragma region Bind Shader and Set Uniforms
		nGraphics::gShader->Bind();
		nGraphics::gShader->SetUniform_ViewMatrix(glm::value_ptr(camera->GetViewMatrix()));
		nGraphics::gShader->SetUniform_EyePosition(glm::value_ptr(camera->GetEyePosition()));
		nGraphics::gShader->SetUniform_ProjectionMatrix(glm::value_ptr(camera->GetProjectionMatrix()));

		nGraphics::gLightManager->LoadUniformLocations(nGraphics::gShader->GetProgramId());
		nGraphics::gLightManager->CopyLightValuesToShader();
#pragma endregion

		

#pragma region DrawObjects
		for (cGameObject* object : gameObjects) {
			nGraphics::DrawObject(object);
		}

		if (bLightDebugSheresOn)
		{

			{// Draw where the light is at
				glm::mat4 matModel = glm::mat4(1.0f);
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;

				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(0.5f);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject(((cGameObject*)pDebugSphere));
			}

			// Draw spheres to represent the attenuation...
			{   // Draw a sphere at 1% brightness
				
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.01f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					nGraphics::gLightManager->GetCurrentLight()->atten.x,
					nGraphics::gLightManager->GetCurrentLight()->atten.y,
					nGraphics::gLightManager->GetCurrentLight()->atten.z);
				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(sphereSize);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject( ((cGameObject*)pDebugSphere));
			}
			{   // Draw a sphere at 25% brightness
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.25f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					nGraphics::gLightManager->GetCurrentLight()->atten.x,
					nGraphics::gLightManager->GetCurrentLight()->atten.y,
					nGraphics::gLightManager->GetCurrentLight()->atten.z);
				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(sphereSize);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject(((cGameObject*)pDebugSphere));
			}
			{   // Draw a sphere at 50% brightness
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.50f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					nGraphics::gLightManager->GetCurrentLight()->atten.x,
					nGraphics::gLightManager->GetCurrentLight()->atten.y,
					nGraphics::gLightManager->GetCurrentLight()->atten.z);
				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(sphereSize);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject(((cGameObject*)pDebugSphere));
			}
			{   // Draw a sphere at 75% brightness
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.75f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					nGraphics::gLightManager->GetCurrentLight()->atten.x,
					nGraphics::gLightManager->GetCurrentLight()->atten.y,
					nGraphics::gLightManager->GetCurrentLight()->atten.z);
				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(sphereSize);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(0.0f, 1.0f, 1.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject(((cGameObject*)pDebugSphere));
			}
			{   // Draw a sphere at 95% brightness
				((cGameObject*)pDebugSphere)->GetPosition() = nGraphics::gLightManager->GetCurrentLight()->position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.95f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					nGraphics::gLightManager->GetCurrentLight()->atten.x,
					nGraphics::gLightManager->GetCurrentLight()->atten.y,
					nGraphics::gLightManager->GetCurrentLight()->atten.z);
				((cGameObject*)pDebugSphere)->GetScale() = glm::vec3(sphereSize);
				((cGameObject*)pDebugSphere)->SetModelColour(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
				((cGameObject*)pDebugSphere)->SetWireframe(true);
				nGraphics::DrawObject(((cGameObject*)pDebugSphere));
			}
		}// if (bLightDebugSheresOn) 
#pragma endregion


		//move any possible particles we have to move
		particleWorld->TimeStep(deltaTime);
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
	gameObjects.clear();
	delete particleWorld;
	nGraphics::Shutdown();

	// all done!
	return 0;
}