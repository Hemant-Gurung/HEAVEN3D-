#include "SwapChain.h"
#include "Renderer.h"
#include <exception>

#include "Graphics.h"

SwapChain::SwapChain(HWND hwnd, UINT width, UINT height,Renderer* system)
	:m_system(system)
{
	ID3D11Device* device = m_system->m_d3d_Device;
	
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	
	// create swapchain for window indicated by HWND PARAMETER
	
	HRESULT result = m_system->m_dxgi_Factory->CreateSwapChain(device, &desc, &m_dxgi_SwapChain);
	
	if (FAILED(result))
	{
		throw std::exception("Swapchain not created correctly");

	}

	ID3D11Texture2D* buffer;
	result = m_dxgi_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);
	if (FAILED(result))
	{
		throw std::exception("SwapChain::Buffer not correctly imported.");

	}

	result = device->CreateRenderTargetView(buffer, NULL, &m_RenderTarget);
	buffer->Release();

	if (FAILED(result))
	{
		throw std::exception("Swap::chain:Render target not correctly created");

	}


	// DEPTH BUFFER
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = width;
	tex_desc.Height = height;
	tex_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.MipLevels = 1;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.MiscFlags = 0;
	tex_desc.ArraySize = 1;
	tex_desc.CPUAccessFlags = 0;

	HRESULT hr = device->CreateTexture2D(&tex_desc, nullptr, &buffer);
	if(FAILED(hr))
	{
		throw std::exception("Swap::chain:TX2D not correctly created");
	}

	hr = device->CreateDepthStencilView(buffer, NULL, &m_depthSV);
	if (FAILED(hr))
	{
		throw std::exception("Swap::chain:depth stencil view not correctly created");
	}
}

SwapChain::~SwapChain()
{
	m_dxgi_SwapChain->Release();
	m_RenderTarget->Release();

}



bool SwapChain::present(bool vsync)
{
	m_dxgi_SwapChain->Present(vsync, NULL);
	return true;
}