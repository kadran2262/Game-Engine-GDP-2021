#include <graphics/lights/cLightManager.h>
#include <GLCommon.h>
cLightManager* cLightManager::m_pLightManager = nullptr;

cLightManager::cLightManager()
{
}

cLightManager::~cLightManager()
{
	delete m_pLightManager;
}

cLightManager* cLightManager::GetLightManager()
{
	if (!(m_pLightManager)) {
		m_pLightManager = new cLightManager();
	}
	return m_pLightManager;
}

void cLightManager::MoveLight(Light_Movement direction)
{
	if (direction == LIGHT_FORWARD)
		GetCurrentLight()->position.z += 1.f;
	if (direction == LIGHT_BACKWARD)
		GetCurrentLight()->position.z -= 1.f;
	if (direction == LIGHT_LEFT)
		GetCurrentLight()->position.x -= 1.f;
	if (direction == LIGHT_RIGHT)
		GetCurrentLight()->position.x += 1.f;
	if (direction == LIGHT_UP)
		GetCurrentLight()->position.y += 1.f;
	if (direction == LIGHT_DOWN)
		GetCurrentLight()->position.y -= 1.f;
}

void cLightManager::ToggleLight()
{
	if (GetCurrentLight()->param2.x == 1)
		GetCurrentLight()->param2.x = 0;
	else
		GetCurrentLight()->param2.x = 1;
}

void cLightManager::ChangeLightType(std::string lightType, int index)
{
}

void cLightManager::LoadUniformLocations(int shaderID)
{
	
	std::string number;
	for (int i = 0; i < m_vecLights.size(); i++) {
		number = std::to_string(i);
		
		m_vecLights[i]->position_UniLoc = glGetUniformLocation(shaderID, ("theLights["+number+"].position").c_str());
		m_vecLights[i]->diffuse_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].diffuse").c_str());
		m_vecLights[i]->specular_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].specular").c_str());
		m_vecLights[i]->atten_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].atten").c_str());
		m_vecLights[i]->direction_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].direction").c_str());
		m_vecLights[i]->param1_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].param1").c_str());
		m_vecLights[i]->param2_UniLoc = glGetUniformLocation(shaderID, ("theLights[" + number + "].param2").c_str());
	}

	 
}

void cLightManager::CopyLightValuesToShader(void)
{
	for (int i = 0; i < m_vecLights.size(); i++) {
		glUniform4f(
			m_vecLights[i]->position_UniLoc,
			m_vecLights[i]->position.x,
			m_vecLights[i]->position.y,
			m_vecLights[i]->position.z,
			m_vecLights[i]->position.a
		);

		glUniform4f(
			m_vecLights[i]->diffuse_UniLoc, 
			m_vecLights[i]->diffuse.x, 
			m_vecLights[i]->diffuse.y,
			m_vecLights[i]->diffuse.z,
			m_vecLights[i]->diffuse.w);	// White

		glUniform4f(
			m_vecLights[i]->specular_UniLoc, 
			m_vecLights[i]->specular.x, 
			m_vecLights[i]->specular.y,
			m_vecLights[i]->specular.z,
			m_vecLights[i]->specular.w);	// White

		glUniform4f(
			m_vecLights[i]->atten_UniLoc,
			m_vecLights[i]->atten.x,  // constant attenuation
			m_vecLights[i]->atten.y,  // Linear 
			m_vecLights[i]->atten.z,	// Quadratic 
			m_vecLights[i]->atten.w);	// Distance cut off

		glUniform4f(
			m_vecLights[i]->direction_UniLoc,
			m_vecLights[i]->direction.x,
			m_vecLights[i]->direction.y,
			m_vecLights[i]->direction.z,
			m_vecLights[i]->direction.a);

		glUniform4f(
			m_vecLights[i]->param1_UniLoc,
			m_vecLights[i]->param1.x,		// 0
			m_vecLights[i]->param1.y,		// -1
			m_vecLights[i]->param1.z,		// 0
			m_vecLights[i]->param1.w);

		glUniform4f(
			m_vecLights[i]->param2_UniLoc,
			m_vecLights[i]->param2.x,
			m_vecLights[i]->param2.y,
			m_vecLights[i]->param2.z,
			m_vecLights[i]->param2.a);
	}

}

void sLight::SetLinearAttenuation(float newLinAtten)
{
}

void sLight::SetPosition(glm::vec3 newPosition)
{
}

void sLight::SetSpecularHighlight(glm::vec3 rgbColour, float power)
{
}

void sLight::SetLightType( std::string typeAsString )
{
	// TODO:

	return;
}

void sLight::SetLightType( sLight::eLightType lightType )
{
	switch ( lightType )
	{
	case sLight::POINT_LIGHT:
		this->param1.x = 0.0f;		// Point
		break;
	case sLight::SPOT_LIGHT:
		this->param1.x = 1.0f;		// Spot
		break;
	case sLight::DIRECTIONAL_LIGHT:
		this->param1.x = 2.0f;		// Directional
		break;
	default:
		// Make point if we don't know
		// (shouldn't happen)
		this->param1.x = 0.0f;		// Point
		break;
	};

	return;
}

void sLight::SetSpotConeAngles( float innerAngleDegrees, float outerAngleDegrees )
{
	//if ( outerAngleDegrees > innerAngleDegrees )
	//{	// Switch them
	//	float temp = innerAngleDegrees;
	//	innerAngleDegrees = outerAngleDegrees;
	//	outerAngleDegrees = temp;
	//}

	//	glm::vec4 param1;		// x = lightType, y = inner angle, z = outer angle, w = TBD
	this->param1.y = innerAngleDegrees;
	this->param1.z = outerAngleDegrees;

	return;
}

void sLight::SetRelativeDirection( glm::vec3 relDirection )
{
	// To set the vec4 that's being passed
	this->direction = glm::vec4( relDirection, 1.0f );
	return;
}

void sLight::SetRelativeDirectionByEulerAngles( glm::vec3 directionAngle )
{
	// Take the angles and make a quaternion out of them
	// Use a mat4x4 x vec4 tranformation (just like the shader or in physics)
	// Use the final xyz location to send to SetRelativeDirectionByLookAt()

	// Ta-Da!

	return;
}

void sLight::SetRelativeDirectionByLookAt( glm::vec3 pointInWorldXYZ )
{
	// The vector from what I'm looking at to where I am, then normalize

	glm::vec3 lookVector = pointInWorldXYZ - glm::vec3(this->position);

	lookVector = glm::normalize( lookVector );

	this->SetRelativeDirection( lookVector );

	return;
}

void cLightManager::GetNextLight()
{
	if (GetCurrentLight()->FriendlyName == m_vecLights[m_vecLights.size()-1]->FriendlyName) {
		m_pCurrentLight = m_vecLights.begin();
	}
	else
	m_pCurrentLight++;
}

sLight* cLightManager::GetCurrentLight()
{
	
	return *m_pCurrentLight;
}


