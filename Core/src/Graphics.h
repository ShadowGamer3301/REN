#pragma once
#include "Framework.h"
#include "Window.h"
#include "Exception.h"

#ifdef TARGET_MS_WIN32

namespace REN
{
	class Graphics
	{
	public:
		Graphics(Window* pWnd);
		~Graphics();

		Graphics(const Graphics&) = delete;
		Graphics operator=(const Graphics&) = delete;

		void StartDraw();
		void EndDraw();

	private:
		void FindSuitalbeAdapter();
		void CreateDevice();
		void CreateSwapChain(Window* pWnd);
		void CreateRenderTarget(int width, int height);
		void CreateDepthStencil(int width, int height);
		void CreateSampler();
		void CreateRasterizer();

	private:
		//Other data
		static const constexpr UINT mNumBuffers = 2; //Number of video buffers

		//DXGI interfaces
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter;
		Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
		
		//D3D11 interfaces
		Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pRenderTarget;
		Microsoft::WRL::ComPtr<ID3D11RasterizerState> pRasterizer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepthView;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> pSampler;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthBuffer;
	};


}

#endif