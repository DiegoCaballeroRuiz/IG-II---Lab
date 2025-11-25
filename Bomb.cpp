#include "Bomb.h"
#include "Globals.h"

#include <iostream>
#include <math.h>


Bomb::Bomb(Ogre::Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, int iterator)
	: IG2Object(initPos, node, sceneMng, "sphere.mesh"), unitScale((GAME_UNIT / mNode->getScale()) * BOMB_SIZE) {

	this->setMaterialName("bomb/Black");

	// Create fuse
	Ogre::Entity* fuseEnt = sceneMng->createEntity("column.mesh");
	fuseEnt->setMaterialName("bomb/Fuse");
	Ogre::SceneNode* fuseNode = mNode->createChildSceneNode();
	fuseNode->setPosition(.0, GAME_UNIT / 2, .0);
	fuseNode->attachObject(fuseEnt);
	fuse = { fuseEnt, fuseNode };

	// Create particleSystem
	pSys = sceneMng->createParticleSystem("FuseSmoker" + std::to_string(iterator), "Smoke/Fire");
	Ogre::SceneNode* fuseSmokeNode = fuseNode->createChildSceneNode();
	fuseSmokeNode->setPosition(Vector3(.0, SMOKE_OFFSET, .0));
	fuseSmokeNode->attachObject(pSys);
	pSys->setEmitting(false);

	mNode->setScale(unitScale);
	unitScale *= 0.5;
	fuse.node->setScale(Ogre::Vector3(BOMB_FUSE_SIZE));
}

Bomb::~Bomb() {

}

void 
Bomb::update(double dt) {
	timeUntilExplosion -= dt;

	fuse.node->setPosition(fuse.node->getPosition() - Vector3(.0, GAME_UNIT * EXPLOSION_DURATION, .0) * dt);
	if (timeUntilExplosion <= 0) {
		pSys->clear();
		pSys->setEmitting(false);
	}
	mNode->setScale(unitScale - unitScale * SCALE_VARIANCE * sinf(EXPLOSION_DURATION - timeUntilExplosion * 3));
}

void 
Bomb::activateBomb() {
	timeUntilExplosion = EXPLOSION_DURATION;
	this->setVisible(true);
	fuse.node->setPosition(.0, GAME_UNIT / 2, .0);
	pSys->setEmitting(true);
}
