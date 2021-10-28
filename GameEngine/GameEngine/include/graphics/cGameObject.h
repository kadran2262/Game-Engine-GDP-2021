#ifndef _cGameObject_HG_
#define _cGameObject_HG_

#include <string>
#include <graphics/load/cMesh.h>
#include <GLCommon.h>

// NOTE: We are including the INTERFACE, not the actual renderer
//#include "../DebugRenderer/iDebugRenderer.h"
 
//TODO: Might want to move sCannonDef to its own file with perhaps its own class to handle
// specific stuff to do with the cannon or other weapons

struct sCannonDef
{
	sCannonDef()
	{
		Pitch = -glm::quarter_pi<float>();
		Yaw = 0.0f;
		PitchMaximum = -glm::pi<float>() / 8.0f;
		PitchMinimum = -glm::half_pi<float>();
		YawMinimum = -glm::quarter_pi<float>();
		YawMaximum = glm::quarter_pi<float>();
		YawSpeed = glm::quarter_pi<float>();
		PitchSpeed = glm::quarter_pi<float>();
	}
	float Pitch;
	float Yaw;
	float PitchMinimum;
	float PitchMaximum;
	float YawMinimum;
	float YawMaximum;
	float PitchSpeed;
	float YawSpeed;
};

enum eShapeTypes
	{
		AABB,					// min and max corners 
		SPHERE,					// Radius
		CAPSULE,
		PLANE,
		MESH,		// Triangle test
		UNKNOWN
	};

struct sGameObjectDef {
	sGameObjectDef() :
		ModelColor(1.f, 1.f, 1.f, 1.f),
		Position(0.0f, 0.0f, 0.0f),
		Rotation(0.0f, 0.0f, 0.0f),
		Scale(1.f, 1.f, 1.f)
	{}
	std::string Mesh;
	glm::vec4 ModelColor;
	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Scale;

};

class cGameObject
{
public:
	cGameObject();
	cGameObject(const sGameObjectDef& def);
	virtual ~cGameObject();


	inline glm::mat4 GetModelMatrix() { return mModelMatrix; }
	inline glm::vec4 GetModelColour() { return mModelColour; }
	inline cMesh* GetMesh() { return mMesh; }
	inline std::string GetMeshName() { return mMeshName; }
	unsigned int GetUniqueID(void);

	bool SetMesh(const std::string& meshName);
	void SetModelMatrix(const glm::mat4& matrix);
	void SetModelColour(const glm::vec4& colour);

	//void setDebugRenderer(iDebugRenderer* pDebugRenderer);

private:
	// this variable is static, so common to all objects.
	// When the object is created, the unique ID is set, and 
	//	the next unique ID is incremented
	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;
	glm::mat4 mModelMatrix;
	glm::vec4 mModelColour;
	cMesh* mMesh;
	std::string mMeshName;
	//iDebugRenderer* m_pDebugRenderer;
};

#endif


