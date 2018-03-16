#pragma once


#include <d3d11.h>
#include <fstream>
#include <cstdlib>
#include "DataType.h"


using namespace std;


class Model
{
private:

public:
	Model();
	Model(const Model&);
	~Model();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, const char*, unsigned int);
	void Shutdown();
	void Render();

	void SetInstanceCount(int instanceCount) { m_instanceCount = instanceCount; };
	int GetVertexCount();
	int GetInstanceCount();
	//ID3D11ShaderResourceView** GetTextureArray();

private:
	bool InitializeBuffers(ID3D11Device*, unsigned int);
	void ShutdownBuffers();
	void RenderBuffers();

	//bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	//void ReleaseTexture();

	bool LoadModel(const char*);
	void ReleaseModel();

private:
	ID3D11DeviceContext* m_deviceContext;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_instanceBuffer;

	int m_vertexCount;
	int m_instanceCount;

	utility::ModelType* m_model;
};

