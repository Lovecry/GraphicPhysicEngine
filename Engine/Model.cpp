#include "model.h"


Model::Model()
{
	m_instanceBuffer = 0;
	m_model = 0;
	m_instanceCount = 1;
}


Model::Model(const Model& other)
{
}


Model::~Model()
{
}


bool Model::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const char* modelFilename, unsigned int moreInstances)
{
	bool result;
	m_deviceContext = deviceContext;
	// Load in the model data,
	result = LoadModel(modelFilename);
	if (!result)	{	return false;	}

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device, moreInstances);
	if (!result)	{	return false;	}

	// Load the texture for this model.
	/*result = LoadTextures(device, textureFilename1, textureFilename2);
	if (!result)	{	return false;	}*/

	return true;
}


void Model::Shutdown()
{
	// Release the model texture.
	//ReleaseTexture();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void Model::Render()
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers();

	return;
}

int Model::GetVertexCount()
{
	return m_vertexCount;
}


int Model::GetInstanceCount()
{
	return m_instanceCount;
}

//
//ID3D11ShaderResourceView** Model::GetTextureArray()
//{
//	return m_TextureArray->GetTextureArray();
//}


bool Model::InitializeBuffers(ID3D11Device* device, unsigned int moreInstances)
{
	utility::VertexType* vertices;

	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, instanceData;
	utility::InstanceType* instances;
	m_instanceCount += moreInstances;
	HRESULT result;
	int i;

	// Create the vertex array.
	vertices = new utility::VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for (i = 0; i<m_vertexCount; i++)
	{
		vertices[i].position = DirectX::XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = DirectX::XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = DirectX::XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		//indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(utility::VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))	{	return false;	}

	delete[] vertices;
	vertices = 0;

	// Set the number of instances in the array.

	// Create the instance array.
	instances = new utility::InstanceType[m_instanceCount];
	if (!instances)
	{
		return false;
	}

	instances[0].position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < m_instanceCount-1; i++)
	{// Load the instance array with data.
		instances[i + 1].position = DirectX::XMFLOAT3((float)(rand() % 60 + (-30)), 0.f, (float)(rand() % 60 + (-30))); //crea le copie del modello in posizione random su x ed z
	}

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(utility::InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete[] instances;
	instances = 0;

	return true;
}


void Model::ShutdownBuffers()
{
	// Release the Instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void Model::RenderBuffers()
{
	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(utility::VertexType);
	strides[1] = sizeof(utility::InstanceType);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	m_deviceContext->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return;
}


bool Model::LoadModel(const char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.
	fin.open(filename);

	// If it could not open the file then exit.
	if (fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new utility::ModelType[m_vertexCount];
	if (!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while (input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for (i = 0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


void Model::ReleaseModel()
{
	if (m_model)
	{
		delete[] m_model;
		m_model = 0;
	}

	return;
}