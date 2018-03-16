#pragma once


#include "Model.h"
#include "TextureManager.h"
#include "ShaderManager.h"

#include "Vector3.h"
#include "RigidBody.h"
#include "Forces.h"

#include <DirectXMath.h>
#include <vector>


using namespace DirectX;


enum IdShader { color, depth, texture};


class GameObject{

public:
	GameObject(TextureManager*, ShaderManager*);
	~GameObject();

	void addModel(Model* modelId) { m_Model = modelId; };
	void addShader(IdShader shaderId) { m_idShader = shaderId; };
	void addTexture(const WCHAR* textureId) {	m_textures.push_back(m_TextureManager->GetTexture(textureId));	};

	void addRigidBody(int type, float mass = 5);

	void setPosition(float, float, float);
	void setScale(float x, float y, float z) { m_scale = { x, y, z }; };
	void setID(unsigned int x) { m_Id = x; };
	XMFLOAT3 getPosition() const { return m_position.convertToXMFloat3(); };
	XMFLOAT3 getScale() const { return m_scale.convertToXMFloat3(); };
	RigidBody& getRigidbody() const { return *m_pRigidbody; };

	bool render(XMMATRIX&, XMMATRIX&, XMMATRIX&);
	
	bool isRigidBody() const;
	static unsigned int m_IdCount;
private :

	Vector3 m_position;
	Vector3 m_scale;
	unsigned int m_Id;
	float m_radius; // Frustum Culling
	Model* m_Model;
	IdShader m_idShader; // serie di if nel render
	RigidBody* m_pRigidbody;
	std::vector<ID3D11ShaderResourceView*> m_textures;

	TextureManager* m_TextureManager;
	ShaderManager* m_ShaderManager;	
};