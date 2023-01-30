#pragma once

#include <d3d11.h>
#include "header.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	
public:
	sSwapChainPtr CreateSwapChain(HWND hwnd, UINT width, UINT height);
	sDeviceContextPtr GetImmediateDeviceContext();
	sVertexBufferPtr CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader);
	sVertexShaderPtr createVertexShader(const void* shader_byte_code, size_t byte_code_size);
	sConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
	sIndexBufferPtr createIndexBuffer(void* list_indices, UINT size_indices);
	sPixelShaderPtr createPixelShader(const void* shader_byte_code, size_t byte_code_size);

public:


public:
	bool CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool ReleaseCompiledShader();
	// simple shaders


public:
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	IDXGIFactory* m_dxgi_Factory;
private:
	ID3D11Device* m_d3d_Device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D11DeviceContext* m_imm_Context;
	IDXGIDevice* m_dxgi_Device;
	IDXGIAdapter* m_dxgi_Adapter;
	
	sDeviceContextPtr m_imm_device_context;
private:
	friend  class SwapChain;
	friend class VertexBuffer;
	friend class VertexShader;
	friend class PixelShader;
	friend class ConstantBuffer;
	friend class IndexBuffer;
	friend class Texture;

private:
	ID3DBlob* m_blob = nullptr;


	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

};

