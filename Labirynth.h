#pragma once
#include "Ogre.h"
#include <string>
#include <vector>
#include "SmokePool.h"

class Hero;
class Enemy;
class PlaneObject;
namespace Ogre {
	class Light;
}

using namespace Ogre;
class Labirynth {
	int numFilas, numColumnas;
	Vector3 initPos;
	SceneManager* mSM;
	SceneNode* mSceneNode;
	PlaneObject* p;
	Light* mLight;
	std::vector<std::vector<bool>> walls;

	const int MAX_SMOKES = 50;

	SmokePool pool;
	bool canExplode(Vector3 pos);
public:
	Labirynth(std::string filePath, SceneManager* sceneManager, Ogre::SceneNode* sceneNode, Vector3 topLeftcorner, Hero*& hero, std::vector<Enemy*>& enemies);
	~Labirynth();

	bool canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir);
	bool setExplosion(Vector3 initialPos, Vector3 previousPos, int range);
};