#include "VertexShader.h"
#include "Renderer.h"
#include <exception>

VertexShader::VertexShader(const void* shader_byte_code, size_t byte_code_size,Renderer* system)
	:m_system(system)
{
	if (FAILED(m_system->m_d3d_Device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
	{
		throw std::exception("VertesShader:: not created correctly");

	}
	
}

VertexShader::~VertexShader()
{
	m_vs->Release();
}
