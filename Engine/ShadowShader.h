#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
#include "DataType.h"
#include "ShaderLoader.h"
using namespace std;


class ShadowShaderClass
{
private:
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX lightView;
		DirectX::XMMATRIX lightProjection;
	};

	struct LightBufferType
	{
		DirectX::XMFLOAT4 ambientColor;
		DirectX::XMFLOAT4 diffuseColor;
		DirectX::XMFLOAT3 lightDirection;
		float padding;
	};

public:
	ShadowShaderClass();
	ShadowShaderClass(const ShadowShaderClass&);
	~ShadowShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*
		, int, int
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, ID3D11ShaderResourceView*
		, ID3D11ShaderResourceView*
		, DirectX::XMFLOAT3
		, DirectX::XMFLOAT4
		, DirectX::XMFLOAT4
		);

private:
	bool InitializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, DirectX::XMMATRIX&
		, ID3D11ShaderResourceView*
		, ID3D11ShaderResourceView*
		, DirectX::XMFLOAT3
		, DirectX::XMFLOAT4
		, DirectX::XMFLOAT4
		);	
	void RenderShader(ID3D11DeviceContext*, int, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleStateWrap;
	ID3D11SamplerState* m_sampleStateClamp;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_lightBuffer;
};

