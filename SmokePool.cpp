#include "SmokePool.h"
#include "OgreParticleSystem.h"
#include "SmokeContainer.h"
#include "IG2App.h"

SmokePool::SmokePool() : firstFree(0), rootNode(nullptr)
{
}

SmokePool::~SmokePool() {
	for (auto smoker : smokers)
		delete smoker;
}

void 
SmokePool::initSmoke(int iterator) {
	SmokeContainer* smoker = new SmokeContainer(Ogre::Vector3(.0), rootNode->createChildSceneNode(), IG2App::getSingleton().getSceneManager(), iterator);
	smokers[iterator] = smoker;
}
void 
SmokePool::initSmokes() {
	for (int i = 0; i < smokers.size() - 1; ++i)
		initSmoke(i);

	firstFree = 0;
}

void 
SmokePool::deleteSmoke(int index) {
	smokers[index]->setVisible(false);
	auto aux = smokers[index];
	smokers[index] = smokers[firstFree - 1];
	smokers[firstFree - 1] = aux;
	firstFree--;
}

void 
SmokePool::init(int N, Ogre::SceneNode* rootNode) {
	this->rootNode = rootNode;
	smokers.assign(N + 1, nullptr);
	initSmokes();
}

void 
SmokePool::frameRendered(const Ogre::FrameEvent& evt) {
	for (int i = 0; i < firstFree; ++i) {
		if (!smokers[i]->isActive()) deleteSmoke(i);
		else smokers[i]->update(evt.timeSinceLastEvent);
	}
}

bool 
SmokePool::activateFreeSmoker(Ogre::Vector3 pos) {
	if (firstFree == smokers.size()) return false;

	auto newActive = smokers[firstFree];
	firstFree++;

	newActive->setPosition(pos);
	newActive->startSmoking();

	return true;
}