#pragma once

#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "GameObject.h"

class SceneModelsList
{
public:
	SceneModelsList();
	SceneModelsList(const SceneModelsList&);
	~SceneModelsList();

	int GetModelsCount() { return m_SceneModelVector.size(); };
	GameObject* getGameObject(int index) { return m_SceneModelVector[index]; };
	void AddObject(GameObject* gameObject);
	void Remove(int index);

private:
	std::vector<GameObject*> m_SceneModelVector;
};
