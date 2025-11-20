#pragma once

#include "Ogre.h"
class Bomb
{
protected:
	struct object {
		Ogre::Entity* ent;
		Ogre::SceneNode* node;
	};

	object fuse;
	object body;
	Ogre::SceneNode* mNode;
public:
	Bomb(Ogre::Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng);
	~Bomb();

};

