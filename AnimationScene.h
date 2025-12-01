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
class Bomb;
class SphereObject;

class AnimationScene : public SceneInterface, public OgreBites::InputListener
{
protected:
	const std::string RUN_TOP = "RunTop", RUN_BASE = "RunBase", DANCE = "Dance", HAND_R = "Handle.R", HAND_L = "Handle.L";
	const double LOOP_DURATION = 21000;
	Ogre::SceneNode* root;
	AnimatableEntity* sinbad;
	AnimatableEntity* ogreHead;
	Bomb* bomb;
	PlaneObject* floor;
	Ogre::Timer* timer;

	Ogre::Entity* leftSword; 
	Ogre::Entity* rightSword;
	SphereObject* planet;

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

	inline void changeInfoOverlay(int lifes, int points) override {}
};

