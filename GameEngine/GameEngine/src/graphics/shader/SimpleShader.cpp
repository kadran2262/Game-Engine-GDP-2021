#include <graphics/shader/SimpleShader.h>
#include <graphics/shader/LoadShader.h>
#include <iostream>

namespace nGraphics {

	cSimpleShader::cSimpleShader() :
		mProgramId(0),
		mUniformId_ModelMatrix(0),
		mUniformId_ViewMatrix(0),
		mUniformId_ProjectionMatrix(0),
		mUniformId_EyePosition(0),
		mUniformId_ModelColor(0)
	{

	}

	cSimpleShader::~cSimpleShader()
	{
		Close();
	}

	bool cSimpleShader::Load() {
		if (IsLoaded()) return true; // all good
		mProgramId = LoadShader("assets/shaders/vertexShader01.glsl", "assets/shaders/fragmentShader01.glsl");
		if (mProgramId == 0)
		{
			std::cout << "shader couldn't load" << std::endl;
			return false;
		}
		// per frame
		mUniformId_ViewMatrix = glGetUniformLocation(mProgramId, "matView");
		mUniformId_ProjectionMatrix = glGetUniformLocation(mProgramId, "matProj");
		mUniformId_EyePosition = glGetUniformLocation(mProgramId, "eyeLocation");
		// per item
		mUniformId_ModelMatrix = glGetUniformLocation(mProgramId, "matModel");
		mUniformId_ModelColor = glGetUniformLocation(mProgramId, "ModelColor");
		return true;
	}

	void cSimpleShader::Bind()
	{
		glUseProgram(mProgramId);
	}

	void cSimpleShader::Close()
	{
		if (mProgramId == 0) return;
		glDeleteShader(mProgramId);
		mProgramId = 0;
		mUniformId_ModelMatrix = 0;
		mUniformId_ModelColor = 0;
		mUniformId_ViewMatrix = 0;
		mUniformId_ProjectionMatrix = 0;
		mUniformId_EyePosition = 0;
	}

}