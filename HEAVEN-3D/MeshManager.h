#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
#include "ResourceManager.h"
#include "header.h"
class MeshManager :public ResourceManager
{
public:
	MeshManager();
	~MeshManager();
	sMeshPtr createMeshFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
private:
	std::unordered_map<std::wstring, sResourcePtr> m_map_Resouces;

};

