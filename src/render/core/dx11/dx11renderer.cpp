#include <Windows.h>

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include "core/filesystem/file.h"
#include "core/filesystem/ifilesystem.h"
#include "core/filesystem/vfs.h"

#include "render/core/dx11/dx11renderer.h"
#include "render/core/dx11/dx11buffer.h"
#include "render/core/dx11/dx11texture.h"
#include "render/core/dx11/dx11profiler.h"
#include "render/core/dx11/dx11shadermanager.h"
#include "render/core/dx11/dx11shaderprogram.h"
#include "render/core/dx11/dx11samplerstate.h"

#include "d3dcompiler.h"
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace solunar
{

// Globals
DX11Renderer* g_dx11Renderer = nullptr; 
HWND g_hWnd;

void debugSaveBytecode(ID3DBlob* blob)
{
	IFile* file = g_fileSystem->openFile("/data/shaders/test.bin", false);

	file->write(blob->GetBufferPointer(), blob->GetBufferSize());

	delete file;
}

DX11Renderer::DX11Renderer(GLFWwindow* window)
{
	g_dx11Renderer = this;

	g_hWnd = glfwGetWin32Window(window);

	RECT clientRect;
	GetClientRect(g_hWnd, &clientRect);

	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (clientRect.right - clientRect.left);
	sd.BufferDesc.Height = (clientRect.bottom - clientRect.top);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 75;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	const D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	UINT deviceCreationFlags = 0;
#ifdef _DEBUG
	deviceCreationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, deviceCreationFlags,
		&featureLevel, 1, D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device,
		NULL, &m_deviceContext);

	ID3D11Texture2D* backBuffer = NULL;
	m_swapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)&backBuffer);

	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView);
	backBuffer->Release();

	// create depth texture
	D3D11_TEXTURE2D_DESC depthTextureDesc;
	memset(&depthTextureDesc, 0, sizeof(depthTextureDesc));
	depthTextureDesc.Width = sd.BufferDesc.Width;
	depthTextureDesc.Height = sd.BufferDesc.Height;
	depthTextureDesc.MipLevels = 1;
	depthTextureDesc.ArraySize = 1;
	depthTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTextureDesc.SampleDesc.Count = 1;
	depthTextureDesc.SampleDesc.Quality = 0;
	depthTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTextureDesc.CPUAccessFlags = 0;
	depthTextureDesc.MiscFlags = 0;
	m_device->CreateTexture2D(&depthTextureDesc, NULL, &m_depthTexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	memset(&depthStencilViewDesc, 0, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = depthTextureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	m_device->CreateDepthStencilView(m_depthTexture, &depthStencilViewDesc, &m_depthStencilView);

	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);

	D3D11_VIEWPORT vp;
	vp.Width = (float)sd.BufferDesc.Width;
	vp.Height = (float)sd.BufferDesc.Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_deviceContext->RSSetViewports(1, &vp);

	dx11ProfilerInit();
}

DX11Renderer::~DX11Renderer()
{
	dx11ProfilerShutdown();

	m_deviceContext->OMSetRenderTargets(0, NULL, NULL);

	m_depthStencilView->Release();
	m_depthTexture->Release();

	m_renderTargetView->Release();

	m_deviceContext->Release();
	m_device->Release();

	m_swapChain->Release();

	g_hWnd = nullptr;
	g_dx11Renderer = nullptr;
}

void DX11Renderer::init()
{
}

void DX11Renderer::shutdown()
{
}

void DX11Renderer::beginFrame()
{
	dx11BeginMarker(D3DCOLOR_XRGB(255, 0, 0), L"DX11Renderer::beginFrame");

	float clearColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, clearColor);
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	dx11EndMarker();
}

void DX11Renderer::endFrame()
{
	dx11BeginMarker(D3DCOLOR_XRGB(255, 0, 0), L"DX11Renderer::endFrame");

	m_swapChain->Present(0, 0);

	dx11EndMarker();
}

void DX11Renderer::draw(uint32_t verticesCount, uint32_t startVertexLocation)
{
	m_deviceContext->Draw(verticesCount, startVertexLocation);
}

void DX11Renderer::drawIndexed(uint32_t indicesCount, uint32_t startIndexLocation, int32_t baseVertexLocation)
{
	m_deviceContext->DrawIndexed(indicesCount, startIndexLocation, baseVertexLocation);
}

void DX11Renderer::setPrimitiveMode(PrimitiveMode primitiveMode)
{
	// #TODO: convert PrimitiveMode to D3D11_PRIMITIVE_TOPOLOGY
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

IBuffer* DX11Renderer::createBuffer(const BufferDesc& bufferDesc, const SubresourceDesc& subresourceDesc)
{
	return new DX11Buffer(bufferDesc, subresourceDesc);
}

void DX11Renderer::setVertexBuffer(IBuffer* buffer, uint32_t stride, uint32_t offset)
{
	if (buffer)
	{
		ID3D11Buffer* d3d11Buffer = ((DX11Buffer*)buffer)->getBuffer();
		m_deviceContext->IASetVertexBuffers(0, 1, &d3d11Buffer, &stride, &offset);
	}
	else
	{
		m_deviceContext->IASetVertexBuffers(0, 0, NULL, &stride, &offset);
	}
}

void DX11Renderer::setIndexBuffer(IBuffer* buffer)
{
	if (buffer)
	{
		ID3D11Buffer* d3d11Buffer = ((DX11Buffer*)buffer)->getBuffer();
		m_deviceContext->IASetIndexBuffer(d3d11Buffer, DXGI_FORMAT_R16_UINT, 0);
	}
	else
	{
		m_deviceContext->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	}
}

IShaderProgram* DX11Renderer::createShaderProgram(const ShaderCreationDesc& vertexShaderDesc, const ShaderCreationDesc& pixelShaderDesc, const std::vector<ShaderInputLayout>& inputLayouts)
{
	return new DX11ShaderProgram((const char*)vertexShaderDesc.m_bytecode, (const char*)pixelShaderDesc.m_bytecode, inputLayouts);
}

void DX11Renderer::setShaderProgram(IShaderProgram* shaderProgram)
{
	DX11ShaderProgram* dx11shaderProgram = (DX11ShaderProgram*)shaderProgram;
	if (dx11shaderProgram)
		DX11ShaderManager::setShaderProgram(dx11shaderProgram);
	else
		DX11ShaderManager::setShaderProgram(nullptr);
}

void DX11Renderer::setConstantBuffer(uint32_t slot, IBuffer* constantBuffer)
{
	if (constantBuffer)
	{
		ID3D11Buffer* d3d11Buffer = ((DX11Buffer*)constantBuffer)->getBuffer();
		m_deviceContext->VSSetConstantBuffers(slot, 1, &d3d11Buffer);
		m_deviceContext->PSSetConstantBuffers(slot, 1, &d3d11Buffer);
	}
	else
	{
		m_deviceContext->VSSetConstantBuffers(slot, 0, NULL);
		m_deviceContext->PSSetConstantBuffers(slot, 0, NULL);
	}
}

ITexture2D* DX11Renderer::createTexture2D(const TextureDesc& textureDesc, const SubresourceDesc& subresourceDesc)
{
	return new DX11Texture2D(textureDesc, subresourceDesc);
}

void DX11Renderer::setTexture2D(uint32_t slot, ITexture2D* texture)
{
	DX11Texture2D* nativeTexture = (DX11Texture2D*)texture;
	if (nativeTexture)
	{
		ID3D11ShaderResourceView* textureView = nativeTexture->getShaderResourceView();
		m_deviceContext->PSSetShaderResources(0, 1, &textureView);

		// #TODO: Sampler objects ???
		//m_deviceContext->PSSetSamplers(0, 1, &g_samplerState);
	}
	else
	{
		m_deviceContext->PSSetShaderResources(0, 0, nullptr);
	}
}

ISamplerState* DX11Renderer::createSamplerState(const SamplerDesc& samplerDesc)
{
	return new DX11SamplerState(samplerDesc);
}

void DX11Renderer::setSamplerState(int slot, ISamplerState* samplerState)
{
	DX11SamplerState* nativeSampler = (DX11SamplerState*)samplerState;
	if (nativeSampler && nativeSampler->getSamplerState())
	{
		ID3D11SamplerState* dx11SamlplerState = nativeSampler->getSamplerState();
		m_deviceContext->PSSetSamplers(slot, 1, &dx11SamlplerState);
	}
	else
	{
		m_deviceContext->PSSetSamplers(slot, 0, nullptr);
	}
}

IRenderer* createDX11Renderer(GLFWwindow* window)
{
	return new DX11Renderer(window);
}

}