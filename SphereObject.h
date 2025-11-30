#pragma once

#include "IG2Object.h"

class SphereObject : public IG2Object
{

public:
	SphereObject(Vector3 pos, SceneNode* mNode, SceneManager* mSM, double scale, std::string materialName);
	~SphereObject() {}
};

