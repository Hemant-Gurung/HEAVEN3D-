#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
#include "header.h"
class ResourceManager
{
public:
	ResourceManager() ;
	~ResourceManager();

	sResourcePtr createResouceFromFile(const wchar_t* filepath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path)=0;
private:
	std::unordered_map<std::wstring, sResourcePtr> m_map_Resouces;
	
};

