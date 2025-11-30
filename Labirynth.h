#pragma once
#include "Ogre.h"
#include <string>
#include <vector>

class Hero;
class Enemy;
class PlaneObject;
class SmokeContainer;
class BombPool;
class Hero;
class Enemy;
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
	std::vector<std::vector<SmokeContainer*>> smokers;
	Hero* hero;
	std::vector<Enemy*> enemies;

	const int MAX_SMOKES = 25;

	bool tileExploded(Vector3 pos);
	void checkBombCollision(Vector3 pos);
public:
	Labirynth(std::string filePath, SceneManager* sceneManager, Ogre::SceneNode* sceneNode, Vector3 topLeftcorner, BombPool* bPool);
	~Labirynth();

	bool canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir);
	bool setExplosion(Vector3 initialPos, Vector3 previousPos, int range);

	bool checkPlayerCollision();
};