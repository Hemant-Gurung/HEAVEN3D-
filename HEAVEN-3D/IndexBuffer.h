#pragma once

#include <d3d11.h>

#include "header.h"

class IndexBuffer
{
public:
	IndexBuffer(void* list_indices, UINT size_indices,Renderer* m_system);
	~IndexBuffer();
	UINT GetIndexSize();
private:
	UINT m_size_list;
private:
	ID3D11Buffer* m_Buffer;
	Renderer* m_system = nullptr;

private:
	friend class DeviceContext;
};

