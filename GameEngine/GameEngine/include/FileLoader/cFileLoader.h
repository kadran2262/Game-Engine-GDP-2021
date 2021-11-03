#pragma once

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <GLCommon.h>

#include <string>
using std::string;

class JSONFile {
	rapidjson::Document m_pDoc;
	FILE* m_pFile;
	char m_readBuffer[65536];
	rapidjson::Value::ConstMemberIterator m_currentObject;

public:
	JSONFile(string filename);
	~JSONFile();

	bool LoadJSONFile(string& const filename);
	float GetFloatFromJSON(string value);
	glm::vec3 GetVec3FromJSON(string value);
	glm::vec4 GetVec4FromJSON(string value);
	string GetStringFromJSON(string value);
	bool GetNextObject();

};