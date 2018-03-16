#pragma once


#include "DDSTextureLoader.h"
#include <vector>


class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();

	bool Initialize(ID3D11Device*);
	void Shutdown();
	ID3D11ShaderResourceView* GetTexture(const WCHAR*);
	std::vector<ID3D11ShaderResourceView*> GetTextureArray();

private:
	ID3D11Device* m_device;
	ID3D11ShaderResourceView* m_texture;
	std::vector<ID3D11ShaderResourceView*> m_textures; 
};

