#include "Graphics.h"
#include <d3dcompiler.h>
#include "Renderer.h"
#include <exception>


Graphics* Graphics::m_engine = nullptr;
Graphics::Graphics()
{
	try
	{
		m_render_system = new Renderer();
	}
	catch (...) { throw std::exception("Graphics Engine not created successfully."); }

	try
	{
		m_texture_manager = new TextureManager();
	}
	catch (...) { throw std::exception("TextureManager not created successfully."); }

	try
	{
		m_mesh_manager = new MeshManager();
	}
	catch (...) { throw std::exception("MeshManager not created successfully."); }

	// CREATE VERTEX BUFFER
	void* shader_bytecode = nullptr;
	size_t size_shader = 0;
	// CREATE VERTEX SHADER
	m_render_system->CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_bytecode, &size_shader);
	::memcpy(m_mesh_layout_byte_code, shader_bytecode, size_shader);
	m_mesh_layout_size = size_shader;
	m_render_system->ReleaseCompiledShader();


}

Graphics::~Graphics()
{
	Graphics::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_texture_manager;
	delete m_render_system;
	
}



Renderer* Graphics::getRenderSystem()
{
	return m_render_system;
}

TextureManager* Graphics::getTextureManager()
{
	return m_texture_manager;
}

MeshManager* Graphics::getMeshManager()
{
	return m_mesh_manager;
}

void Graphics::getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size)
{
	*byte_code = m_mesh_layout_byte_code;
	*size = m_mesh_layout_size;

}


Graphics* Graphics::get()
{
	return m_engine;
}

void Graphics::create()
{
	if (Graphics::m_engine) throw std::exception("Graphics Engine is already created.");
	Graphics::m_engine = new Graphics();

	
}

void Graphics::release()
{
	if (!Graphics::m_engine) throw std::exception("Graphics Engine is already released.");
	delete Graphics::m_engine;
}

