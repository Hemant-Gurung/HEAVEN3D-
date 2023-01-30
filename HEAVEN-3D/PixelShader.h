#pragma once
#include <d3d11.h>
#include "header.h"

class PixelShader
{
public:
	PixelShader(const void* shader_byte_code, size_t byte_code_size,Renderer* m_system);

	~PixelShader();



private:
	ID3D11PixelShader* m_ps;
	Renderer* m_system = nullptr;

private:
	friend class Renderer;
	friend class DeviceContext;
};

