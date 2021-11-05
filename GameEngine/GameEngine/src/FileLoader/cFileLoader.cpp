#include <FileLoader/cFileLoader.h>
#include <iostream>
#include <graphics/cGameObject.h>
#include <fstream>
#include "rapidjson/filewritestream.h"
#include <rapidjson/prettywriter.h>

using namespace rapidjson;

extern std::vector<cGameObject*> gameObjects;

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
	
	rapidjson::Value::ConstMemberIterator itr;
	
	itr = m_currentObject->value.FindMember(value.c_str());

	if (itr != m_pDoc.MemberEnd()) {
		return itr->value.GetString();
	}

	return "";
}

bool JSONFile::SaveJSONFile(string filename)
{
	
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	std::string x;
	std::ofstream myFile(filename);

	writer.StartObject();
	x = s.GetString();
	myFile << x;
	myFile << "\n";
	s.Clear();
	for (cGameObject* object : gameObjects) {
		writer.Key(object->GetFriendlyName().c_str());
		writer.StartObject(); 

		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.Key("meshname");                
		writer.String(object->GetMeshName().c_str());  
		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.Key("friendlyname");
		writer.String(object->GetFriendlyName().c_str());
		

		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.Key("position");

		writer.StartArray(); 
		writer.Double(object->GetPosition().x); 
		writer.Double(object->GetPosition().y); 
		writer.Double(object->GetPosition().z);
		writer.EndArray();

		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.String("rotation");
		writer.StartArray();
		writer.Double(object->GetRotation().x);
		writer.Double(object->GetRotation().y);
		writer.Double(object->GetRotation().z);
		writer.EndArray();

		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.String("scale");
		writer.StartArray();
		writer.Double(object->GetScale().x);
		writer.Double(object->GetScale().y);
		writer.Double(object->GetScale().z);
		writer.EndArray();

		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";

		writer.String("modelcolour");
		writer.StartArray();
		writer.Double(object->GetModelColour().r);
		writer.Double(object->GetModelColour().g);
		writer.Double(object->GetModelColour().b);
		writer.Double(object->GetModelColour().a);
		writer.EndArray();
		
		writer.EndObject();
		x = s.GetString();
		s.Clear();
		myFile << x;
		myFile << "\n";
	}
	writer.EndObject();

	x = s.GetString();
	
		myFile << x;

	


	return false;
}

bool JSONFile::GetNextObject()
{
	m_currentObject++;
	if (m_currentObject == m_pDoc.MemberEnd())
		return false;
	
	return true;
}



