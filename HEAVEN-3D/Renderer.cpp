#include "Renderer.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include <d3dcompiler.h>
#include <dxgi.h>
#include "ConstantBuffer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "IndexBuffer.h"
#include <exception>

Renderer::Renderer()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
	D3D_DRIVER_TYPE_HARDWARE,
	D3D_DRIVER_TYPE_WARP,
	D3D_DRIVER_TYPE_REFERENCE
	};

	UINT num_driver_types = ARRAYSIZE(driver_types);
	D3D_FEATURE_LEVEL feature_levels[] =
	{
	D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	//ID3D11DeviceContext* immContext;
	for (UINT driverTypeIndex = 0; driverTypeIndex < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driverTypeIndex], NULL, NULL,
			feature_levels,
			num_feature_levels,
			D3D11_SDK_VERSION,
			&m_d3d_Device
			, &m_feature_level
			, &m_imm_Context);

		if (SUCCEEDED(res))
		{
			break;
			++driverTypeIndex;
		}

	}

	if (FAILED(res))
		throw std::exception("Renderer:: not created correctly");


	m_imm_device_context = std::make_shared<DeviceContext>(m_imm_Context, this);

	m_d3d_Device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_Device);
	m_dxgi_Device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_Adapter);
	m_dxgi_Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_Factory);



}

Renderer::~Renderer()
{
	
	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_Factory->Release();
	m_dxgi_Adapter->Release();
	m_dxgi_Device->Release();

	m_d3d_Device->Release();
}


sSwapChainPtr Renderer::CreateSwapChain(HWND hwnd, UINT width, UINT height)
{
	sSwapChainPtr sc = nullptr;
	try
	{
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
	}
	catch (...){}

	return sc;

}

bool Renderer::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3D10Blob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)error_blob->Release();
		return false;
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();


	return true;
}

bool Renderer::ReleaseCompiledShader()
{
	if (m_blob)m_blob->Release();
	return true;
}

bool Renderer::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3D10Blob* error_blob = nullptr;
	if (!SUCCEEDED(::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob)error_blob->Release();
		return false;
	}
	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();


	return true;

}

sPixelShaderPtr Renderer::createPixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	
	sPixelShaderPtr ps = nullptr;
	try
	{
		ps = std::make_shared<PixelShader> (shader_byte_code, byte_code_size, this);
	}
	catch (...)
	{
		throw std::exception("asdfa");
	}

	return ps;
}

sDeviceContextPtr Renderer::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

sVertexBufferPtr Renderer::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader)
{
	
	sVertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>  (list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch (...) {}
	return vb;
}

sVertexShaderPtr Renderer::createVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	sVertexShaderPtr vs = nullptr;
	try
	{
		vs = std::make_shared<VertexShader> (shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return vs;
	 
}

sConstantBufferPtr Renderer::createConstantBuffer(void* buffer, UINT size_buffer)
{
	 
	sConstantBufferPtr cb = nullptr;
	try
	{
		cb = std::make_shared<ConstantBuffer> (buffer, size_buffer, this);
	}
	catch (...) {}
	return cb;

}

sIndexBufferPtr Renderer::createIndexBuffer(void* list_indices, UINT size_indices)
{
	 
	sIndexBufferPtr ib = nullptr;
	try
	{
		ib = std::make_shared<IndexBuffer>  (list_indices, size_indices, this);
	}
	catch (...) {}
	return ib;
}
