#pragma once
#include <d3d11.h>
#include "header.h"

class VertexBuffer
{
public:
	VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader,Renderer* m_system);
	~VertexBuffer();

	UINT GetVertexSize();
private:
	UINT  m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_Buffer;
	ID3D11InputLayout* m_Layout;
	Renderer* m_system = nullptr;

private:
	friend class DeviceContext;
};

