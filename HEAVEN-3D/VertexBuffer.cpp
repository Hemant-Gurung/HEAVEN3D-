#include "VertexBuffer.h"
#include "Renderer.h"
#include <exception>


VertexBuffer::VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, UINT size_byte_shader,Renderer* system)
	:m_system(system),
	m_Layout(0),
	m_Buffer(0)
{
	
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_vertices;

	m_size_list = size_list;
	m_size_vertex = size_vertex;


	HRESULT res = m_system->m_d3d_Device->CreateBuffer(&buff_desc, &init_data, &m_Buffer);

	if (FAILED(res))
	{
		throw std::exception("VertexBuffer:: not created correctly");
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		// SEMANTIC NAME	-	SEMANTIC INDEX	-	FORMAT	-	INPUTSLOT	-	ALIGNED BYTE OFFSET	-	INPUT SLOT CLASS	-	INSTANCE DATA SETP RATE
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}// OFFSET OF 12 BYTES = SUM OF SIZE OF POSITION
	};

	UINT size_layout = ARRAYSIZE(layout);
	//m_system->m_d3d_Device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_Layout);
	res = m_system->m_d3d_Device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_Layout);
	if (FAILED(res))
	{
		throw std::exception("VertexBuffer:: InputLayout not created correctly");

	}

	
}

VertexBuffer::~VertexBuffer()
{
	m_Buffer->Release();
	m_Layout->Release();
}


UINT VertexBuffer::GetVertexSize()
{
	return this->m_size_list;
}
