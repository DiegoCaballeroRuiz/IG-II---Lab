#include "BombPool.h"

#include <Ogre.h>
#include "IG2App.h"
#include "Bomb.h"

using namespace Ogre;

BombPool::BombPool() 
{
}

void 
BombPool::init(int N, Ogre::SceneNode* rootNode) {
	this->rootNode = rootNode;
	bombs.assign(N, nullptr);
	initBombs();
}

BombPool::~BombPool() {

}

bool
BombPool::activateFreeBomb(Vector3 pos) {
	if (firstFree == bombs.size() - 1) return false;

	Bomb* newActive = bombs[firstFree];
	firstFree++;

	newActive->setPosition(pos);
	newActive->activateBomb();
}

void 
BombPool::initBomb(int iterator) {
	Bomb* bomb = new Bomb(Vector3(.0), rootNode->createChildSceneNode(), IG2App::getSingleton().getSceneManager(), iterator);
	bomb->setVisible(false);
	bombs[iterator] = bomb;
}

void
BombPool::initBombs() {
	for (int i = 0; i < bombs.size() - 1; ++i)
		initBomb(i);

	firstFree = 0;
}

void 
BombPool::frameRendered(const Ogre::FrameEvent& evt) {
	for (int i = 0; i < firstFree; ++i) {
		if (!bombs[i]->isActive()) explodeBomb(i);
		else bombs[i]->update(evt.timeSinceLastFrame);
	}
}

void 
BombPool::explodeBomb(int index) {
	//Explosion


	//Deletion
	bombs[index]->setVisible(false);
	auto aux = bombs[index];
	bombs[index] = bombs[firstFree - 1];
	bombs[firstFree - 1] = aux;
	firstFree--;
}