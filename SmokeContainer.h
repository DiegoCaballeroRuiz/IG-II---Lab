#pragma once

#include "IG2Object.h"
namespace Ogre {
	class ParticleSystem;
	class SceneNode;
}

class SmokeContainer : public IG2Object {
	Ogre::ParticleSystem* pSys;

	double timeUntilDeletion;
	const double ACTIVATION_DURATION = 3.5;
public:
	SmokeContainer(Ogre::Vector3 initPos, Ogre::SceneNode* node, SceneManager* sceneMng, int iterator);
	~SmokeContainer() {}

	void update(double dt);
	void startSmoking();
	inline bool isActive() { return timeUntilDeletion > .0; }
};

