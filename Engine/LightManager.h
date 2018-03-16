#pragma once


#include <DirectXMath.h>
#include <crtdbg.h>


class LightManager
{
public:
	LightManager();
	LightManager(const LightManager&);
	~LightManager();

	void * operator new(size_t nSize, size_t nAlignment);
	void operator delete(void *pObject, size_t nAlignment);

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetPosition(float, float, float);
	void SetLookAt(float, float, float);

	DirectX::XMFLOAT4 GetAmbientColor();
	DirectX::XMFLOAT4 GetDiffuseColor();
	DirectX::XMVECTOR GetPosition();

	void GenerateViewMatrix();
	void GetViewMatrix(DirectX::XMMATRIX&);

	void GenerateOrthoMatrix(float, float, float);
	void GetOrthoMatrix(DirectX::XMMATRIX&);

	void SetDirection(float, float, float);
	DirectX::XMFLOAT3 GetDirection();

private:
	DirectX::XMFLOAT4 m_ambientColor;
	DirectX::XMFLOAT4 m_diffuseColor;

	DirectX::XMVECTOR m_position;
	DirectX::XMVECTOR m_lookAt;

	DirectX::XMMATRIX m_viewMatrix;
	DirectX::XMMATRIX m_orthoMatrix;
	DirectX::XMFLOAT3 m_direction;
};