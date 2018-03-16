#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::TextureManager(const TextureManager& other)
{
}


TextureManager::~TextureManager()
{
}

bool TextureManager::Initialize(ID3D11Device* device)
{
	m_device = device;
	return true;
}

ID3D11ShaderResourceView* TextureManager::GetTexture(const WCHAR* filename1)
{
	HRESULT result;
	// Load the first texture in.
	result = DirectX::CreateDDSTextureFromFile(m_device, filename1, nullptr, &m_texture);
	if (FAILED(result))
	{
		return false;
	}
	for (std::vector<ID3D11ShaderResourceView*>::iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		if (m_texture == *it) { return *it; }
	}
	m_textures.push_back(m_texture);

	return m_texture;
}


void TextureManager::Shutdown()
{
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		m_textures.at(i)->Release();
	}
	return;
}


std::vector<ID3D11ShaderResourceView*> TextureManager::GetTextureArray()
{
	return m_textures;
}