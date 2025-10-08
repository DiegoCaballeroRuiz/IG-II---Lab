#pragma once
#include "Ogre.h"
#include <string>
#include <vector>

using namespace Ogre;

class Labirynth {
	int numFilas, numColumnas;
	Vector3 initPos;
	SceneManager* mSM;
	SceneNode* mSceneNode;
	std::vector<std::vector<bool>> walls;

	
public:
	Labirynth(std::string filePath, SceneManager* sceneManager, Vector3 topLeftcorner);
	~Labirynth();

	bool freeSquare(Vector3 pos);
};