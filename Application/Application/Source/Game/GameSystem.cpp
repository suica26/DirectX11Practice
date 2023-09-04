#include "framework.h"
#include "GameSystem.h"
#include "Source/DirectX/Direct3D.h"

void GameSystem::Initialize()
{

}

void GameSystem::Execute()
{
	float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
	D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);

	// 三角形の描画
	{
		// 1頂点の形式(今回は座標だけ)
		struct VertexType
		{
			DirectX::XMFLOAT3 Pos;
		};
		// 三角形を作るため、頂点を3つ作る
		VertexType v[3] = {
			{{0, 0, 0}},
			{{1, -1, 0}},
			{{-1, -1, 0}},
		};

		// 頂点バッファ作成
		// 作成するバッファの使用を決める
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// デバイスにバインドするときの種類
		vbDesc.ByteWidth = sizeof(v);						// 作成するバッファのバイトサイズ
		vbDesc.MiscFlags = 0;								// その他フラグ
		vbDesc.StructureByteStride = 0;						// 構造化バッファの場合、その構造体のサイズ
		vbDesc.Usage = D3D11_USAGE_DEFAULT;					// 作成するバッファの使用法
		vbDesc.CPUAccessFlags = 0;

		// 上の使用を渡して頂点バッファを作ってもらう
		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };		// 書き込むデータ
		D3D.m_device->CreateBuffer(&vbDesc, &initData, &vb);			// 頂点バッファの作成

		// ==================================================ここから描画=========================================================

		// 頂点バッファを描画で使えるようにセットする
		UINT stride = sizeof(VertexType);
		UINT offset = 0;
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);
		// プリミティブ・トポロジーをセット
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// シェーダーをセット
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());

		// 描画実行
		D3D.m_deviceContext->Draw(3, 0);
	}

	D3D.m_swapChain->Present(1, 0);
}