#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <string>
#include <D3Dcompiler.h>


namespace utility
{

	class ShaderLoader
	{
	public:
		static HRESULT vertexPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11VertexShader** outVertexSahder, ID3DBlob** outBlob = nullptr);
		static HRESULT pixelPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11PixelShader** outPixelSahder, ID3DBlob** outBlob = nullptr);
		static HRESULT geometryPreBuiltLoad(const LPCWSTR fileName, ID3D11Device* pd3d11Device, ID3D11GeometryShader** outGeometrySahder, ID3DBlob** outBlob = nullptr);
		static HRESULT createInputLayout(const LPCWSTR vsFileName, ID3D11Device* pd3d11Device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], const unsigned int descSize, ID3D11InputLayout** outInputLayout);
		static HRESULT createInputLayout(ID3DBlob* blob, ID3D11Device* pd3d11Device, D3D11_INPUT_ELEMENT_DESC layoutDesc[], const unsigned int descSize, ID3D11InputLayout** outInputLayout);
	};

};
