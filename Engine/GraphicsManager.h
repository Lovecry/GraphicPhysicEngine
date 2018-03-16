#pragma once


#include "LightManager.h"
#include "DXManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"

#include "Camera.h"
#include "Model.h"
#include "ParticleModel.h"
#include "Terrain.h"
#include "GameObject.h"
#include "Frustum.h"
#include "SceneModelsList.h"

#include "RenderToTexture.h"

#include "textDrawer.h"
#include "Constants.h"
#include "Physic.h"

#include <vector>


class Camera;


class GraphicsManager
{
public:
	GraphicsManager();
	GraphicsManager(const GraphicsManager&);
	~GraphicsManager();

	bool Initialize(DXManager*, HWND, Camera*, Physic*);
	bool Frame(float, int, int);
	void Shutdown();	

protected:
	virtual void start() = 0;
	virtual void update() = 0;
	GameObject* InstanceGameObject();
	void AddRigidBody(GameObject *, int type, float mass = 5);

private:
	bool RenderSceneToTexture();
	bool Render(float);
	void addWindows(GameObject*);
	
protected:
	Model* m_CubeModel;
	Model* m_SphereModel;
	Camera* m_Camera;
	DXManager* m_D3D;
	ParticleModel* m_ParticleSystem;

	ShaderManager* m_ShaderManager;
	TextureManager* m_TextureManager;

	SceneModelsList* m_SceneModelsListDinamic;
	SceneModelsList* m_SceneModelsListStatic;

private:	
	LightManager* m_Light;
	Terrain* m_Terrain;	
	RenderToTexture* m_RenderToTexture;
	Frustum* m_Frustum;
	TextDrawer* m_TextDrawer;
	TextFont* m_ArialFont;
	Physic* m_Physic;

};