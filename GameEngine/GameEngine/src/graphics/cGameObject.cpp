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
		
		mFriendlyName = def.FriendlyName;
		mVisible = def.Visible;
		mWireframe = def.Wireframe;
		
		mRotation = def.Rotation;
		mPosition = def.Position;
		mScale = def.Scale;

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


	void cGameObject::MoveObject(const glm::vec3& movement) {
		
		glm::vec3 newPos = mPosition + movement;
		mPosition = newPos;

		mModelMatrix = glm::eulerAngleXYZ(mRotation.x, mRotation.y, mRotation.z);
		mModelMatrix = glm::translate(mModelMatrix, newPos);
		mModelMatrix = glm::scale(mModelMatrix, mScale);
	}
	void cGameObject::RotateObject(const glm::vec3& rotation) {

		glm::vec3 newRotation = mRotation + rotation;
		mRotation = newRotation;

		mModelMatrix = glm::eulerAngleXYZ(newRotation.x, newRotation.y, newRotation.z);
		mModelMatrix = glm::translate(mModelMatrix, mPosition);
		mModelMatrix = glm::scale(mModelMatrix, mScale);
	}

	// this variable is static, so common to all objects.
	// When the object is created, the unique ID is set, and 
	//	the next unique ID is incremented
	//static 
	unsigned int cGameObject::next_uniqueID = 1000;	// Starting at 1000, just because
