#include "DeviceContext.h"

#include "ConstantBuffer.h"
#include "SwapChain.h"
#include "VertexBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "IndexBuffer.h"
#include <exception>

#include "Texture.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext,Renderer* system)
	:m_system(system),
	m_DeviceContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
{
	m_DeviceContext->Release();

}

bool DeviceContext::ClearRenderTargetColor(const sSwapChainPtr& swapchain, float red, float green, float blue, float alpha)
{
	FLOAT clear_color[] =
	{
		red,green,blue,alpha
	};
	m_DeviceContext->ClearRenderTargetView(swapchain->m_RenderTarget, clear_color);
	m_DeviceContext->ClearDepthStencilView(swapchain->m_depthSV,D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,1,0);
	m_DeviceContext->OMSetRenderTargets(1, &swapchain->m_RenderTarget,swapchain->m_depthSV);
	return true;
}


void DeviceContext::DrawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_DeviceContext->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::DrawStriangleStrip(UINT vertexCount, UINT start_vertex_index)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_DeviceContext->Draw(vertexCount, start_vertex_index);
}

void DeviceContext::DrawIndexTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location)
{
	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_DeviceContext->DrawIndexed(index_count, start_index_location, start_vertex_index);
}

void DeviceContext::SetViewPortSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp ={};
	vp.Width = (FLOAT)width;
	vp.Height = (FLOAT)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void DeviceContext::SetVetexBuffer(const sVertexBufferPtr& vertex_buffer)
{
	UINT stride = vertex_buffer->m_size_vertex;
	UINT offset = 0;

	m_DeviceContext->IASetVertexBuffers(0, 1, &vertex_buffer->m_Buffer, &stride, &offset);
	m_DeviceContext->IASetInputLayout(vertex_buffer->m_Layout);
	
}

void DeviceContext::setVertexShader(const sVertexShaderPtr& vertex_shader)
{
	m_DeviceContext->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(const sPixelShaderPtr& pixel_shader)
{
	m_DeviceContext->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setConstantBuffer(const sVertexShaderPtr& vertex_shader, const sConstantBufferPtr& buffer)
{
	m_DeviceContext->VSSetConstantBuffers(0, 1, &buffer->m_Buffer);
}

void DeviceContext::setConstantBuffer(const sPixelShaderPtr& pixel_shader, const sConstantBufferPtr& buffer)
{
	m_DeviceContext->PSSetConstantBuffers(0, 1, &buffer->m_Buffer);

}

void DeviceContext::setIndexBuffer(const sIndexBufferPtr& index_buffer)
{
	m_DeviceContext->IASetIndexBuffer(index_buffer->m_Buffer, DXGI_FORMAT_R32_UINT, 0);
}

void DeviceContext::setTexture(const sVertexShaderPtr& vertex_shader, const sTexturePtr& texture)
{
	m_DeviceContext->VSSetShaderResources(0, 1, &texture->m_shader_res_view);
}

void DeviceContext::setTexture(const sPixelShaderPtr& vertex_shader, const sTexturePtr& texture)
{
	m_DeviceContext->PSSetShaderResources(0, 1, &texture->m_shader_res_view);

}
