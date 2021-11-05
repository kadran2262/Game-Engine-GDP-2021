#include <graphics/OpenGL.h>
#include <iostream>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

extern int windowWidth;
extern int windowHeight;
extern std::vector<cGameObject*> gameObjects;;
extern std::vector<cGameObject*>::iterator selectedGameObject;

namespace nGraphics {
	//globals
	GLFWwindow* gWindow = 0;
	Camera* gCamera = 0;
	cSimpleShader* gShader = 0;
	cVAOManager* gVAOManager = 0;
	cModelLoader* gModelLoader = 0;
	cLightManager* gLightManager = 0;
	std::map<std::string, cMesh*> gMeshes;

	void DrawObject(cGameObject* pCurrentObject)
	{	
		GLint matModel_UL = glGetUniformLocation(gShader->GetProgramId(), "matModel");

		glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(pCurrentObject->GetModelMatrix()));


		// Calcualte the inverse transpose of the model matrix and pass that...
		// Stripping away scaling and translation, leaving only rotation
		// Because the normal is only a direction, really
		GLint matModelIT_UL = glGetUniformLocation(gShader->GetProgramId(), "matModelInverseTranspose");
		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(pCurrentObject->GetModelMatrix()));
		glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));




		// Find the location of the uniform variable newColour
		GLint newColour_location = glGetUniformLocation(gShader->GetProgramId(), "newColour");

		glUniform3f(newColour_location,
			pCurrentObject->GetModelColour().r,
			pCurrentObject->GetModelColour().g,
			pCurrentObject->GetModelColour().b);

		GLint diffuseColour_UL = glGetUniformLocation(gShader->GetProgramId(), "diffuseColour");
		glUniform4f(diffuseColour_UL,
			pCurrentObject->GetModelColour().r,
			pCurrentObject->GetModelColour().g,
			pCurrentObject->GetModelColour().b,
			pCurrentObject->GetModelColour().a);	// 

		GLint specularColour_UL = glGetUniformLocation(gShader->GetProgramId(), "specularColour");
		glUniform4f(specularColour_UL,
			pCurrentObject->GetModelColour().r,// R
			pCurrentObject->GetModelColour().g,// G
			pCurrentObject->GetModelColour().b,// B
			pCurrentObject->GetModelColour().a);	// Specular "power" (how shinny the object is)
						// 1.0 to really big (10000.0f)


//uniform vec4 debugColour;
//uniform bool bDoNotLight;
		GLint debugColour_UL = glGetUniformLocation(gShader->GetProgramId(), "debugColour");
		GLint bDoNotLight_UL = glGetUniformLocation(gShader->GetProgramId(), "bDoNotLight");
		//if (pCurrentObject->GetWirefram())
		//{
		//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		//	glUniform4f(debugColour_UL,
		//		pCurrentObject->GetModelColour().r,
		//		pCurrentObject->GetModelColour().g,
		//		pCurrentObject->GetModelColour().b,
		//		pCurrentObject->GetModelColour().a);
		//		
		//	glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
		//}
		//
		//else{	// Regular object (lit and not wireframe)
			
			glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);			// SOLID
		//}
		

		
		{
			glEnable(GL_DEPTH_TEST);						// Turn ON depth test
		}

		
		{
			glEnable(GL_DEPTH);								// Write to depth buffer
		}



		sModelDrawInfo drawInfo;
		
		if (gVAOManager->FindDrawInfoByModelName(pCurrentObject->GetMeshName(), drawInfo))
		{
			glBindVertexArray(drawInfo.VAO_ID);
			glDrawElements(GL_TRIANGLES,
				drawInfo.numberOfIndices,
				GL_UNSIGNED_INT,
				0);
			glBindVertexArray(0);
		}

		return;
	} // DrawObject;


	void Callback_WindowResize(GLFWwindow* window, int width, int height)
	{
		if (gCamera)
		{
			gCamera->WindowResize(width, height);
		}
	}

	void Callback_Error(int error, const char* description)
	{
		fprintf(stderr, "Error: %s\n", description);
	}

	bool Init() {

		glfwSetErrorCallback(Callback_Error);
		if (!glfwInit())
		{
			exit(EXIT_FAILURE);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	
		gWindow = glfwCreateWindow(windowWidth, windowHeight, "Simple example", NULL, NULL);

		if (!gWindow)
		{
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		// the camera
		if (gCamera)
		{
			gCamera->WindowResize(windowWidth, windowHeight);
		}
		
		glfwSetWindowSizeCallback(gWindow, Callback_WindowResize);
		glfwPollEvents();
		

		glfwSetKeyCallback(gWindow, key_callback);
		glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(gWindow, mouse_callback);
		glfwMakeContextCurrent(gWindow);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSwapInterval(1);

		gVAOManager = new cVAOManager();

		gModelLoader = new cModelLoader();

		gLightManager = new cLightManager();

		gShader = new cSimpleShader();
		if (!gShader->Load())
		{
			std::cout << "Shader failed to load" << std::endl;
			delete gShader;
			gShader = 0;
			return false;
		}
		
		



		glEnable(GL_DEPTH);			// Write to the depth buffer
		glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

		return true;
	}

	void Render() {

	}

	bool WindowShouldClose() {
		return glfwWindowShouldClose(gWindow) != 0;
	}

	void Focus() {
		if (gWindow)
		{
			glfwFocusWindow(gWindow);
		}
	}

	void SetCamera(Camera* camera) {
		gCamera = camera;
	}

	void SetWindowTitle(const std::string& title) {
		glfwSetWindowTitle(gWindow, title.c_str());
	}

	void Shutdown() {
		if (gCamera) {
			gCamera = 0;
		}
		if (gVAOManager) {
			gVAOManager = 0;
		}
		if (gModelLoader) {
			gModelLoader = 0;
		}
		if (gShader) {
			gShader = 0;
		}
		if (gLightManager) {
			gLightManager = 0;
		}

		glfwTerminate();
		if (gWindow)
		{
			gWindow = 0;
		}
	}
}