#pragma once

#include <GLCommon.h>


namespace nGraphics
{
	class cSimpleShader
	{
	public:
		cSimpleShader();
		virtual ~cSimpleShader();

		// load it up!
		bool Load();
		// deletes and cleans up stuff
		// dtor will call this
		void Close();
		void Bind();

		// successfully loaded, good to use
		inline bool IsLoaded() const { return mProgramId != 0; }
		inline GLuint GetProgramId() const { return mProgramId; }

		//set up per-frame uniforms
		inline void SetUniform_ViewMatrix(const float* m) { glUniformMatrix4fv(mUniformId_ViewMatrix, 1, GL_FALSE, m); }
		inline void SetUniform_ProjectionMatrix(const float* m) { glUniformMatrix4fv(mUniformId_ProjectionMatrix, 1, GL_FALSE, m); }
		inline void SetUniform_EyePosition(const float* v) { glUniform3fv(mUniformId_EyePosition, 1, v); }
	private:

		GLuint mProgramId;
		GLuint mUniformId_ModelMatrix;
		GLuint mUniformId_ViewMatrix;
		GLuint mUniformId_ProjectionMatrix;
		GLuint mUniformId_ModelColor;
		GLuint mUniformId_EyePosition;

	};
}