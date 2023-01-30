#include "ConstantBuffer.h"

#include "DeviceContext.h"
#include "Renderer.h"
#include <exception>

ConstantBuffer::ConstantBuffer(void* buffer, UINT size_buffer,Renderer* system)
	:m_system(system)
{
	
	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_buffer;
	buff_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = buffer;

	HRESULT res = m_system->m_d3d_Device->CreateBuffer(&buff_desc, &init_data, &m_Buffer);

	if(FAILED(res))
	{
		throw std::exception("Constant Buffer not created correctly");
	}
}

ConstantBuffer::~ConstantBuffer()
{
	if (m_Buffer)m_Buffer->Release();
}


void ConstantBuffer::update(sDeviceContextPtr context, void* buffer)
{
	context->m_DeviceContext->UpdateSubresource(this->m_Buffer, NULL, NULL, buffer, NULL, NULL);
}
