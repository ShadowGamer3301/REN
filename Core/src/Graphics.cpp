#include "Graphics.h"

#ifdef TARGET_MS_WIN32

//Minimal VRAM size in bytes required to mark adapter as suitable
#define MIN_VRAM_REQ 2147483648 

using namespace REN;

//Create macro to throw exceptions on hresult fail
#define THROW_IF_FAILED(hr) if(FAILED(hr)) throw Exception()

Graphics::Graphics(Window* pWnd)
{
#ifdef _DEBUG
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(pFactory.GetAddressOf()));
#else
	HRESULT hr = CreateDXGIFactory(IID_PPV_ARGS(pFactory.GetAddressOf()));
#endif

	THROW_IF_FAILED(hr);

	FindSuitalbeAdapter();
	if (pAdapter == NULL) throw Exception();
		
	CreateDevice();
	CreateRasterizer();
	CreateSwapChain(pWnd);
	CreateSampler();
}

Graphics::~Graphics()
{
	//Free all used interfaces

}

void Graphics::StartDraw()
{
	float color[4] = { 0.0f, 0.4f, 0.6f, 1.0f };
	pContext->ClearRenderTargetView(pRenderTarget.Get(), color);
}

void Graphics::EndDraw()
{
	pSwapChain->Present(0, 0);
}

void Graphics::FindSuitalbeAdapter()
{
	IDXGIAdapter* tempAdapter;
	UINT i = 0;

	//Go through all adapters installed in computer
	while (pFactory->EnumAdapters(i, &tempAdapter) != DXGI_ERROR_NOT_FOUND)
	{
		//Get details 
		DXGI_ADAPTER_DESC dsc;
		tempAdapter->GetDesc(&dsc);

		printf("Adapter found: %ls\n", dsc.Description);
		if (dsc.DedicatedVideoMemory > MIN_VRAM_REQ)
		{
			printf("Adapter suitable: %ls\n", dsc.Description);
			pAdapter = tempAdapter;
			return;
		}
	}
}

void Graphics::CreateDevice()
{
	D3D_FEATURE_LEVEL fl[] = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};
#ifdef _DEBUG
	HRESULT hr = D3D11CreateDevice(pAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_DEBUG, fl,
		_countof(fl), D3D11_SDK_VERSION, pDevice.GetAddressOf(), nullptr, pContext.GetAddressOf());
#else
	HRESULT hr = D3D11CreateDevice(pAdapter.Get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, fl,
		_countof(fl), D3D11_SDK_VERSION, pDevice.GetAddressOf(), nullptr, pContext.GetAddressOf());

#endif

	THROW_IF_FAILED(hr);
}

void Graphics::CreateSwapChain(Window* pWnd)
{
	int width = 0, height = 0;
	glfwGetWindowSize(pWnd->pWnd, &width, &height);
	
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd)); //Make sure that everything is set to default values
	sd.BufferCount = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Windowed = !pWnd->fs;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //Use normalized 32-bit RGBA format
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.RefreshRate.Numerator = 240; //Support refresh rates from 240 to 1 Hz
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = 0;
	sd.OutputWindow = glfwGetWin32Window(pWnd->pWnd);
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	HRESULT hr = pFactory->CreateSwapChain(pDevice.Get(), &sd, pSwapChain.GetAddressOf());
	THROW_IF_FAILED(hr);

	CreateDepthStencil(width, height);
	CreateRenderTarget(width, height);
}

void Graphics::CreateRenderTarget(int width, int height)
{
	ID3D11Texture2D* pBackBuffer;
	HRESULT hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
	THROW_IF_FAILED(hr);

	hr = pDevice->CreateRenderTargetView(pBackBuffer, 0, pRenderTarget.GetAddressOf());
	THROW_IF_FAILED(hr);

	pContext->OMSetRenderTargets(1, pRenderTarget.GetAddressOf(), pDepthView.Get());
}

void Graphics::CreateDepthStencil(int width, int height)
{
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_R24G8_TYPELESS;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	HRESULT hr = pDevice->CreateTexture2D(&descDepth, nullptr, pDepthBuffer.GetAddressOf());
	THROW_IF_FAILED(hr);

	D3D11_DEPTH_STENCIL_DESC dsDesc;
	// Depth test parameters
	dsDesc.DepthEnable = true;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;

	// Stencil test parameters
	dsDesc.StencilEnable = true;
	dsDesc.StencilReadMask = 0xFF;
	dsDesc.StencilWriteMask = 0xFF;

	// Stencil operations if pixel is front-facing
	dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Stencil operations if pixel is back-facing
	dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	hr = pDevice->CreateDepthStencilState(&dsDesc, pDepthState.GetAddressOf());
	THROW_IF_FAILED(hr);

	pContext->OMSetDepthStencilState(pDepthState.Get(), 0);

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;
	descDSV.Flags = 0;
	hr = pDevice->CreateDepthStencilView(pDepthBuffer.Get(), &descDSV, pDepthView.GetAddressOf());
}

void Graphics::CreateSampler()
{
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = pDevice->CreateSamplerState(&sampDesc, pSampler.GetAddressOf());
	THROW_IF_FAILED(hr);
}

void Graphics::CreateRasterizer()
{
	D3D11_RASTERIZER_DESC dsc = {};
	dsc.FillMode = D3D11_FILL_SOLID;
	dsc.CullMode = D3D11_CULL_BACK;
	dsc.FrontCounterClockwise = FALSE;
	dsc.DepthBias = 0;
	dsc.DepthBiasClamp = 0.0f;
	dsc.SlopeScaledDepthBias = 0.0f;
	dsc.DepthClipEnable = FALSE;
	dsc.ScissorEnable = FALSE;
	dsc.MultisampleEnable = TRUE;
	dsc.AntialiasedLineEnable = FALSE;

	HRESULT hr = pDevice->CreateRasterizerState(&dsc, pRasterizer.GetAddressOf());
	THROW_IF_FAILED(hr);

	pContext->RSSetState(pRasterizer.Get());
}


#endif