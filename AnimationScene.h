#pragma once
#include "SceneInterface.h"
#include <OgreInput.h>
#include <Ogre.h>
#include <string>


namespace Ogre {
	class SceneNode;
	class Timer;
}

class AnimatableEntity;
class PlaneObject;

class AnimationScene : public SceneInterface, public OgreBites::InputListener
{
protected:
	const std::string RUN_TOP = "RunTop", RUN_BASE = "RunBase", DANCE = "Dance", HAND_R = "Hand.R", HAND_L = "Hand.L";
	const double LOOP_DURATION = 22000;
	Ogre::SceneNode* root;
	AnimatableEntity* sinbad;
	AnimatableEntity* ogreHead;
	PlaneObject* floor;
	Ogre::Timer* timer;

	Ogre::Entity* leftSword; 
	Ogre::Entity* rightSword;

	void setSinbadAnims();
	void setOgreheadAnims();

	bool swordsAttached = false;
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

