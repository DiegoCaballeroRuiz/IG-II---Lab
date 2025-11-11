#pragma once
#include "Ogre.h"
#include <string>
#include <vector>

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
	
public:
	Labirynth(std::string filePath, SceneManager* sceneManager, Ogre::SceneNode* sceneNode, Vector3 topLeftcorner, Hero*& hero, std::vector<Enemy*>& enemies);
	~Labirynth();

	bool canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir);
};