#include "ResourceManager.h"
#include <filesystem>


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

sResourcePtr ResourceManager::createResouceFromFile(const wchar_t* file_path)
{
	std::wstring full_path = std::filesystem::absolute(file_path);
	auto it = m_map_Resouces.find(full_path);
	if (it != m_map_Resouces.end())
		return it->second;


	Resource* raw_res = this->createResourceFromFileConcrete(full_path.c_str());

	if(raw_res)
	{
		sResourcePtr res(raw_res);
		m_map_Resouces[full_path] = res;
		return res;
	}

	return nullptr;
}
