#include "MeshManager.h"
#include "Mesh.h"
MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

sMeshPtr MeshManager::createMeshFromFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Mesh>(createResouceFromFile(file_path));
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* file_path)
{
	Mesh* tex = nullptr;
	try
	{
		tex = new Mesh(file_path);
	}
	catch (...) {}

	return tex;
}
