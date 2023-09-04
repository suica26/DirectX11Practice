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

	// �O�p�`�̕`��
	{
		// 1���_�̌`��(����͍��W����)
		struct VertexType
		{
			DirectX::XMFLOAT3 Pos;
		};
		// �O�p�`����邽�߁A���_��3���
		VertexType v[3] = {
			{{0, 0, 0}},
			{{1, -1, 0}},
			{{-1, -1, 0}},
		};

		// ���_�o�b�t�@�쐬
		// �쐬����o�b�t�@�̎g�p�����߂�
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;		// �f�o�C�X�Ƀo�C���h����Ƃ��̎��
		vbDesc.ByteWidth = sizeof(v);						// �쐬����o�b�t�@�̃o�C�g�T�C�Y
		vbDesc.MiscFlags = 0;								// ���̑��t���O
		vbDesc.StructureByteStride = 0;						// �\�����o�b�t�@�̏ꍇ�A���̍\���̂̃T�C�Y
		vbDesc.Usage = D3D11_USAGE_DEFAULT;					// �쐬����o�b�t�@�̎g�p�@
		vbDesc.CPUAccessFlags = 0;

		// ��̎g�p��n���Ē��_�o�b�t�@������Ă��炤
		ComPtr<ID3D11Buffer> vb;
		D3D11_SUBRESOURCE_DATA initData = { &v[0], sizeof(v), 0 };		// �������ރf�[�^
		D3D.m_device->CreateBuffer(&vbDesc, &initData, &vb);			// ���_�o�b�t�@�̍쐬

		// ==================================================��������`��=========================================================

		// ���_�o�b�t�@��`��Ŏg����悤�ɃZ�b�g����
		UINT stride = sizeof(VertexType);
		UINT offset = 0;
		D3D.m_deviceContext->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &stride, &offset);
		// �v���~�e�B�u�E�g�|���W�[���Z�b�g
		D3D.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �V�F�[�_�[���Z�b�g
		D3D.m_deviceContext->VSSetShader(D3D.m_spriteVS.Get(), 0, 0);
		D3D.m_deviceContext->PSSetShader(D3D.m_spritePS.Get(), 0, 0);
		D3D.m_deviceContext->IASetInputLayout(D3D.m_spriteInputLayout.Get());

		// �`����s
		D3D.m_deviceContext->Draw(3, 0);
	}

	D3D.m_swapChain->Present(1, 0);
}