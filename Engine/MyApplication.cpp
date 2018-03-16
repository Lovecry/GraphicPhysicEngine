#include "MyApplication.h"
#include <math.h>    
#include <time.h>


void MyApplication::start(){

	//view objects in scene
	renderObject();
	//uncomment to view physic engine
	//physic();
}

void MyApplication::update(){
	//uncomment to view particle system
	//particle();
}


void MyApplication::particle(){
	
	DirectX::XMFLOAT3 cameraPosition, particlePosition;
	DirectX::XMMATRIX translateMatrix, worldMatrix, projectionMatrix, viewMatrix;

	double angle;
	float rotation;
	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();
	// Set the position of the billboard model.
	particlePosition.x = 50.0f;
	particlePosition.y = 8.0f;
	particlePosition.z = 20.0f;
	angle = atan2(particlePosition.x - cameraPosition.x, particlePosition.z - cameraPosition.z) * (180.0 / DirectX::XM_PI);
	rotation = (float)angle * 0.0174532925f;
	worldMatrix = DirectX::XMMatrixRotationY(rotation);
	translateMatrix = DirectX::XMMatrixTranslation(particlePosition.x, particlePosition.y, particlePosition.z);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);
	m_Camera->GetViewMatrix(viewMatrix); //Get camera matrix
	projectionMatrix = m_D3D->GetTransf()->projection;
	// Turn on alpha blending.
	m_D3D->TurnOnAlphaBlending();
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());
	bool result = m_ShaderManager->RenderParticleShader(m_ParticleSystem->GetIndexCount(), 1, worldMatrix, viewMatrix, projectionMatrix, m_ParticleSystem->GetTexture());
	/*assert( result == false );*/
	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();
}


void MyApplication::physic(){
	sphere1 = InstanceGameObject(); // Primo oggetto con posizione e scala
	sphere1->addModel(m_SphereModel);
	sphere1->addShader(IdShader::color);
	sphere1->setPosition(50, 10, 40);
	sphere1->setScale(1, 1, 1);
	AddRigidBody(sphere1, 0, 15);

	sphere2 = InstanceGameObject();
	sphere2->addModel(m_SphereModel);
	sphere2->addShader(IdShader::texture);
	sphere2->addTexture(Constants::METAL);
	sphere2->addTexture(Constants::WALL01);
	sphere2->setPosition(51, 20, 40);
	sphere2->setScale(1, 1, 1);
	AddRigidBody(sphere2, 0, 15);

	sphere3 = InstanceGameObject();
	sphere3->addModel(m_SphereModel);
	sphere3->addShader(IdShader::texture);
	sphere3->addTexture(Constants::METAL);
	sphere3->setPosition(20, 20, 50);
	sphere3->setScale(1, 1, 1);
	AddRigidBody(sphere3, 0, 10);

	cube1 = InstanceGameObject();
	cube1->addModel(m_CubeModel);
	cube1->addShader(IdShader::texture);
	cube1->addTexture(Constants::METAL);
	cube1->addTexture(Constants::ICE);
	cube1->setPosition(35, 20, 50);
	cube1->setScale(1, 1, 1);
	AddRigidBody(cube1, 1, 7);

	cube2 = InstanceGameObject();
	cube2->addModel(m_CubeModel);
	cube2->addShader(IdShader::color);
	cube2->setPosition(40, 10, 50);
	cube2->setScale(1, 1, 1);
	AddRigidBody(cube2, 1, 7);	
}

void MyApplication::renderObject()
{
	for (int i = 0; i < Constants::MAX_MODELS; ++i)
	{
		GameObject* temp;
		temp = InstanceGameObject();
		temp->addModel(m_SphereModel);
		temp->setPosition((float)(rand() % 100), (float)(rand() % 10), (float)(rand() % 100));
		temp->addShader(IdShader::color);
		temp->setScale(1, 1, 1);
		m_GameObjectPool.push_back(temp);
	}
}