#pragma once
#include <memory>

class SwapChain;
class VertexBuffer;
class DeviceContext;
class VertexShader;
class PixelShader;
class ConstantBuffer;
class IndexBuffer;
class Renderer;
class Graphics;
class Resource;
class ResourceManager;
class Texture;
class TextureManager;
class MeshManager;
class Mesh;




typedef std::shared_ptr<SwapChain> sSwapChainPtr;
typedef std::shared_ptr<DeviceContext> sDeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> sVertexBufferPtr;
typedef std::shared_ptr<VertexShader> sVertexShaderPtr;
typedef std::shared_ptr<PixelShader> sPixelShaderPtr;
typedef std::shared_ptr<ConstantBuffer> sConstantBufferPtr;
typedef std::shared_ptr<IndexBuffer> sIndexBufferPtr;
typedef std::shared_ptr<Resource> sResourcePtr;
typedef std::shared_ptr<Texture> sTexturePtr;
typedef std::shared_ptr<Mesh> sMeshPtr;









