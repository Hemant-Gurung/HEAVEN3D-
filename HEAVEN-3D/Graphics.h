#pragma once

#include <d3d11.h>
#include "header.h"
#include "TextureManager.h"
#include "MeshManager.h"

class Graphics
{
private:
	Graphics() ;
	~Graphics();

	
public:
	static Graphics* get();
	static void create();
	static void release();
	Renderer* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);
private:
	Renderer* m_render_system = nullptr;
	static Graphics* m_engine;
	TextureManager* m_texture_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;


private:
	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};

