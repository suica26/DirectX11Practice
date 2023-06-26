#include "Direct3D.h"

#include <Windows.h>

bool Direct3D::Initialize(HWND hWnd, int width, int height)
{
	ComPtr<IDXGIFactory> factory;

	if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(&factory))))
	{
		return false;
	}

	UINT creationFlags = 0;

#ifdef _DEBUG
	// DEBUGビルド時はDirect3Dのデバッグを有効にする
	// (すごく重いが細かいエラーがわかる)
	creationFlags != D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,	// Direct3D 11.1	ShaderModel5
		D3D_FEATURE_LEVEL_11_0,	// Direct3D 11		ShaderModel5
		D3D_FEATURE_LEVEL_10_1,	// Direct3D 10.1	ShaderModel4
		D3D_FEATURE_LEVEL_10_0,	// Direct3D 10.0	ShaderModel4
		D3D_FEATURE_LEVEL_9_3,	// Direct3D 9.3		ShaderModel3
		D3D_FEATURE_LEVEL_9_2,	// Direct3D 9.2		ShaderModel3
		D3D_FEATURE_LEVEL_9_1,	// Direct3D 9.1		ShaderModel3
	};

	// デバイスとデバイスコンテキストを作成
	D3D_FEATURE_LEVEL futureLevel;
	if (FAILED(D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		creationFlags,
		featureLevels,
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&m_device,
		&futureLevel,
		&m_deviceContext)))
	{
		return false;
	}

	//=========================================================
	// スワップチェイン作成(フロントバッファに表示可能なバックバッファを持つもの)
	//=========================================================
	DXGI_SWAP_CHAIN_DESC scDesc = {};		// スワップチェーンの設定データ
	scDesc.BufferDesc.Width = width;
	scDesc.BufferDesc.Height = height;



	return true;
}