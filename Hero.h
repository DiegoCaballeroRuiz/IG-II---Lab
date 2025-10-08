#pragma once
#include "IG2Object.h"

class Labirynth;
class Hero : public IG2Object
{
private:
	const double SPEED = 0.5;
	Vector3 targetDirection;
	Vector3 currentDirection;
	
	Labirynth* labuburinth;
public:
	Hero(Vector3 initPos, Vector3 currentDirection, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu);
	void keypressed(OgreBites::Keycode key);
	bool tryToMove();
};

