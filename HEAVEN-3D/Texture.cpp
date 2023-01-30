#include "Texture.h"
#include <DirectXTex.h>
#include "Graphics.h"
#include "Renderer.h"

Texture::Texture(const wchar_t* full_path):Resource(full_path)
{
	DirectX::ScratchImage image_data;
	// it will parse any image file
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);
	if(SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(
			Graphics::get()->getRenderSystem()->m_d3d_Device,
			image_data.GetImages(),
			image_data.GetImageCount(),
			image_data.GetMetadata(),
			&m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		Graphics::get()->getRenderSystem()->m_d3d_Device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
	}
	else
	{
		throw std::exception("Texture not created successfully");
	}
}

Texture::~Texture()
{
	m_texture->Release();
	m_texture = nullptr;

}
