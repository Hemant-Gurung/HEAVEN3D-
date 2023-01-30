#pragma once
#include <d3d11.h>
#include "header.h"

class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size,Renderer* m_system);
	
	~VertexShader();

	

private:
	ID3D11VertexShader* m_vs;
	Renderer* m_system = nullptr;
private:
	friend class Renderer;
	friend class DeviceContext;
};

