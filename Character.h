#pragma once
#include "IG2Object.h"

class Labirynth;
class Character : public IG2Object
{
protected:
	double speed;
	Labirynth* labuburinth;

public:
	explicit Character(double speed, Labirynth* labuburinth, SceneManager* sceneMng, SceneNode* sceneNode, std::string mesh, Vector3 pos) 
		:  IG2Object(pos, sceneNode, sceneMng, mesh), speed(speed), labuburinth(labuburinth) {}

	virtual ~Character() {}

	virtual bool tryToMove(double delta) { return false; }
};

