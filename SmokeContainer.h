#pragma once

#include "IG2Object.h"
namespace Ogre {
	class ParticleSystem;
	class SceneNode;
}

class SmokeContainer : public IG2Object {
	Ogre::ParticleSystem* pSys;

	double timeUntilDeletion;
	const double ACTIVATION_DURATION = 2.0;
public:
	SmokeContainer(Ogre::Vector3 initPos, Ogre::SceneNode* node, SceneManager* sceneMng, int iterator);
	~SmokeContainer() {}

	void frameRendered(const Ogre::FrameEvent& evt) override;
	void startSmoking();
	inline bool isActive() { return timeUntilDeletion > .0; }
};

