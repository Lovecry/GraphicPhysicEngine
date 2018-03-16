#include "ShaderManager.h"


ShaderManager::ShaderManager()
{
	m_TextureShader = 0;
	m_ColorShader = 0;
	m_DepthShader = 0;
	m_ShadowShader = 0;
	m_MultiTextureShader = 0;
}


ShaderManager::ShaderManager(const ShaderManager& other)
{
}


ShaderManager::~ShaderManager()
{
}


bool ShaderManager::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd)
{
	bool result;
	m_deviceContext = deviceContext;

	// Create and initialize the texture shader object.
	m_TextureShader = new TextureShader;
	if (!m_TextureShader)	{	return false;	}
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)	{ return false; }
	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize  the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)	{ return false; }
	result = m_ShadowShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)	{ return false; }
	result = m_DepthShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and Initialize the multitexture shader object.
	m_MultiTextureShader = new MultiTextureShader;
	if (!m_MultiTextureShader)	{	return false;	}
	result = m_MultiTextureShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the multitexture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the Particle shader object.
	m_ParticleShader = new ParticleShader;
	if (!m_ParticleShader)	{ return false; }
	result = m_ParticleShader->Initialize(device, hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ShaderManager::Shutdown()
{
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}
	if (m_MultiTextureShader)
	{
		m_MultiTextureShader->Shutdown();
		delete m_MultiTextureShader;
		m_MultiTextureShader = 0;
	}
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}
	return;
}


bool ShaderManager::RenderTextureShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix,
	ID3D11ShaderResourceView* texture)
{
	bool result;
	
	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)	{	return false;	}

	return true;
}

bool ShaderManager::RenderColorShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix){
	bool result;

	// Render the model using the texture shader.
	result = m_ColorShader->Render(m_deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderShadowShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix, DirectX::XMMATRIX& lightViewMatrix, DirectX::XMMATRIX& lightProjectionMatrix, ID3D11ShaderResourceView* texture, ID3D11ShaderResourceView* depthMapTexture,
	DirectX::XMFLOAT3 lightDirection, DirectX::XMFLOAT4 ambientColor, DirectX::XMFLOAT4 diffuseColor)
{
	bool result;

	// Render the model using the texture shader.
	result = m_ShadowShader->Render(m_deviceContext, vertexCount, instanceCount , worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, lightProjectionMatrix, texture, depthMapTexture, lightDirection, ambientColor, diffuseColor);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderDepthShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix){
	bool result;

	// Render the model using the texture shader.
	result = m_DepthShader->Render(m_deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderMultiTextureShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView** texture)
{
	bool result;

	// Render the model using the texture shader.
	result = m_MultiTextureShader->Render(m_deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)	{ return false; }

	return true;
}

bool ShaderManager::RenderParticleShader(int vertexCount, int instanceCount, DirectX::XMMATRIX& worldMatrix, DirectX::XMMATRIX& viewMatrix, DirectX::XMMATRIX& projectionMatrix, ID3D11ShaderResourceView* texture)
{
	bool result;

	// Render the model using the Particle shader.
	result = m_ParticleShader->Render(m_deviceContext, vertexCount, instanceCount, worldMatrix, viewMatrix, projectionMatrix, texture);
	if (!result)	{ return false; }

	return true;
}