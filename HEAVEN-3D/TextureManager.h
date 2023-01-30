#pragma once
#include <unordered_map>
#include <string>
#include "Resource.h"
#include "ResourceManager.h"
#include "header.h"
class TextureManager:public ResourceManager
{
public:
	TextureManager();
	~TextureManager();
	sTexturePtr createTextureFromFile(const wchar_t* file_path);
protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* file_path);
private:
	std::unordered_map<std::wstring, sResourcePtr> m_map_Resouces;

};
