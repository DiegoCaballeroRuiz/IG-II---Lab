#include "Bomb.h"
#include "Globals.h"

#include <iostream>

Bomb::Bomb(Ogre::Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng): mNode(node) {
	mNode->setPosition(initPos);

	Ogre::Entity* bodyEnt = sceneMng->createEntity("sphere.mesh");
	bodyEnt->setMaterialName("bomb/Black");
	Ogre::SceneNode* bodyNode = mNode->createChildSceneNode();
	bodyNode->attachObject(bodyEnt);

	body = { bodyEnt, bodyNode };

	Ogre::Entity* fuseEnt = sceneMng->createEntity("column.mesh");
	fuseEnt->setMaterialName("bomb/Fuse");
	Ogre::SceneNode* fuseNode = mNode->createChildSceneNode();
	fuseNode->setPosition(.0, GAME_UNIT / 2, .0);
	fuseNode->attachObject(fuseEnt);

	fuse = { fuseEnt, fuseNode };

	mNode->setScale((GAME_UNIT / mNode->getScale()) * BOMB_SIZE);
	fuse.node->setScale(Ogre::Vector3(BOMB_FUSE_SIZE));

	/*body = IG2Object(Vector3(.0), mNode->createChildSceneNode(), sceneMng, "sphere.mesh");
	fuse = IG2Object(Vector3(.0, GAME_UNIT/2, .0), mNode->createChildSceneNode(), sceneMng, "column.mesh");*/
}

Bomb::~Bomb() {}