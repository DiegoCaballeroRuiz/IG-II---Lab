#pragma once
#include "Character.h"
#include <OgreInput.h>

class Labirynth;
class BombPool;
class Hero : public Character
{
private:
	int lives;
	
	double inmuneTime;
	Vector3 targetDirection;
	Vector3 currentDirection;

	BombPool* bombPool;
public:
	Hero(Vector3 initPos, Vector3 currentDirection, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu);
	bool keyPressed(const OgreBites::KeyboardEvent& evt) override;
	void frameRendered(const Ogre::FrameEvent& evt) override;
	bool tryToMove(double delta);

	inline void registerBombPool(BombPool* newBombPool) { bombPool = newBombPool; }
};

