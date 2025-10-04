#pragma once
#include "IG2Object.h"

class Labirynth;
class Hero : public IG2Object
{
private:
	const double SPEED = 5;
	Vector3 targetDirection;
	
	Labirynth* labuburinth;
public:
	Hero(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu);
	void keypressed(OgreBites::Keycode key);
};

