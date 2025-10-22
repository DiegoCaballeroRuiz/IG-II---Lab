#pragma once
#include "IG2Object.h"
#include <OgreInput.h>

class Labirynth;
class Hero : public IG2Object
{
private:
	const double SPEED = 2.5;
	Vector3 targetDirection;
	Vector3 currentDirection;
	
	Labirynth* labuburinth;
public:
	Hero(Vector3 initPos, Vector3 currentDirection, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu);
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;
	bool tryToMove(double delta);
};

