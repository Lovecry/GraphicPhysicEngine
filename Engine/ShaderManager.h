#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include "TextureShader.h"
#include "ShadowShader.h"
#include "DepthShader.h"
#include "ColorShader.h"
#include "MultiTextureShader.h"
#include "ParticleShader.h"
#include "DataType.h"


class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager&);
	~ShaderManager();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND);
	void Shutdown();

	bool RenderTextureShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView*);
	bool RenderColorShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&);
	bool RenderShadowShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4);
	bool RenderDepthShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&);
	bool RenderMultiTextureShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView**);
	bool RenderParticleShader(int, int, DirectX::XMMATRIX&, DirectX::XMMATRIX&, DirectX::XMMATRIX&, ID3D11ShaderResourceView*);

private:
	TextureShader* m_TextureShader;
	ColorShaderClass* m_ColorShader;
	ShadowShaderClass* m_ShadowShader;
	DepthShaderClass* m_DepthShader;
	MultiTextureShader* m_MultiTextureShader;
	ParticleShader* m_ParticleShader;

	ID3D11DeviceContext* m_deviceContext;
	
};