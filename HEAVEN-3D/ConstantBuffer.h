#pragma once
#include <d3d11.h>
#include "header.h"
class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer,Renderer* m_system);
	~ConstantBuffer();
	void update(sDeviceContextPtr context,void* buffer);
private:
	ID3D11Buffer* m_Buffer;
	Renderer* m_system = nullptr;

private:
	friend class DeviceContext;
};

