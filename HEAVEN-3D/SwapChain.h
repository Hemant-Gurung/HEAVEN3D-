#pragma once
#include <d3d11.h>
#include "header.h"

class SwapChain
{
public:
	SwapChain(HWND hwnd, UINT width, UINT height,Renderer* m_system) ;
	~SwapChain();

	bool present(bool vsync);

private:
	IDXGISwapChain* m_dxgi_SwapChain;
	ID3D11RenderTargetView* m_RenderTarget;
	Renderer* m_system = nullptr;
	ID3D11DepthStencilView* m_depthSV = nullptr;
private:
	friend class DeviceContext;
};

