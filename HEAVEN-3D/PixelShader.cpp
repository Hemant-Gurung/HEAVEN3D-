#include "PixelShader.h"

#include "Renderer.h"
#include <exception>

PixelShader::PixelShader(const void* shader_byte_code, size_t byte_code_size,Renderer* system)
	:m_system(system)
{
	// Create Vertex Shader
	if (!SUCCEEDED(m_system->m_d3d_Device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
	{
		throw std::exception("Index Buffer not created correctly");
	}
	
}

PixelShader::~PixelShader()
{
	m_ps->Release();
}
