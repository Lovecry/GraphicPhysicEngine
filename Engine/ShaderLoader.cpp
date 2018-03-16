#include "ShaderLoader.h"

using namespace utility;

HRESULT ShaderLoader::vertexPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11VertexShader** outVertexSahder, ID3DBlob** outBlob)
{
	HRESULT result = S_OK;

	ID3DBlob* vertexShaderBlob = nullptr;
	result = D3DReadFileToBlob(fileName, &vertexShaderBlob);
	if (FAILED(result))
	{
		return result;
	}

	// Creazione dello shader.
	result = pd3d11Device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, outVertexSahder);

	if (outBlob != nullptr)
		*outBlob = vertexShaderBlob;
	else
		vertexShaderBlob->Release();

	return result;
}

HRESULT ShaderLoader::pixelPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11PixelShader** outPixelSahder, ID3DBlob** outBlob)
{
	HRESULT result = S_OK;

	ID3DBlob* pixelShaderBlob = nullptr;
	result = D3DReadFileToBlob(fileName, &pixelShaderBlob);
	if (FAILED(result))
	{
		return result;
	}

	// Creazione dello shader.
	result = pd3d11Device->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, outPixelSahder);

	if (outBlob != nullptr)
		*outBlob = pixelShaderBlob;
	else
		pixelShaderBlob->Release();

	return result;
}

HRESULT ShaderLoader::geometryPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11GeometryShader** outGeometrySahder, ID3DBlob** outBlob)
{
	HRESULT result = S_OK;

	ID3DBlob* geometryShaderBlob = nullptr;
	result = D3DReadFileToBlob(fileName, &geometryShaderBlob);
	if (FAILED(result))
	{
		return result;
	}

	// Creazione dello shader.
	result = pd3d11Device->CreateGeometryShader(geometryShaderBlob->GetBufferPointer(), geometryShaderBlob->GetBufferSize(), nullptr, outGeometrySahder);

	if (outBlob != nullptr)
		*outBlob = geometryShaderBlob;
	else
		geometryShaderBlob->Release();

	return result;
}

HRESULT ShaderLoader::createInputLayout(const LPCWSTR vsFileName, ID3D11Device* pd3d11Device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], const unsigned int descSize, ID3D11InputLayout** outInputLayout)
{
	HRESULT result = S_OK;
	ID3DBlob* vertexShaderBlob = nullptr;
	result = D3DReadFileToBlob(vsFileName, &vertexShaderBlob);
	if (FAILED(result))
	{
		return result;
	}

	// Creazione dell'input layout per il vertex shader.
	result = createInputLayout(vertexShaderBlob, pd3d11Device, layoutDesc, descSize, outInputLayout);
	vertexShaderBlob->Release();

	return result;
}

HRESULT ShaderLoader::createInputLayout(ID3DBlob* blob, ID3D11Device* pd3d11Device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], const unsigned int descSize, ID3D11InputLayout** outInputLayout)
{
	HRESULT result = S_OK;

	// Creazione dell'input layout per il vertex shader.
	result = pd3d11Device->CreateInputLayout(layoutDesc, descSize, blob->GetBufferPointer(), blob->GetBufferSize(), outInputLayout);

	return result;
}


