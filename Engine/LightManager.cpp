#include "LightManager.h"

void * LightManager::operator new(size_t nSize, size_t nAlignment)

{
	if (((nAlignment)&(nAlignment - 1)) == 0)
	return (void *)_aligned_malloc_dbg(nSize, nAlignment, __FILE__, __LINE__);
	else
		return (void *)NULL;

}

void LightManager::operator delete(void *pObject, size_t nAlignment)

{
	if (pObject != NULL)
		_aligned_free_dbg(pObject);
}

LightManager::LightManager()
{
}


LightManager::LightManager(const LightManager& other)
{
}


LightManager::~LightManager()
{
}


void LightManager::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = DirectX::XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightManager::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = DirectX::XMFLOAT4(red, green, blue, alpha);
	return;
}


void LightManager::SetPosition(float x, float y, float z)
{
	m_position = DirectX::XMVectorSet(x, y, z, 0.0f);
	return;
}


void LightManager::SetLookAt(float x, float y, float z)
{
	m_lookAt = DirectX::XMVectorSet(x, y, z, 0.0f);
	return;
}


DirectX::XMFLOAT4 LightManager::GetAmbientColor()
{
	return m_ambientColor;
}


DirectX::XMFLOAT4 LightManager::GetDiffuseColor()
{
	return m_diffuseColor;
}


DirectX::XMVECTOR LightManager::GetPosition()
{
	return m_position;
}


void LightManager::GenerateViewMatrix()
{
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Create the view matrix from the three vectors.
	m_viewMatrix = DirectX::XMMatrixLookAtLH(m_position, m_lookAt, up);

	return;
}


void LightManager::GetViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}


void LightManager::GenerateOrthoMatrix(float width, float depthPlane, float nearPlane)
{
	// Create the orthographic matrix for the light.
	m_orthoMatrix=DirectX::XMMatrixOrthographicLH(width, width, nearPlane, depthPlane);

	return;
}


void LightManager::GetOrthoMatrix(DirectX::XMMATRIX& orthoMatrix)
{
	orthoMatrix = m_orthoMatrix;
	return;
}


void LightManager::SetDirection(float x, float y, float z)
{
	m_direction = DirectX::XMFLOAT3(x, y, z);
	return;
}


DirectX::XMFLOAT3 LightManager::GetDirection()
{
	return m_direction;
}