#pragma once
#include "IG2Object.h"

class PlaneObject : public IG2Object
{
public:
	PlaneObject(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode);
	~PlaneObject();
};

