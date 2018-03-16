#pragma once

#include <DirectXMath.h>

namespace utility
{
#pragma pack(push, 16)
	struct Transformations
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
		DirectX::XMFLOAT4 cameraPosition; // WORLD
	};
#pragma pack(pop)

	// Proprieta' Sorgente luminosa puntiforme
	const unsigned int MaxLights = 5;
#pragma pack(push, 16)
	struct Lights
	{
		DirectX::XMFLOAT4 position[MaxLights];
		DirectX::XMFLOAT4 color[MaxLights];
		DirectX::XMFLOAT4 ambient[MaxLights];
		DirectX::XMFLOAT4 attenuation[MaxLights];
		int usedLights; // quante luci sono utilizzate.
		float padding[3];
	};
#pragma pack(pop)

#pragma pack(push, 16)
	struct Material
	{
		DirectX::XMFLOAT4 ambiental;
		DirectX::XMFLOAT4 diffusive;
		DirectX::XMFLOAT4 specular;
		DirectX::XMFLOAT4 emissive;
		float shininess;
		float padding[3];
	};
#pragma pack(pop)

	struct PositionNormal
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
	};

	struct PositionNormalTex2
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 texCoord;
	};

	struct PositionTangentSpaceTex2
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT3 tangent;
		DirectX::XMFLOAT3 biNormal;
		DirectX::XMFLOAT2 texCoord;
	};

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
		DirectX::XMFLOAT3 normal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct InstanceType
	{
		DirectX::XMFLOAT3 position;
	};

}
