#include <FileLoader/cFileLoader.h>
#include <iostream>
JSONFile::JSONFile(string filename) {
	fopen_s(&m_pFile, filename.c_str(), "rb");
	rapidjson::FileReadStream is(m_pFile, m_readBuffer, sizeof(m_readBuffer));
	m_pDoc.ParseStream(is);
	m_currentObject = m_pDoc.MemberBegin();
	fclose(m_pFile);
}

JSONFile::~JSONFile() {

	fclose(m_pFile);
}

bool JSONFile::LoadJSONFile(string& const filename)
{
	
	fopen_s(&m_pFile,filename.c_str(),"rb");
	rapidjson::FileReadStream is(m_pFile, m_readBuffer, sizeof(m_readBuffer));
	m_pDoc.ParseStream(is);
	fclose(m_pFile);
	return true;
}

float JSONFile::GetFloatFromJSON(string value)
{
	//find the specific projectile we are looking for
	
	rapidjson::Value::ConstMemberIterator itr;

	itr = m_currentObject->value.FindMember(value.c_str());

	if (itr != m_pDoc.MemberEnd()) {
		return itr->value.GetFloat();
	}

	return 0.0f;
}


glm::vec3 JSONFile::GetVec3FromJSON(string value) {

	rapidjson::Value::ConstMemberIterator itr;

	itr = m_currentObject->value.FindMember(value.c_str());

	if (itr != m_pDoc.MemberEnd() && itr->value.GetArray().Size() == 3) {
		return glm::vec3(itr->value.GetArray()[0].GetFloat()
			, itr->value.GetArray()[1].GetFloat()
			, itr->value.GetArray()[2].GetFloat());

	}

	return glm::vec3(0.0f);
}

glm::vec4 JSONFile::GetVec4FromJSON(string value) {

	rapidjson::Value::ConstMemberIterator itr;

	itr = m_currentObject->value.FindMember(value.c_str());

	if (itr != m_pDoc.MemberEnd() && itr->value.GetArray().Size() == 4) {
		return glm::vec4(itr->value.GetArray()[0].GetFloat()
						, itr->value.GetArray()[1].GetFloat()
						, itr->value.GetArray()[2].GetFloat()
						, itr->value.GetArray()[3].GetFloat());
			
	}

	return glm::vec4(0.0f);
}

string JSONFile::GetStringFromJSON(string value)
{
	//find the specific projectile we are looking for

	
	rapidjson::Value::ConstMemberIterator itr;
	
	itr = m_currentObject->value.FindMember(value.c_str());

	if (itr != m_pDoc.MemberEnd()) {
		return itr->value.GetString();
	}

	return "";
}

bool JSONFile::GetNextObject()
{
	if (m_currentObject == m_pDoc.MemberEnd())
		return false;
	else
		m_currentObject++;

	return true;
}



