#include "Camera.h"


void * Camera::operator new(size_t nSize, size_t nAlignment)

{
	if (((nAlignment)&(nAlignment - 1)) == 0)
	return (void *)_aligned_malloc_dbg(nSize, nAlignment, __FILE__, __LINE__);
	else
		return (void *)NULL;

}

void Camera::operator delete(void *pObject, size_t nAlignment)

{
	if (pObject != NULL)
		_aligned_free_dbg(pObject);
}

Camera::Camera()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;
}


Camera::Camera(const Camera& other)
{
}


Camera::~Camera()
{
}


void Camera::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}


void Camera::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}


DirectX::XMFLOAT3 Camera::GetPosition()
{
	return DirectX::XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}


DirectX::XMFLOAT3 Camera::GetRotation()
{
	return DirectX::XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}


void Camera::Render()
{
	DirectX::XMVECTOR up = DirectX::XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	DirectX::XMVECTOR position = DirectX::XMVectorSet(m_positionX, m_positionY, m_positionZ, 0.0f); 
	DirectX::XMVECTOR lookAt = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	float yaw, pitch, roll;
	DirectX::XMMATRIX rotationMatrix;
	
	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	lookAt = DirectX::XMVector3TransformCoord(lookAt, rotationMatrix);
	up = DirectX::XMVector3TransformCoord(up, rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = DirectX::XMVectorAdd(position, lookAt);
	
	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);

	return;
}


void Camera::GetViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}