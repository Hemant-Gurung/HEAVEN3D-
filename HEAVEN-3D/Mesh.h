#pragma once
#include "PixelShader.h"
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
class Mesh:public Resource
{
public:
	Mesh(const wchar_t* full_path) ;
	~Mesh() ;

	const sVertexBufferPtr& getVertexBuffer();
	const sIndexBufferPtr& getIndexBuffer();
private:
	sVertexBufferPtr m_vertex_buffer;
	sIndexBufferPtr m_index_buffer;
	std::string wide_string_to_string(const std::wstring& wide_string);
private:
	friend class DeviceContext;
};

