#include <graphics/cGameObject.h>
#include <graphics/OpenGL.h>
#include <GLCommon.h>


	cGameObject::cGameObject()
	{
		this->m_uniqueID = this->next_uniqueID;
		this->next_uniqueID++;
		return;
	}

	cGameObject::cGameObject(const sGameObjectDef& def)
	{

		if (def.Mesh != "")
		{
			SetMesh(def.Mesh);
		}


		mModelMatrix = glm::eulerAngleXYZ(def.Rotation.x, def.Rotation.y, def.Rotation.z);
		mModelMatrix = glm::translate(mModelMatrix, def.Position);
		mModelMatrix = glm::scale(mModelMatrix, def.Scale);
		mModelColour = def.ModelColor;
		


		this->m_uniqueID = this->next_uniqueID;
		this->next_uniqueID++;
		return;
	}

	cGameObject::~cGameObject()
	{
		mMesh = 0;
	}


	unsigned int cGameObject::GetUniqueID(void)
	{
		return this->m_uniqueID;
	}

	bool cGameObject::SetMesh(const std::string& meshName)
	{
		mMesh = nGraphics::gMeshes[meshName];
		mMeshName = meshName;
		return mMesh!=0;
	}

	void cGameObject::SetModelMatrix(const glm::mat4& matrix)
	{
		mModelMatrix = matrix;

	}

	void cGameObject::SetModelColour(const glm::vec4& colour) {
		mModelColour = colour;
	}

	//void cGameObject::setDebugRenderer(iDebugRenderer* pDebugRenderer)
	//{
	//	this->m_pDebugRenderer = pDebugRenderer;
	//	return;
	//}


	// this variable is static, so common to all objects.
	// When the object is created, the unique ID is set, and 
	//	the next unique ID is incremented
	//static 
	unsigned int cGameObject::next_uniqueID = 1000;	// Starting at 1000, just because
