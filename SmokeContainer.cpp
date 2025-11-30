#include "SmokeContainer.h"

#include "OgreParticleSystem.h"

SmokeContainer::SmokeContainer(Vector3 initPos, SceneNode* node, SceneManager* sceneMng, int iterator) 
	: IG2Object(initPos, node, sceneMng) 
{
	pSys = sceneMng->createParticleSystem("TileSmoker" + std::to_string(iterator), "Smoke/Explode");
	pSys->setEmitting(false);
	node->attachObject(pSys);
}

void 
SmokeContainer::frameRendered(const Ogre::FrameEvent& evt) {
	if (!isActive()) return;

	timeUntilDeletion -= evt.timeSinceLastFrame;
	if (timeUntilDeletion < .0) {
		pSys->setEmitting(false);
		pSys->clear();
	}
}

void 
SmokeContainer::startSmoking() {
	pSys->setEmitting(true);
	timeUntilDeletion = ACTIVATION_DURATION;
}
