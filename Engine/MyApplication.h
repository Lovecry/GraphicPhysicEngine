#pragma once


#include "GraphicsManager.h"
#include "GameObject.h"
#include "Physic.h"
#include "Constants.h"
#include <iostream>
#include <vector>


using namespace std;


class MyApplication : public GraphicsManager {

public :
	void start() override;
	void update() override;

	void particle();
	void physic();
	void renderObject();
	std::vector<GameObject*> m_GameObjectPool;

	GameObject* sphere1;
	GameObject* sphere2;
	GameObject* cube1;
	GameObject* sphere3;
	GameObject* cube2;
};
