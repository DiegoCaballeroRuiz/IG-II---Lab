#pragma once
#include "IG2Object.h"

class PlaneObject : public IG2Object
{
public:
	PlaneObject(Vector3 initPos, Ogre::SceneManager* sceneMng, Ogre::SceneNode* sceneNode, double width, double height, std::string name = "Floor");
	~PlaneObject() {}
};

