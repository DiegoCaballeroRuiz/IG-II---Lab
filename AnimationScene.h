#pragma once
#include "SceneInterface.h"
#include <OgreInput.h>

namespace Ogre {
	class SceneNode;
	class Timer;
}

class AnimatableEntity;
class PlaneObject;

class AnimationScene : public SceneInterface, public OgreBites::InputListener
{
protected:
	Ogre::SceneNode* root;
	AnimatableEntity* sinbad;
	AnimatableEntity* ogreHead;
	PlaneObject* floor;
	Ogre::Timer* timer;

	void setSinbadAnims();
	void setOgreheadAnims();
public:
	AnimationScene();
	~AnimationScene();

	void setupScene() override;
	void closeScene() override;
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;

	inline bool checkCollisions() override { return false; }
	inline void changeInfoOverlay(int lifes, int points) override {}
};

