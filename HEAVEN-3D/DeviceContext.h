#pragma once
#include <d3d11.h>

#include "header.h"

class DeviceContext
{
public:
	DeviceContext(ID3D11DeviceContext* deviceContext, Renderer* m_system);
	~DeviceContext();
	bool ClearRenderTargetColor(const sSwapChainPtr& swapChain,float red, float green, float blue, float alpha);
	
	void DrawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void DrawStriangleStrip(UINT vertexCount, UINT start_vertex_index);
	void DrawIndexTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void SetViewPortSize(UINT width, UINT height);
	void SetVetexBuffer(const sVertexBufferPtr& vertex_buffer);
	void setVertexShader(const sVertexShaderPtr& vertex_shader);
	void setPixelShader(const sPixelShaderPtr& vertex_shader);

	void setConstantBuffer(const sVertexShaderPtr& vertex_shader, const sConstantBufferPtr& buffer);
	void setConstantBuffer(const sPixelShaderPtr& vertex_shader, const sConstantBufferPtr& buffer);

	void setIndexBuffer(const sIndexBufferPtr& index_buffer);

	void setTexture(const sVertexShaderPtr& vertex_shader, const sTexturePtr& buffer);
	void setTexture(const sPixelShaderPtr& vertex_shader, const sTexturePtr& buffer);

private:
	ID3D11DeviceContext* m_DeviceContext;
	Renderer* m_system = nullptr;

private:
	friend class ConstantBuffer;
};

