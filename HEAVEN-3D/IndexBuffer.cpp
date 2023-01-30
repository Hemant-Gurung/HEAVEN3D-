#include "IndexBuffer.h"
#include "Renderer.h"
#include <exception>


IndexBuffer::IndexBuffer(void* list_indices, UINT size_list,Renderer* system)
	:m_system(system),
	m_Buffer(0)
{

	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = 4 * size_list;
	buff_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = list_indices;

	m_size_list = size_list;


	HRESULT res = m_system->m_d3d_Device->CreateBuffer(&buff_desc, &init_data, &m_Buffer);

	if (FAILED(res))
		throw std::exception("Index Buffer not created correctly");

}

IndexBuffer::~IndexBuffer()
{
	m_Buffer->Release();
}


UINT IndexBuffer::GetIndexSize()
{
	return this->m_size_list;
}
